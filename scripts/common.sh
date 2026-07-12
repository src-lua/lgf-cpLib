# ============================================================
#  Lua's Notebook — helpers de shell compartilhados
#
#  Feito para ser "sourced" pelos scripts de tests/ e generator/.
#  Fornece cores, deteccao de TTY, spinner e run_step.
#  Defina QUIET=1 antes do source para silenciar o spinner.
# ============================================================

GREEN='\033[0;32m'
YELLOW='\033[0;33m'
RED='\033[0;31m'
PURPLE='\033[38;5;135m'
GOLD='\033[38;5;220m'
DIM='\033[2m'
NC='\033[0m'
CLR='\r\033[2K'
if [ -t 1 ]; then TTY=1; else TTY=0; CLR=""; fi

# Spinner (anima so em TTY e fora do modo QUIET)
spin_pid=""
_spin_loop() { # $1 = label, $2 = indentacao
  local frames=('⠋' '⠙' '⠹' '⠸' '⠼' '⠴' '⠦' '⠧' '⠇' '⠏')
  local i=0
  while true; do
    printf "\r%s${YELLOW}%s${NC} %s" "$2" "${frames[$i]}" "$1"
    i=$(( (i + 1) % ${#frames[@]} ))
    sleep 0.08
  done
}
spin_start() { # $1 = label, $2 = indentacao (default "  ")
  [ "${QUIET:-0}" -eq 1 ] && return 0
  [ "${TTY:-0}" -eq 1 ] || return 0
  _spin_loop "$1" "${2:-  }" &
  spin_pid=$!
}
spin_stop() {
  [ -n "$spin_pid" ] || return 0
  kill "$spin_pid" 2>/dev/null || true
  wait "$spin_pid" 2>/dev/null || true
  spin_pid=""
}

# run_step "label" cmd args... — roda um passo com spinner e
# ✓/✗; em caso de falha, re-roda com output e sai com 1.
run_step() {
  local label="$1"; shift
  spin_start "$label"
  if "$@" > /dev/null 2>&1; then
    spin_stop
    printf "${CLR}  ${GREEN}✓${NC} %s\n" "$label"
  else
    spin_stop
    printf "${CLR}  ${RED}✗${NC} %s\n" "$label"
    echo ""
    echo "  Rerunning with output for diagnostics:"
    "$@"
    exit 1
  fi
}
