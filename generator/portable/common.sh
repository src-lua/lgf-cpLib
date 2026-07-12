# ============================================================
#  Lua's Notebook Generator — lógica do portable
#
#  Feito para ser "sourced". Cada <os>/run.sh define os caminhos
#  específicos e chama portable_main:
#
#    REPO_DIR   raiz do repositório (contém lib/ e generator/)
#    BIN_DIR    dir com os binários notebook-gen e typst
#    FONT_DIR   dir com as fontes JetBrains Mono
#    OS_LABEL   texto do header (ex: "macOS Portable Edition")
#    portable_main "$@"
#
#  Os helpers genéricos (cores, spinner, run_step) vêm do
#  scripts/common.sh na raiz do repo.
# ============================================================

source "$REPO_DIR/scripts/common.sh"

cleanup() {
  spin_stop
  [ -n "${WORK_DIR:-}" ] && rm -rf "$WORK_DIR"
}

portable_main() {
  local BW=false
  local OUTPUT="$REPO_DIR/print/notebook.pdf"
  for arg in "$@"; do
    case "$arg" in
      --p\&b|--pb|--bw)
        BW=true; OUTPUT="$REPO_DIR/print/notebook-bw.pdf" ;;
    esac
  done

  printf "\n${PURPLE}╔══════════════════════════════╗${NC}\n"
  printf "${PURPLE}║ 🌙 Lua's Notebook Generator  ║${NC}\n"
  printf "${PURPLE}╚══════════════════════════════╝${NC}\n"
  printf "     ${GOLD}(%s)${NC}\n\n" "${OS_LABEL:-Portable Edition}"
  $BW && printf "  ${YELLOW}Modo preto e branco ativado${NC}\n\n"

  # Recria a estrutura esperada pelo generator num dir temporário.
  WORK_DIR="$(mktemp -d)"
  trap cleanup EXIT
  mkdir -p "$WORK_DIR/generator" "$WORK_DIR/lib"
  cp -r "$REPO_DIR/generator/." "$WORK_DIR/generator/"
  cp -r "$REPO_DIR/lib/." "$WORK_DIR/lib/"
  cd "$WORK_DIR/generator"

  run_step "Gerando contents.typ" "$BIN_DIR/notebook-gen"

  local TYPST_ENTRY="notebook.typ"
  $BW && TYPST_ENTRY="notebook-bw.typ"
  run_step "Compilando PDF" \
    env TYPST_FONT_PATHS="$FONT_DIR" \
    "$BIN_DIR/typst" compile --root .. --input bw="$BW" \
    "$TYPST_ENTRY" "$OUTPUT"

  printf "\n  ${GREEN}PDF disponivel em: %s${NC}\n" "$OUTPUT"
  printf "\n\033[1m${GOLD}🌙 Good luck and good contest!${NC}\n\n"
}
