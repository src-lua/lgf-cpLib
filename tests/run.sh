#!/bin/bash
# ============================================================
#  Lua's Notebook — Test Suite
#    1) compile-check de todos os headers de lib/
#    2) stress tests (stress/ espelha a estrutura de lib/)
# ============================================================

set -u
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

GREEN='\033[0;32m'
YELLOW='\033[0;33m'
RED='\033[0;31m'
PURPLE='\033[38;5;135m'
GOLD='\033[38;5;220m'
DIM='\033[2m'
NC='\033[0m'
CLR='\r\033[2K'

ROOT=".."
CXX="g++ -std=c++17 -O2"
BIN="$(mktemp)"
pass=0; fail=0
declare -a failed=()

# Só anima se a saída for um terminal (fora disso: log limpo, 1 linha por teste).
if [ -t 1 ]; then TTY=1; else TTY=0; CLR=""; fi

# ── Spinner ───────────────────────────────────────────────────────────────────
spin_pid=""
spin() {  # $1 = indentação (alinha o frame com o ✓), $2 = label
  local frames=('⠋' '⠙' '⠹' '⠸' '⠼' '⠴' '⠦' '⠧' '⠇' '⠏')
  local i=0
  while true; do
    printf "\r%s${YELLOW}%s${NC} %s" "$1" "${frames[$i]}" "$2"
    i=$(( (i + 1) % ${#frames[@]} ))
    sleep 0.08
  done
}
start_spin() { [ $TTY -eq 1 ] || return 0; spin "$1" "$2" & spin_pid=$!; }
stop_spin() {
  [ -n "$spin_pid" ] && { kill "$spin_pid" 2>/dev/null; wait "$spin_pid" 2>/dev/null || true; spin_pid=""; }
}
cleanup() { stop_spin; rm -f "$BIN"; }
trap cleanup EXIT

# ── Header ────────────────────────────────────────────────────────────────────
printf "\n${PURPLE}╔══════════════════════════════╗${NC}\n"
printf "${PURPLE}║ 🌙 Lua's Notebook — Tests    ║${NC}\n"
printf "${PURPLE}╚══════════════════════════════╝${NC}\n\n"

# ── Compile check ─────────────────────────────────────────────────────────────
printf "${GOLD}▸ Compile check${NC}\n"
start_spin "  " "compilando todos os headers"
cout=$(bash compile_all.sh --quiet 2>&1); crc=$?
stop_spin
if [ $crc -eq 0 ]; then
  nh=$(cd "$ROOT" && find lib -name '*.hpp' | wc -l | tr -d ' ')
  printf "${CLR}  ${GREEN}✓${NC} todos os headers compilam ${DIM}(${nh})${NC}\n"
else
  printf "${CLR}  ${RED}✗${NC} headers com erro de compilação\n"
  echo "$cout" | sed 's/^/    /'
  fail=$((fail + 1))
fi

# ── Stress tests ──────────────────────────────────────────────────────────────
printf "\n${GOLD}▸ Stress tests${NC}\n"
last_section=""
for src in $(find stress -name '*.cpp' | sort); do
  name="${src#stress/}"; name="${name%.cpp}"
  section="${name%%/*}"
  label="${name#*/}"; [ "$label" = "$name" ] && label="$name"

  if [ "$section" != "$last_section" ]; then
    printf "  ${PURPLE}%s${NC}\n" "$section"
    last_section="$section"
  fi

  start_spin "    " "$label"
  if ! out=$($CXX -I "$ROOT" "$src" -o "$BIN" 2>&1); then
    stop_spin
    printf "${CLR}    ${RED}✗${NC} %s ${DIM}(build)${NC}\n" "$label"
    echo "$out" | grep -i "error" | head -3 | sed 's/^/        /'
    failed+=("$name"); fail=$((fail + 1)); continue
  fi
  if runout=$("$BIN" 2>&1); then
    stop_spin
    printf "${CLR}    ${GREEN}✓${NC} %s\n" "$label"
    pass=$((pass + 1))
  else
    stop_spin
    printf "${CLR}    ${RED}✗${NC} %s\n" "$label"
    echo "$runout" | tail -4 | sed 's/^/        /'
    failed+=("$name"); fail=$((fail + 1))
  fi
done

# ── Footer ────────────────────────────────────────────────────────────────────
printf "\n"
if [ $fail -eq 0 ]; then
  printf "  ${GREEN}✓ %d testes passaram${NC}\n" "$pass"
  printf "\n\033[1m${GOLD}🌙 Tudo verde. Boa prova!${NC}\n\n"
else
  printf "  ${GREEN}%d ok${NC}   ${RED}%d falhou${NC}\n" "$pass" "$fail"
  for n in "${failed[@]}"; do printf "    ${RED}✗${NC} %s\n" "$n"; done
  printf "\n"
  exit 1
fi
