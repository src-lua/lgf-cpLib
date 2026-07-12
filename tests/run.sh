#!/bin/bash
# ============================================================
#  Lua's Notebook — Test Suite
#    1) format check (colunas)
#    2) compile-check de todos os headers de lib/
#    3) stress tests (stress/ espelha a estrutura de lib/)
#
#  Aperte 's' para pular o compile check ou um stress em curso.
# ============================================================

set -u
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# Cores, spinner e run_step compartilhados.
source "$SCRIPT_DIR/../scripts/common.sh"

ROOT=".."
CXX_BIN="${CXX:-g++}"
CXX="$CXX_BIN -std=c++17 -O2"
BIN="$(mktemp)"
pass=0; fail=0
declare -a failed=()
declare -a skipped=()
SKIP_ENABLED=0
STTY_SAVED=""

cleanup() {
  spin_stop
  rm -f "$BIN"
  [ -n "$STTY_SAVED" ] && stty "$STTY_SAVED" 2>/dev/null
  return 0
}
trap cleanup EXIT

# Mata um processo e toda a sua árvore de descendentes (congela
# com STOP antes de descer para não perder filhos recém-criados).
kill_tree() {
  local p="$1" c
  kill -STOP "$p" 2>/dev/null
  for c in $(pgrep -P "$p" 2>/dev/null); do kill_tree "$c"; done
  kill -KILL "$p" 2>/dev/null
}

# Roda "$@" em background; se 's' for apertado (quando o skip
# está ativo), mata a árvore do processo e retorna 2. Caso
# contrário retorna o exit do comando. A saída fica em RUN_OUT.
#
# Lê a tecla com 'dd' (não com 'read -n1', que força leitura
# bloqueante e ignoraria o stty): com 'min 0 time 1' o dd
# retorna sozinho em ~0.1s se nada for digitado, ou na hora
# quando uma tecla chega. Assim o loop nunca fica preso.
run_skippable() {
  local tmp; tmp="$(mktemp)"
  "$@" > "$tmp" 2>&1 &
  local pid=$! key rc
  if [ "$SKIP_ENABLED" -eq 1 ]; then
    while kill -0 "$pid" 2>/dev/null; do
      key=$(dd bs=1 count=1 2>/dev/null)
      if [ "$key" = "s" ]; then
        kill_tree "$pid"; wait "$pid" 2>/dev/null
        RUN_OUT="$(cat "$tmp")"; rm -f "$tmp"
        return 2
      fi
    done
  fi
  wait "$pid"; rc=$?
  RUN_OUT="$(cat "$tmp")"; rm -f "$tmp"
  return $rc
}

# Header
printf "\n${PURPLE}╔══════════════════════════════╗${NC}\n"
printf "${PURPLE}║ 🌙 Lua's Notebook — Tests    ║${NC}\n"
printf "${PURPLE}╚══════════════════════════════╝${NC}\n\n"

# Leitura de tecla não-bloqueante para o skip (só em terminal).
if [ "$TTY" -eq 1 ] && [ -t 0 ]; then
  STTY_SAVED="$(stty -g 2>/dev/null || true)"
  [ -n "$STTY_SAVED" ] && stty -echo -icanon min 0 time 1 \
    2>/dev/null && SKIP_ENABLED=1
fi

# Format check
printf "${GOLD}▸ Format check${NC}"
[ "$SKIP_ENABLED" -eq 1 ] && printf "  ${DIM}(s = pular)${NC}"
printf "\n"
spin_start "validando colunas" "  "
run_skippable bash check_format.sh --quiet; frc=$?
spin_stop
if [ $frc -eq 2 ]; then
  printf "${CLR}  ${YELLOW}⊘${NC} format check ${DIM}(pulado)${NC}\n"
  skipped+=("format-check")
elif [ $frc -eq 0 ]; then
  printf "${CLR}  ${GREEN}✓${NC} código limitado a 65 colunas\n"
else
  printf "${CLR}  ${RED}✗${NC} linhas acima de 65 colunas\n"
  echo "$RUN_OUT" | sed 's/^/    /'
  fail=$((fail + 1))
fi

# Compile check
printf "\n${GOLD}▸ Compile check${NC}"
[ "$SKIP_ENABLED" -eq 1 ] && printf "  ${DIM}(s = pular)${NC}"
printf "\n"
spin_start "compilando todos os headers" "  "
run_skippable bash compile_all.sh --quiet; crc=$?
spin_stop
if [ $crc -eq 2 ]; then
  printf "${CLR}  ${YELLOW}⊘${NC} compile check ${DIM}(pulado)${NC}\n"
  skipped+=("compile-check")
elif [ $crc -eq 0 ]; then
  nh=$(cd "$ROOT" && find lib -name '*.hpp' | wc -l | tr -d ' ')
  printf "${CLR}  ${GREEN}✓${NC} todos os headers compilam ${DIM}(${nh})${NC}\n"
else
  printf "${CLR}  ${RED}✗${NC} headers com erro de compilação\n"
  echo "$RUN_OUT" | sed 's/^/    /'
  fail=$((fail + 1))
fi

# Stress tests
printf "\n${GOLD}▸ Stress tests${NC}"
[ "$SKIP_ENABLED" -eq 1 ] && printf "  ${DIM}(s = pular)${NC}"
printf "\n"
last_section=""
for src in $(find stress -name '*.cpp' | sort); do
  name="${src#stress/}"; name="${name%.cpp}"
  section="${name%%/*}"
  label="${name#*/}"; [ "$label" = "$name" ] && label="$name"

  if [ "$section" != "$last_section" ]; then
    printf "  ${PURPLE}%s${NC}\n" "$section"
    last_section="$section"
  fi

  spin_start "$label" "    "

  run_skippable $CXX -I "$ROOT" "$src" -o "$BIN"; brc=$?
  if [ $brc -eq 2 ]; then
    spin_stop
    printf "${CLR}    ${YELLOW}⊘${NC} %s ${DIM}(pulado)${NC}\n" "$label"
    skipped+=("$name"); continue
  fi
  if [ $brc -ne 0 ]; then
    spin_stop
    printf "${CLR}    ${RED}✗${NC} %s ${DIM}(build)${NC}\n" "$label"
    echo "$RUN_OUT" | grep -i "error" | head -3 | sed 's/^/        /'
    failed+=("$name"); fail=$((fail + 1)); continue
  fi

  run_skippable "$BIN"; rrc=$?
  if [ $rrc -eq 2 ]; then
    spin_stop
    printf "${CLR}    ${YELLOW}⊘${NC} %s ${DIM}(pulado)${NC}\n" "$label"
    skipped+=("$name")
  elif [ $rrc -eq 0 ]; then
    spin_stop
    printf "${CLR}    ${GREEN}✓${NC} %s\n" "$label"
    pass=$((pass + 1))
  else
    spin_stop
    printf "${CLR}    ${RED}✗${NC} %s\n" "$label"
    echo "$RUN_OUT" | tail -4 | sed 's/^/        /'
    failed+=("$name"); fail=$((fail + 1))
  fi
done

[ "$SKIP_ENABLED" -eq 1 ] && { stty "$STTY_SAVED" 2>/dev/null; STTY_SAVED=""; }

# Footer
printf "\n"
nskip=${#skipped[@]}
if [ $fail -eq 0 ]; then
  printf "  ${GREEN}✓ %d testes passaram${NC}" "$pass"
  [ $nskip -gt 0 ] && printf "   ${YELLOW}%d pulados${NC}" "$nskip"
  printf "\n\n\033[1m${GOLD}🌙 Tudo verde. Boa prova!${NC}\n\n"
else
  printf "  ${GREEN}%d ok${NC}   ${RED}%d falhou${NC}" "$pass" "$fail"
  [ $nskip -gt 0 ] && printf "   ${YELLOW}%d pulados${NC}" "$nskip"
  printf "\n"
  for n in "${failed[@]}"; do printf "    ${RED}✗${NC} %s\n" "$n"; done
  printf "\n"
  exit 1
fi
