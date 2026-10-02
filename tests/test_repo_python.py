"""Exercise repository Python isolation through a real nested script call."""
from pathlib import Path
import os
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class RepositoryPythonTests(unittest.TestCase):
    def test_nested_status_ignores_shell_pythonpath(self):
        with tempfile.TemporaryDirectory(prefix="th075-python-isolation-") as temporary:
            unrelated_directory = Path(temporary)
            (unrelated_directory / "json.py").write_text(
                'raise RuntimeError("inherited shell PYTHONPATH reached Python")\n'
            )
            result = subprocess.run(
                [str(ROOT / "scripts/repo-python"),
                 str(ROOT / "scripts/update-progress.py"), "--check"],
                cwd=unrelated_directory,
                env={**os.environ, "PYTHONPATH": str(unrelated_directory)},
                capture_output=True, text=True, timeout=30,
            )
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn("Progress card:", result.stdout)


if __name__ == "__main__":
    unittest.main()
