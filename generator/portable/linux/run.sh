#!/bin/bash
# ============================================================
#  Lua's Notebook Generator — portable edition (Linux x86_64)
#    Só define os caminhos deste OS; a lógica vem de common.sh.
# ============================================================

set -euo pipefail
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PORTABLE_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
REPO_DIR="$(cd "$PORTABLE_DIR/../.." && pwd)"
BIN_DIR="$SCRIPT_DIR/bin"
FONT_DIR="$PORTABLE_DIR/fonts"
OS_LABEL="Linux x86_64 Portable Edition"

source "$PORTABLE_DIR/common.sh"
portable_main "$@"
