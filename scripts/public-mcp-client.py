#!/usr/bin/env python3
"""Call the private no-auth Funnel MCP through verified public HTTPS ingress.

Read a tools/call request (name and arguments) from stdin. The private URL is
loaded locally and never passed in process arguments or printed. Output is
the MCP tool result, including its isError flag.
"""
from __future__ import annotations

import ipaddress
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import urllib.parse
import urllib.request

ROOT = Path(__file__).resolve().parents[1]


def main() -> int:
    params = json.load(sys.stdin)
    if set(params) != {"name", "arguments"}:
        raise ValueError("stdin must contain name and arguments")
    env = dict(line.split("=", 1) for line in
               (ROOT / ".tools/mcp_for_gptweb-ghidra/.env").read_text().splitlines()
               if line and not line.startswith("#"))
    if env.get("MCP_BEARER_TOKEN"):
        raise ValueError("this deployment requires no bearer authentication")
    state = json.loads(subprocess.check_output(["tailscale", "status", "--json"]))
    host = state["Self"]["DNSName"].rstrip(".")
    port = int(env["FUNNEL_HTTPS_PORT"])
    url = f"https://{host}:{port}{env['MCP_PATH']}"
    query = urllib.parse.urlencode({"name": host, "type": "A"})
    with urllib.request.urlopen("https://dns.google/resolve?" + query, timeout=20) as response:
        dns = json.load(response)
    addresses = [item["data"] for item in dns.get("Answer", [])
                 if item["type"] == 1 and ipaddress.ip_address(item["data"]).is_global]
    if not addresses:
        raise ValueError("no public IPv4 Funnel ingress found")
    directory = ROOT / ".analysis/public-client"
    directory.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=directory) as temporary:
        scratch = Path(temporary)
        headers = scratch / "headers.txt"
        headers.write_text("Content-Type: application/json\nAccept: application/json, text/event-stream\n")
        headers.chmod(0o600)
        body = scratch / "request.json"
        output = scratch / "response.txt"

        def rpc(identifier: int, method: str, arguments: dict):
            body.write_text(json.dumps({"jsonrpc": "2.0", "id": identifier,
                                        "method": method, "params": arguments}))
            body.chmod(0o600)
            command = ["curl", "--silent", "--show-error", "--ipv4", "--noproxy", "*",
                       "--resolve", f"{host}:{port}:{addresses[0]}",
                       "--connect-timeout", "15", "--max-time", "1000",
                       "--header", "@" + str(headers), "--data-binary", "@" + str(body),
                       "--output", str(output), "--write-out", "%{http_code}", "--config", "-"]
            result = subprocess.run(command, input="url = " + json.dumps(url) + "\n",
                                    capture_output=True, text=True)
            if result.returncode:
                raise ValueError("public HTTPS request failed (curl exit " + str(result.returncode) + ")")
            if result.stdout != "200":
                raise ValueError("MCP returned HTTP " + result.stdout)
            lines = [line[5:].strip() for line in output.read_text().splitlines()
                     if line.startswith("data:")]
            message = json.loads(lines[-1] if lines else output.read_text())
            if "error" in message:
                raise ValueError("MCP JSON-RPC error: " + json.dumps(message["error"]))
            return message["result"]

        rpc(1, "initialize", {"protocolVersion": "2025-03-26", "capabilities": {},
                             "clientInfo": {"name": "th075-public-client", "version": "1.0"}})
        result = rpc(2, "tools/call", params)
        print(json.dumps(result, ensure_ascii=False))
        return 1 if result.get("isError") else 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, KeyError, TypeError, ValueError, subprocess.CalledProcessError) as exc:
        print("error: " + str(exc), file=sys.stderr)
        raise SystemExit(1)
