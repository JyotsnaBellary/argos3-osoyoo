#!/usr/bin/env bash
set -euo pipefail

usage() {
  cat <<'EOF'
Usage: scripts/rename_robot_tokens.sh [options]

Replaces robot tokens inside text files under a robot plugin folder.
Defaults:
  --robot-plugin=argos3/plugins/robots/osoyoo
  --current=turtlebot4
  --change-to=osoyoo

It replaces:
  - lowercase token
  - UPPERCASE token
  - CamelCase token (first letter upper)
You can override CamelCase/UPPERCASE explicitly.

Options:
  --robot-plugin PATH        Root folder to search (default: argos3/plugins/robots/osoyoo)
  --current TOKEN            Lowercase token to replace (default: turtlebot4)
  --change-to TOKEN          Lowercase replacement token (default: osoyoo)
  --current-camel TOKEN      CamelCase token override (default: Turtlebot4)
  --change-to-camel TOKEN    CamelCase replacement override (default: Osoyoo)
  --current-upper TOKEN      Uppercase token override (default: TURTLEBOT4)
  --change-to-upper TOKEN    Uppercase replacement override (default: OSOYOO)
  --dry-run                  Print files that would change without editing
  -h, --help                 Show this help

Examples:
  scripts/rename_robot_tokens.sh --dry-run
  scripts/rename_robot_tokens.sh --robot-plugin argos3/plugins/robots/osoyoo --current turtlebot4 --change-to osoyoo
  scripts/rename_robot_tokens.sh --current turtlebot4 --change-to osoyoo --change-to-camel OsoYoo
EOF
}

dry_run=0
root="argos3/plugins/robots/osoyoo"
from="turtlebot4"
to="osoyoo"
from_camel=""
to_camel=""
from_upper=""
to_upper=""

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
    --current-camel)
      from_camel="${2:-}"
      shift 2
      ;;
    --change-to-camel)
      to_camel="${2:-}"
      shift 2
      ;;
    --current-upper)
      from_upper="${2:-}"
      shift 2
      ;;
    --change-to-upper)
      to_upper="${2:-}"
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
from_camel = "$from_camel" or (from_token[:1].upper() + from_token[1:])
to_camel = "$to_camel" or (to_token[:1].upper() + to_token[1:])
from_upper = "$from_upper" or from_token.upper()
to_upper = "$to_upper" or to_token.upper()
dry_run = $dry_run

if not root.exists():
    print(f"Path not found: {root}", file=sys.stderr)
    sys.exit(1)

pairs = []
for src, dst in [
    (from_token, to_token),
    (from_camel, to_camel),
    (from_upper, to_upper),
]:
    if src and src != dst and (src, dst) not in pairs:
        pairs.append((src, dst))

def is_binary(path: Path) -> bool:
    try:
        with path.open("rb") as f:
            chunk = f.read(2048)
        return b"\x00" in chunk
    except OSError:
        return True

for path in root.rglob("*"):
    if not path.is_file():
        continue
    if is_binary(path):
        continue
    try:
        original = path.read_text(encoding="utf-8", errors="surrogateescape")
    except OSError:
        continue
    updated = original
    for src, dst in pairs:
        updated = updated.replace(src, dst)
    if updated == original:
        continue
    if dry_run:
        print(f"DRY-RUN: {path}")
    else:
        path.write_text(updated, encoding="utf-8", errors="surrogateescape")
        print(f"UPDATED: {path}")
PY
