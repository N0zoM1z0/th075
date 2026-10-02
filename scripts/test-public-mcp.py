#!/usr/bin/env python3
"""Test the private TH075 Funnel URL without authentication or URL disclosure."""
from __future__ import annotations

import ipaddress
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import time
import urllib.parse
import urllib.request

ROOT = Path(__file__).resolve().parents[1]


def main() -> int:
    directory = ROOT / ".analysis/deployment"
    directory.mkdir(parents=True, exist_ok=True)
    env = dict(line.split("=", 1) for line in
               (ROOT / ".tools/mcp_for_gptweb-ghidra/.env").read_text().splitlines()
               if line and not line.startswith("#"))
    if env.get("MCP_BEARER_TOKEN"):
        raise ValueError("this deployment must have no bearer authentication configured")
    deadline = time.monotonic() + 10
    while True:
        try:
            with urllib.request.urlopen(f"http://127.0.0.1:{env['PORT']}/healthz", timeout=2) as response:
                health = json.load(response)
            break
        except urllib.error.URLError:
            if time.monotonic() >= deadline:
                raise
            time.sleep(0.2)
    if health.get("authentication") != "none" or health.get("workspaceRoot") != str(ROOT):
        raise ValueError("service does not report the expected no-auth TH075 configuration")
    state = json.loads(subprocess.check_output(["tailscale", "status", "--json"]))
    host = state["Self"]["DNSName"].rstrip(".")
    port = int(env["FUNNEL_HTTPS_PORT"])
    url = f"https://{host}:{port}{env['MCP_PATH']}"
    dns_url = "https://dns.google/resolve?" + urllib.parse.urlencode({"name": host, "type": "A"})
    with urllib.request.urlopen(dns_url, timeout=20) as response:
        dns = json.load(response)
    addresses = [row["data"] for row in dns.get("Answer", []) if row["type"] == 1
                 and ipaddress.ip_address(row["data"]).is_global]
    if not addresses:
        raise ValueError("public DNS returned no global IPv4 Funnel ingress address")
    ingress = addresses[0]
    results = []
    sequence = 0

    with tempfile.TemporaryDirectory(prefix="public-smoke-", dir=directory) as temporary:
        scratch = Path(temporary)
        def request(method: str, payload: dict | None = None, request_url: str | None = None):
            headers = scratch / "headers.txt"
            text = "Content-Type: application/json\nAccept: application/json, text/event-stream\n"
            headers.write_text(text)
            headers.chmod(0o600)
            output = scratch / "response.txt"
            command = ["curl", "--silent", "--show-error", "--ipv4", "--noproxy", "*",
                       "--resolve", f"{host}:{port}:{ingress}", "--connect-timeout", "15",
                       "--max-time", "120", "--request", method, "--header", "@" + str(headers),
                       "--output", str(output), "--write-out", "%{http_code}"]
            if payload is not None:
                body = scratch / "request.json"
                body.write_text(json.dumps(payload))
                command += ["--data-binary", "@" + str(body)]
            # Keep the private capability URL out of process arguments and logs.
            completed = subprocess.run([*command, "--config", "-"],
                input="url = " + json.dumps(request_url or url) + "\n",
                capture_output=True, text=True)
            if completed.returncode:
                raise ValueError("public HTTPS request failed: " + completed.stderr.strip())
            return int(completed.stdout), output.read_text()

        def rpc(method: str, params: dict):
            nonlocal sequence
            sequence += 1
            status, body = request("POST", {"jsonrpc": "2.0", "id": sequence,
                                           "method": method, "params": params})
            if status != 200:
                raise ValueError(f"{method}: HTTP {status}: {body[:500]}")
            messages = [line[5:].strip() for line in body.splitlines() if line.startswith("data:")]
            data = json.loads(messages[-1] if messages else body)
            if "error" in data:
                raise ValueError(f"{method}: {data['error']}")
            return data["result"]

        def tool(name: str, arguments: dict, expected_error: bool = False):
            result = rpc("tools/call", {"name": name, "arguments": arguments})
            if bool(result.get("isError")) != expected_error:
                raise ValueError(f"{name}: unexpected tool status: {result}")
            return "\n".join(block.get("text", "") for block in result.get("content", []))

        status, _ = request("POST", {"jsonrpc": "2.0", "id": 0, "method": "tools/list", "params": {}})
        if status != 200:
            raise ValueError("public MCP access without Authorization did not return HTTP 200")
        results.append("no-auth public request accepted (200)")
        status, _ = request("GET", request_url=f"https://{host}:{port}/not-a-th075-endpoint")
        if status != 404:
            raise ValueError("an unrelated URL unexpectedly exposes a handler")
        results.append("unrelated URL rejected (404)")
        initialized = rpc("initialize", {"protocolVersion": "2025-03-26", "capabilities": {},
                          "clientInfo": {"name": "th075-public-smoke", "version": "1.0"}})
        results.append("MCP initialize: " + initialized["protocolVersion"])
        listing = rpc("tools/list", {})
        if sorted(item["name"] for item in listing["tools"]) != ["ghidra_call", "run_command"]:
            raise ValueError("unexpected public tool catalog")
        results.append("two-tool discovery")
        bash = tool("run_command", {"command": "python3 scripts/verify-target.py"})
        if env["WORKSPACE_ROOT"] not in bash or "bd441e99075436e8" not in bash:
            raise ValueError("Bash tool did not attest the TH075 target")
        results.append("Bash workspace and target verification")
        checked = tool("ghidra_call", {"operation": "check"})
        if "TH075_GHIDRA_ATTESTATION_OK:bd441e99075436e8" not in checked:
            raise ValueError("public Ghidra attestation marker missing")
        results.append("Ghidra project attestation")
        metadata = tool("ghidra_call", {"operation": "function", "addresses": ["0x00401000"]})
        if "body_addresses: 27" not in metadata:
            raise ValueError("public function query returned an unexpected extent")
        results.append("bounded function query")
        decompiled = tool("ghidra_call", {"operation": "decompile", "addresses": ["0x00401000"]})
        if "DAT_00671210" not in decompiled:
            raise ValueError("public decompilation did not return the expected function")
        results.append("bounded decompilation")
        tool("ghidra_call", {"operation": "decompile", "addresses": ["0x0"]}, True)
        results.append("failed decompilation rejected")
        replay = tool("run_command", {"command":
            "python3 scripts/replay-exact-units.py --unit graphics-resource-client-constructor",
            "timeout_ms": 120000})
        if "Cold replay: 1/1 exact units" not in replay:
            raise ValueError("cold function replay failed through public Bash")
        results.append("cold 27-byte exact replay through Bash")
        status, _ = request("GET")
        if status != 405:
            raise ValueError("stateless MCP GET did not return HTTP 405")
        results.append("stateless GET rejected (405)")

    if any((ROOT / ".analysis/mcp-ghidra").iterdir()):
        raise ValueError("Ghidra bridge did not clean call scratch directories")
    results.append("bridge scratch cleanup")
    current = json.loads(subprocess.check_output(["tailscale", "funnel", "status", "--json"]))
    before_path = directory / "funnel-before-no-auth.json"
    if not before_path.exists():
        before_path = directory / "funnel-before.json"
    if before_path.exists():
        before = json.loads(before_path.read_text())
        for listener, web in before.get("Web", {}).items():
            for route, handler in web.get("Handlers", {}).items():
                if current.get("Web", {}).get(listener, {}).get("Handlers", {}).get(route) != handler:
                    raise ValueError("an existing Funnel handler changed")
        results.append("existing Funnel handlers preserved")
    listener = f"{host}:{port}"
    expected_proxy = f"http://127.0.0.1:{env['PORT']}{env['MCP_PATH']}"
    actual_proxy = current.get("Web", {}).get(listener, {}).get("Handlers", {}).get(env["MCP_PATH"], {}).get("Proxy")
    if actual_proxy != expected_proxy or not current.get("AllowFunnel", {}).get(listener):
        raise ValueError("TH075 public Funnel handler is not configured as expected")
    report = {"public_url": url, "public_ingress_ipv4": ingress, "authentication": "none",
              "resolution": "Google public DNS; curl --resolve and --noproxy '*'; TLS validation enabled",
              "checks": results, "result": "passed"}
    receipt = directory / "public-smoke.json"
    receipt.write_text(json.dumps(report, indent=2) + "\n")
    receipt.chmod(0o600)
    print(f"Public Funnel smoke test passed: {len(results)} checks via global IPv4 ingress.")
    for result in results:
        print("  " + result)
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, TypeError, ValueError, subprocess.CalledProcessError) as exc:
        print("error: public MCP test failed: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
