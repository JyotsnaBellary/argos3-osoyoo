#!/usr/bin/env bash
set -euo pipefail

usage() {
  cat <<'EOF'
Usage: scripts/rename_test_tokens.sh [options]

Replaces tokens in a test controller folder and its matching .argos file.
Defaults:
  --controllers-path=argos3/testing/controllers
  --experiments-path=argos3/testing/experiments
  --controller=osoyoo_test
  --current=turtlebot4
  --change-to=osoyoo

It replaces:
  - lowercase token
  - UPPERCASE token
  - CamelCase token (first letter upper)
You can override CamelCase/UPPERCASE explicitly.

Options:
  --controllers-path PATH   Root controllers folder (default: argos3/testing/controllers)
  --experiments-path PATH   Root experiments folder (default: argos3/testing/experiments)
  --controller NAME         Controller folder name (default: osoyoo_test; if omitted, auto-detect)
  --current TOKEN           Lowercase token to replace (default: turtlebot4)
  --change-to TOKEN         Lowercase replacement token (default: osoyoo)
  --current-camel TOKEN     CamelCase token override (default: Turtlebot4)
  --change-to-camel TOKEN   CamelCase replacement override (default: Osoyoo)
  --current-upper TOKEN     Uppercase token override (default: TURTLEBOT4)
  --change-to-upper TOKEN   Uppercase replacement override (default: OSOYOO)
  --rename-controller-folder  Rename the controller folder and .argos file (default: on)
  --rename-controller-files   Rename files inside the controller folder (default: on)
  --include-cmake             Update CMakeLists.txt in controllers (default: on)
  --dry-run                 Print files that would change without editing
  -h, --help                Show this help

Examples:
  scripts/rename_test_tokens.sh --dry-run --controller turtlebot4_test
  scripts/rename_test_tokens.sh --controller turtlebot4_test --current turtlebot4 --change-to osoyoo
  scripts/rename_test_tokens.sh --controller turtlebot4_test --current turtlebot4 --change-to osoyoo --change-to-camel OsoYoo
  scripts/rename_test_tokens.sh --current turtlebot4 --change-to osoyoo --rename-controller-folder
EOF
}

dry_run=0
controllers_root="argos3/testing/controllers"
experiments_root="argos3/testing/experiments"
controller=""
from="turtlebot4"
to="osoyoo"
from_camel=""
to_camel=""
from_upper=""
to_upper=""
rename_controller_folder=1
rename_controller_files=1
include_cmake=1

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
    --controllers-path)
      controllers_root="${2:-}"
      shift 2
      ;;
    --experiments-path)
      experiments_root="${2:-}"
      shift 2
      ;;
    --controller)
      controller="${2:-}"
      shift 2
      ;;
    --rename-controller-folder)
      rename_controller_folder=1
      shift
      ;;
    --rename-controller-files)
      rename_controller_files=1
      shift
      ;;
    --include-cmake)
      include_cmake=1
      shift
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

if [[ -z "$controllers_root" || -z "$experiments_root" || -z "$from" || -z "$to" ]]; then
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

controllers_root = Path("$controllers_root")
experiments_root = Path("$experiments_root")
controller = "$controller"
from_token = "$from"
to_token = "$to"
from_camel = "$from_camel" or (from_token[:1].upper() + from_token[1:])
to_camel = "$to_camel" or (to_token[:1].upper() + to_token[1:])
from_upper = "$from_upper" or from_token.upper()
to_upper = "$to_upper" or to_token.upper()
dry_run = $dry_run
rename_controller_folder = $rename_controller_folder
rename_controller_files = $rename_controller_files
include_cmake = $include_cmake

if not controllers_root.exists():
    print(f"Controllers path not found: {controllers_root}", file=sys.stderr)
    sys.exit(1)
if not experiments_root.exists():
    print(f"Experiments path not found: {experiments_root}", file=sys.stderr)
    sys.exit(1)

if controller:
    controller_path = controllers_root / controller
    if not controller_path.exists():
        print(f"Controller path not found: {controller_path}", file=sys.stderr)
        sys.exit(1)
else:
    matches = [p for p in controllers_root.iterdir() if p.is_dir() and from_token in p.name]
    if len(matches) == 0:
        print(f"No controller folders contain '{from_token}' under {controllers_root}", file=sys.stderr)
        sys.exit(1)
    if len(matches) > 1:
        names = ", ".join(sorted(p.name for p in matches))
        print(f"Multiple controller folders match '{from_token}': {names}", file=sys.stderr)
        print("Please pass --controller to disambiguate.", file=sys.stderr)
        sys.exit(1)
    controller_path = matches[0]
    controller = controller_path.name

new_controller = controller.replace(from_token, to_token)
experiments_file = experiments_root / f"{controller}.argos"
experiments_file_new = experiments_root / f"{new_controller}.argos"

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

def replace_file(path: Path) -> None:
    if not path.exists() or not path.is_file():
        return
    if is_binary(path):
        return
    try:
        original = path.read_text(encoding="utf-8", errors="surrogateescape")
    except OSError:
        return
    updated = original
    for src, dst in pairs:
        updated = updated.replace(src, dst)
    if updated == original:
        return
    if dry_run:
        print(f"DRY-RUN: {path}")
    else:
        path.write_text(updated, encoding="utf-8", errors="surrogateescape")
        print(f"UPDATED: {path}")

def rename_path(src: Path, dst: Path) -> None:
    if src == dst:
        return
    if dry_run:
        print(f"DRY-RUN RENAME: {src} -> {dst}")
    else:
        src.rename(dst)
        print(f"RENAMED: {src} -> {dst}")

if rename_controller_folder and new_controller != controller:
    rename_path(controller_path, controllers_root / new_controller)
    controller_path = controllers_root / new_controller
    if experiments_file.exists():
        rename_path(experiments_file, experiments_file_new)
    experiments_file = experiments_file_new

if rename_controller_files:
    files = [p for p in controller_path.iterdir() if p.is_file() and from_token in p.name]
    files.sort(key=lambda p: len(p.name), reverse=True)
    for path in files:
        new_path = path.with_name(path.name.replace(from_token, to_token))
        rename_path(path, new_path)

for path in controller_path.rglob("*"):
    if path.suffix in {".h", ".hpp", ".cpp", ".c"}:
        replace_file(path)

replace_file(experiments_file)

if include_cmake:
    replace_file(controllers_root / "CMakeLists.txt")
    replace_file(controller_path / "CMakeLists.txt")
PY
