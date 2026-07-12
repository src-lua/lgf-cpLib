#!/bin/bash
# ============================================================
#  Lua's Notebook Generator — Typst edition
# ============================================================

set -euo pipefail
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# Cores, spinner e run_step compartilhados.
source "$SCRIPT_DIR/../scripts/common.sh"

cleanup() {
  spin_stop
  rm -rf temp/
}
trap cleanup EXIT

# Args
BW=false
OUTPUT="../print/notebook.pdf"
for arg in "$@"; do
  case "$arg" in
    --p\&b|--pb|--bw) BW=true; OUTPUT="../print/notebook-bw.pdf" ;;
  esac
done

# Header
printf "\n${PURPLE}╔══════════════════════════════╗${NC}\n"
printf "${PURPLE}║ 🌙 Lua's Notebook Generator  ║${NC}\n"
printf "${PURPLE}╚══════════════════════════════╝${NC}\n\n"
$BW && printf "  ${YELLOW}Modo preto e branco ativado${NC}\n\n"

# Compila o gerador Rust, gera o contents.typ e compila o PDF.
run_step "Compilando gerador Rust" \
  cargo build --release --manifest-path Cargo.toml

run_step "Gerando contents.typ" \
  ./target/release/notebook-gen

TYPST_ENTRY="notebook.typ"
$BW && TYPST_ENTRY="notebook-bw.typ"

run_step "Compilando PDF" \
  typst compile --root .. --input bw="$BW" "$TYPST_ENTRY" "$OUTPUT"

# Done
printf "\n  ${GREEN}PDF disponivel em: ${OUTPUT#../}${NC}\n"
printf "\n\033[1m${GOLD}🌙 Good luck and good contest!${NC}\n\n"
