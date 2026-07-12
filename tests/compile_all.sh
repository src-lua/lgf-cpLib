#!/bin/bash
# ============================================================
#  Lua's Notebook — Compile check
#    Compila (syntax-only) cada header de lib/ isoladamente.
#    Pega a classe de bug "nem compila" (paste, ; faltando...).
#    Uso: ./compile_all.sh [--quiet]
# ============================================================

set -u
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR/.." || exit 1

QUIET=0
[ "${1:-}" = "--quiet" ] && QUIET=1
CXX="${CXX:-g++}"

# Cores, spinner e run_step compartilhados (spin respeita QUIET).
source "$SCRIPT_DIR/../scripts/common.sh"
trap spin_stop EXIT

# Header (so standalone)
if [ $QUIET -eq 0 ]; then
  printf "\n${PURPLE}╔══════════════════════════════╗${NC}\n"
  printf "${PURPLE}║ 🌙 Notebook — Compile check  ║${NC}\n"
  printf "${PURPLE}╚══════════════════════════════╝${NC}\n\n"
fi

headers=$(find lib -name '*.hpp' | sort)
total=$(echo "$headers" | wc -l | tr -d ' ')
declare -a bad=()

spin_start "compilando $total headers"
while IFS= read -r f; do
  err=$($CXX -std=c++17 -fsyntax-only -x c++ "$f" 2>&1)
  echo "$err" | grep -qi "error" || continue
  bad+=("$f")
  if [ $QUIET -eq 0 ]; then
    spin_stop
    printf "${CLR}  ${RED}✗${NC} %s\n" "$f"
    echo "$err" | grep -i "error" | head -3 | sed 's/^/      /'
    spin_start "compilando $total headers"
  else
    printf "COMPILE FAIL %s\n" "$f"
    echo "$err" | grep -i "error" | head -3 | sed 's/^/    /'
  fi
done <<< "$headers"
spin_stop

# Resultado
if [ ${#bad[@]} -eq 0 ]; then
  [ $QUIET -eq 0 ] && printf "${CLR}  ${GREEN}✓${NC} todos os %s headers compilam\n\n" "$total"
  exit 0
else
  [ $QUIET -eq 0 ] && printf "\n  ${RED}%d de %d headers falharam${NC}\n\n" "${#bad[@]}" "$total"
  exit 1
fi
