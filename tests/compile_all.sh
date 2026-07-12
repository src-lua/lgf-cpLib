#!/bin/bash
# ============================================================
#  Lua's Notebook — Compile check
#    Compila (syntax-only) cada header de lib/ isoladamente.
#    Pega a classe de bug "nem compila" (paste acidental, ; faltando...).
#    Uso: ./compile_all.sh [--quiet]
# ============================================================

set -u
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR/.." || exit 1   # raiz do repo

GREEN='\033[0;32m'
YELLOW='\033[0;33m'
RED='\033[0;31m'
PURPLE='\033[38;5;135m'
GOLD='\033[38;5;220m'
DIM='\033[2m'
NC='\033[0m'
CLR='\r\033[2K'

QUIET=0
[ "${1:-}" = "--quiet" ] && QUIET=1
if [ -t 1 ]; then TTY=1; else TTY=0; CLR=""; fi

# ── Spinner ───────────────────────────────────────────────────────────────────
spin_pid=""
spin() {
  local frames=('⠋' '⠙' '⠹' '⠸' '⠼' '⠴' '⠦' '⠧' '⠇' '⠏')
  local i=0
  while true; do
    printf "\r  ${YELLOW}${frames[$i]}${NC} %s" "$1"
    i=$(( (i + 1) % ${#frames[@]} ))
    sleep 0.08
  done
}
start_spin() { { [ $QUIET -eq 1 ] || [ $TTY -eq 0 ]; } && return 0; spin "$1" & spin_pid=$!; }
stop_spin() {
  [ -n "$spin_pid" ] && { kill "$spin_pid" 2>/dev/null; wait "$spin_pid" 2>/dev/null || true; spin_pid=""; }
}
trap stop_spin EXIT

# ── Header (só standalone) ────────────────────────────────────────────────────
if [ $QUIET -eq 0 ]; then
  printf "\n${PURPLE}╔══════════════════════════════╗${NC}\n"
  printf "${PURPLE}║ 🌙 Notebook — Compile check  ║${NC}\n"
  printf "${PURPLE}╚══════════════════════════════╝${NC}\n\n"
fi

headers=$(find lib -name '*.hpp' | sort)
total=$(echo "$headers" | wc -l | tr -d ' ')
declare -a bad=()

start_spin "compilando $total headers"
while IFS= read -r f; do
  err=$(g++ -std=c++17 -fsyntax-only -x c++ "$f" 2>&1)
  echo "$err" | grep -qi "error" || continue
  bad+=("$f")
  if [ $QUIET -eq 0 ]; then
    stop_spin
    printf "${CLR}  ${RED}✗${NC} %s\n" "$f"
    echo "$err" | grep -i "error" | head -3 | sed 's/^/      /'
    start_spin "compilando $total headers"
  else
    printf "COMPILE FAIL %s\n" "$f"
    echo "$err" | grep -i "error" | head -3 | sed 's/^/    /'
  fi
done <<< "$headers"
stop_spin

# ── Resultado ─────────────────────────────────────────────────────────────────
if [ ${#bad[@]} -eq 0 ]; then
  [ $QUIET -eq 0 ] && printf "${CLR}  ${GREEN}✓${NC} todos os %s headers compilam\n\n" "$total"
  exit 0
else
  [ $QUIET -eq 0 ] && printf "\n  ${RED}%d de %d headers falharam${NC}\n\n" "${#bad[@]}" "$total"
  exit 1
fi
