#!/bin/bash
# ============================================================
#  Lua's Notebook — Format check
#    Valida o limite de colunas dos fontes de lib/.
#    Standalone: aceita arquivos/diretorios e limite custom.
#    Uso: ./check_format.sh [--quiet] [-n N] [alvo...]
# ============================================================

set -u
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

MAX_COLS=65
QUIET=0
declare -a TARGETS=()

# Args
usage() { sed -n '2,7p' "${BASH_SOURCE[0]}" | sed 's/^#\{0,1\} \{0,1\}//'; }
while [ $# -gt 0 ]; do
  case "$1" in
    -q|--quiet)    QUIET=1; shift ;;
    -n|--max-cols) MAX_COLS="$2"; shift 2 ;;
    -h|--help)     usage; exit 0 ;;
    -*) echo "opcao desconhecida: $1" >&2; exit 2 ;;
    *)  TARGETS+=("$1"); shift ;;
  esac
done
[ ${#TARGETS[@]} -eq 0 ] && TARGETS=("$ROOT/lib")

# Cores e spinner compartilhados (spin respeita QUIET).
source "$SCRIPT_DIR/../scripts/common.sh"
trap spin_stop EXIT

# Diretorios viram fontes (.hpp/.cpp/.sh); arquivos passam direto.
collect_files() {
  local t
  for t in "${TARGETS[@]}"; do
    if [ -d "$t" ]; then
      find "$t" -type f \
        \( -name '*.hpp' -o -name '*.cpp' -o -name '*.sh' \) \
        -print0
    elif [ -f "$t" ]; then
      printf '%s\0' "$t"
    else
      printf "COLLECT FAIL %s (nao encontrado)\n" "$t" >&2
    fi
  done
}

# Header (só standalone)
if [ $QUIET -eq 0 ]; then
  printf "\n${PURPLE}╔══════════════════════════════╗${NC}\n"
  printf "${PURPLE}║ 🌙 Notebook — Format check   ║${NC}\n"
  printf "${PURPLE}╚══════════════════════════════╝${NC}\n\n"
fi

total=0
bad=0
spin_start "validando fontes (<= $MAX_COLS colunas)"
while IFS= read -r -d '' file; do
  total=$((total + 1))
  rel="${file#"$ROOT"/}"
  line_no=0
  while IFS= read -r line || [ -n "$line" ]; do
    line_no=$((line_no + 1))
    # Includes nao podem ser quebrados como C++ comum.
    [[ "$line" =~ ^[[:space:]]*#include[[:space:]] ]] && continue
    [ "${#line}" -le "$MAX_COLS" ] && continue

    bad=$((bad + 1))
    if [ $QUIET -eq 0 ]; then
      spin_stop
      printf "${CLR}  ${RED}✗${NC} %s:%d ${DIM}(%d > %d)${NC}\n" \
        "$rel" "$line_no" "${#line}" "$MAX_COLS"
      spin_start "validando fontes (<= $MAX_COLS colunas)"
    else
      printf "FORMAT FAIL %s:%d (%d > %d)\n" \
        "$rel" "$line_no" "${#line}" "$MAX_COLS"
    fi
  done < "$file"
done < <(collect_files | sort -z)
spin_stop

# Resultado
if [ "$bad" -eq 0 ]; then
  [ $QUIET -eq 0 ] && printf "${CLR}  ${GREEN}✓${NC} %d fonte(s), tudo <= %d colunas\n\n" "$total" "$MAX_COLS"
  exit 0
else
  [ $QUIET -eq 0 ] && printf "\n  ${RED}%d linha(s) acima de %d colunas${NC}\n\n" "$bad" "$MAX_COLS"
  exit 1
fi
