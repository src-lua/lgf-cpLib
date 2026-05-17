#!/bin/bash
# ============================================================
#  Lua's Notebook Generator — Typst edition
# ============================================================

set -euo pipefail
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

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
  rm -rf temp/
}
trap cleanup EXIT

# ── Args ──────────────────────────────────────────────────────────────────────
BW=false
OUTPUT="../print/notebook.pdf"
for arg in "$@"; do
  case "$arg" in
    --p\&b|--pb|--bw) BW=true; OUTPUT="../print/notebook-bw.pdf" ;;
  esac
done

# ── Header ────────────────────────────────────────────────────────────────────
printf "\n${PURPLE}╔══════════════════════════════╗${NC}\n"
printf "${PURPLE}║ 🌙 Lua's Notebook Generator  ║${NC}\n"
printf "${PURPLE}╚══════════════════════════════╝${NC}\n\n"
$BW && printf "  ${YELLOW}Modo preto e branco ativado${NC}\n\n"

# ── Build Rust generator ──────────────────────────────────────────────────────
run_step "Compilando gerador Rust" \
  cargo build --release --manifest-path Cargo.toml

# ── Run generator (produces contents.typ + temp/) ────────────────────────────
run_step "Gerando contents.typ" \
  ./target/release/notebook-gen

# ── Compile with Typst ────────────────────────────────────────────────────────
TYPST_ENTRY="notebook.typ"
$BW && TYPST_ENTRY="notebook-bw.typ"

run_step "Compilando PDF" \
  typst compile --input bw="$BW" "$TYPST_ENTRY" "$OUTPUT"

# ── Done ──────────────────────────────────────────────────────────────────────
printf "\n  ${GREEN}PDF disponivel em: ${OUTPUT#../}${NC}\n"
printf "\n\033[1m${GOLD}🌙 Good luck and good contest!${NC}\n\n"
