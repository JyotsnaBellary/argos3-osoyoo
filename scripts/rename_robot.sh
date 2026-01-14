#!/usr/bin/env bash
set -euo pipefail

usage() {
  cat <<'EOF'
Usage: scripts/rename_robot.sh [options]

Renames files and directories whose names contain the "from" token.
Defaults: --robot-plugin=argos3/plugins/robots/turtlebot4 --current=turtlebot4 --change-to=osoyoo

Options:
  --robot-plugin PATH   Root folder to rename within (default: argos3/plugins/robots/turtlebot4)
  --current TOKEN       Token to replace (default: turtlebot4)
  --change-to TOKEN     Replacement token (default: osoyoo)
  --dry-run             Print planned renames without applying
  -h, --help            Show this help

Examples:
  scripts/rename_robot.sh --dry-run
  scripts/rename_robot.sh --robot-plugin argos3/plugins/robots/turtlebot4 --current turtlebot4 --change-to osoyoo
  scripts/rename_robot.sh --robot-plugin argos3/plugins/robots/turtlebot4 --current turtlebot --change-to osoyoo
EOF
}

dry_run=0
root="argos3/plugins/robots/turtlebot4"
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
  echo "python3 is required for safe renames." >&2
  exit 1
fi

python3 - <<PY
import os
import sys
from pathlib import Path

root = Path("$root")
from_token = "$from"
to_token = "$to"
dry_run = $dry_run

if not root.exists():
    print(f"Path not found: {root}", file=sys.stderr)
    sys.exit(1)

targets = []
for path in root.rglob("*"):
    name = path.name
    if from_token in name:
        targets.append(path)

# Rename deepest paths first to avoid clobbering.
targets.sort(key=lambda p: len(p.parts), reverse=True)

for path in targets:
    new_name = path.name.replace(from_token, to_token)
    new_path = path.with_name(new_name)
    if dry_run:
        print(f"DRY-RUN: {path} -> {new_path}")
    else:
        os.rename(path, new_path)
        print(f"RENAMED: {path} -> {new_path}")
PY
