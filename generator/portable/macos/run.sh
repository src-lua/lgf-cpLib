#!/bin/bash
# ============================================================
#  Lua's Notebook Generator — portable edition (macOS)
# ============================================================

set -euo pipefail
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

GREEN='\033[0;32m'
YELLOW='\033[0;33m'
RED='\033[0;31m'
PURPLE='\033[38;5;135m'
GOLD='\033[38;5;220m'
NC='\033[0m'

# ── Spinner ───────────────────────────────────────────────────────────────────
spin_pid=""
spin() {
  local frames=('⠋' '⠙' '⠹' '⠸' '⠼' '⠴' '⠦' '⠧' '⠇' '⠏')
  local i=0
  while true; do
    printf "\r  ${YELLOW}${frames[$i]}${NC} %s..." "$1"
    i=$(( (i+1) % ${#frames[@]} ))
    sleep 0.08
  done
}

run_step() {
  local label="$1"; shift
  spin "$label" &
  spin_pid=$!
  if "$@" > /dev/null 2>&1; then
    kill $spin_pid 2>/dev/null; wait $spin_pid 2>/dev/null || true
    printf "\r  ${GREEN}✓${NC} %s\n" "$label"
  else
    kill $spin_pid 2>/dev/null; wait $spin_pid 2>/dev/null || true
    printf "\r  ${RED}✗${NC} %s\n" "$label"
    echo ""
    echo "  Rerunning with output for diagnostics:"
    "$@"
    exit 1
  fi
  spin_pid=""
}

cleanup() {
  [ -n "$spin_pid" ] && kill "$spin_pid" 2>/dev/null || true
  rm -rf "$WORK_DIR"
}

# ── Args ──────────────────────────────────────────────────────────────────────
BW=false
PORTABLE_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
REPO_DIR="$(cd "$PORTABLE_DIR/../.." && pwd)"
OUTPUT="$REPO_DIR/print/notebook.pdf"
for arg in "$@"; do
  case "$arg" in
    --p\&b|--pb|--bw) BW=true; OUTPUT="$REPO_DIR/print/notebook-bw.pdf" ;;
  esac
done

# ── Header ────────────────────────────────────────────────────────────────────
printf "\n${PURPLE}╔══════════════════════════════╗${NC}\n"
printf "${PURPLE}║ 🌙 Lua's Notebook Generator  ║${NC}\n"
printf "${PURPLE}╚══════════════════════════════╝${NC}\n\n"
$BW && printf "  ${YELLOW}Modo preto e branco ativado${NC}\n\n"

# ── Setup work dir ────────────────────────────────────────────────────────────
WORK_DIR="$(mktemp -d)"
trap cleanup EXIT

# Recria estrutura esperada pelo generator: work_dir/generator/ + work_dir/lib/
mkdir -p "$WORK_DIR/generator" "$WORK_DIR/lib"
cp -r "$REPO_DIR/generator/." "$WORK_DIR/generator/"
cp -r "$REPO_DIR/lib/." "$WORK_DIR/lib/"
cd "$WORK_DIR/generator"

# ── Run generator ─────────────────────────────────────────────────────────────
run_step "Gerando contents.typ" \
  "$SCRIPT_DIR/bin/notebook-gen"

# ── Compile with Typst ────────────────────────────────────────────────────────
TYPST_ENTRY="notebook.typ"
$BW && TYPST_ENTRY="notebook-bw.typ"

run_step "Compilando PDF" \
  "$SCRIPT_DIR/bin/typst" compile --input bw="$BW" "$TYPST_ENTRY" "$OUTPUT"

# ── Done ──────────────────────────────────────────────────────────────────────
printf "\n  ${GREEN}PDF disponivel em: %s${NC}\n" "$OUTPUT"
printf "\n\033[1m${GOLD}🌙 Good luck and good contest!${NC}\n\n"
