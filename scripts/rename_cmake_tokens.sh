#!/usr/bin/env bash
set -euo pipefail

usage() {
  cat <<'EOF'
Usage: scripts/rename_cmake_tokens.sh [options]

Replaces tokens in CMakeLists.txt files under the given robot plugin folder.
Defaults: --robot-plugin=argos3/plugins/robots/osoyoo --current=turtlebot4 --change-to=osoyoo

It also replaces the ALL-CAPS form of the tokens.

Options:
  --robot-plugin PATH   Root folder to search (default: argos3/plugins/robots/osoyoo)
  --current TOKEN       Token to replace (default: turtlebot4)
  --change-to TOKEN     Replacement token (default: osoyoo)
  --dry-run             Print files that would change without editing
  -h, --help            Show this help

Examples:
  scripts/rename_cmake_tokens.sh --dry-run
  scripts/rename_cmake_tokens.sh --robot-plugin argos3/plugins/robots/osoyoo --current turtlebot4 --change-to osoyoo
EOF
}

dry_run=0
root="argos3/plugins/robots/osoyoo"
from="turtlebot4"
to="osoyoo"

while [[ $# -gt 0 ]]; do
  case "$1" in
    -h|--help)
      usage
      exit 0
      ;;
    --dry-run)
      dry_run=1
      shift
      ;;
    --robot-plugin)
      root="${2:-}"
      shift 2
      ;;
    --current)
      from="${2:-}"
      shift 2
      ;;
    --change-to)
      to="${2:-}"
      shift 2
      ;;
    *)
      echo "Unknown option: $1" >&2
      usage
      exit 1
      ;;
  esac
done

if [[ -z "$root" || -z "$from" || -z "$to" ]]; then
  echo "Missing required option value." >&2
  usage
  exit 1
fi

if [[ "$from" == "$to" ]]; then
  echo "from and to are the same; nothing to do." >&2
  exit 1
fi

if ! command -v python3 >/dev/null 2>&1; then
  echo "python3 is required for safe replacements." >&2
  exit 1
fi

python3 - <<PY
import sys
from pathlib import Path

root = Path("$root")
from_token = "$from"
to_token = "$to"
dry_run = $dry_run

if not root.exists():
    print(f"Path not found: {root}", file=sys.stderr)
    sys.exit(1)

def replace_all(text: str) -> str:
    return (
        text.replace(from_token, to_token)
            .replace(from_token.upper(), to_token.upper())
    )

files = list(root.rglob("CMakeLists.txt"))
for path in files:
    original = path.read_text()
    updated = replace_all(original)
    if original == updated:
        continue
    if dry_run:
        print(f"DRY-RUN: {path}")
    else:
        path.write_text(updated)
        print(f"UPDATED: {path}")
PY
