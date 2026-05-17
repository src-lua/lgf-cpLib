#!/bin/bash
# ============================================
# 🌙 Lua's Notebook Generator
# 🦖 Inspired by SamuellH12's notebook generator
# ============================================

GREEN='\033[0;32m'
YELLOW='\033[0;33m'
RED='\033[0;31m'
PURPLE='\033[38;5;135m'
GOLD='\033[38;5;220m'
NC='\033[0m'

cmd_pid=""
frames=('⠋' '⠙' '⠹' '⠸' '⠼' '⠴' '⠦' '⠧' '⠇' '⠏')

spin() {
    local msg="$1"
    local i=0
    while kill -0 "$cmd_pid" 2>/dev/null; do
        printf "\r\033[K${frames[$i]} %s" "$msg" > /dev/tty
        i=$(( (i+1) % ${#frames[@]} ))
        sleep 0.08
    done
}

run_step() {
    local msg="$1"
    shift

    "$@" > /dev/null 2>&1 &
    cmd_pid=$!
    spin "$msg"
    wait "$cmd_pid"; local status=$?
    cmd_pid=""

    if [ $status -eq 0 ]; then
        printf "\r\033[K${GREEN}✓${NC} %s\n" "$msg" > /dev/tty
    else
        printf "\r\033[K${YELLOW}↻${NC} %s\n" "$msg" > /dev/tty
        "$@" > /dev/null 2>&1 &
        cmd_pid=$!
        spin "$msg"
        wait "$cmd_pid"; status=$?
        cmd_pid=""
        if [ $status -eq 0 ]; then
            printf "\r\033[K${GREEN}✓${NC} %s\n" "$msg" > /dev/tty
        else
            printf "\r\033[K${RED}✗${NC} %s — rode manualmente para ver detalhes\n" "$msg" > /dev/tty
            exit 1
        fi
    fi
}

run_xelatex() {
    local msg="$1"

    xelatex -halt-on-error -file-line-error notebook.tex > /dev/null 2>&1 &
    cmd_pid=$!
    spin "$msg"
    wait "$cmd_pid"; local status=$?
    cmd_pid=""

    if [ $status -eq 0 ]; then
        printf "\r\033[K${GREEN}✓${NC} %s\n" "$msg" > /dev/tty
    else
        printf "\r\033[K${YELLOW}↻${NC} %s\n" "$msg" > /dev/tty
        rm -f *.aux *.log *.out *.toc *.fdb_latexmk *.fls *.synctex.gz
        xelatex -halt-on-error -file-line-error notebook.tex > /dev/null 2>&1 &
        cmd_pid=$!
        spin "$msg"
        wait "$cmd_pid"; status=$?
        cmd_pid=""
        if [ $status -eq 0 ]; then
            printf "\r\033[K${GREEN}✓${NC} %s\n" "$msg" > /dev/tty
        else
            printf "\r\033[K${RED}✗${NC} %s — rode manualmente para ver detalhes\n" "$msg" > /dev/tty
            exit 1
        fi
    fi
}

cleanup() {
    [ -n "$cmd_pid" ] && kill "$cmd_pid" 2>/dev/null
    printf "\r\033[K${RED}✗${NC} Interrompido\n" > /dev/tty
    exit 1
}
trap cleanup INT TERM

printf "${PURPLE}=============================\n"
printf " 🌙 Lua's Notebook Generator \n"
printf "=============================${NC}\n\n"

OPENSSL=$(brew --prefix openssl)

run_step "Compilando gerador LaTeX" \
    g++ -std=c++17 -o generate_latex generate_latex.cpp -O2 -lcrypto \
        -Wno-deprecated-declarations \
        -I"$OPENSSL/include" -L"$OPENSSL/lib"

run_step "Gerando contents.tex" \
    ./generate_latex

run_xelatex "Compilando PDF (1a passagem)"
run_xelatex "Compilando PDF (2a passagem)"

run_step "Movendo PDF para ../print" \
    mv notebook.pdf ../print/notebook.pdf

printf "${GREEN}✓${NC} PDF disponível em ../print/notebook.pdf\n" > /dev/tty

rm -f generate_latex
rm -f *.aux *.log *.out *.toc *.fdb_latexmk *.fls *.synctex.gz
rm -rf temp/

printf "\n${GOLD}🌙 Good luck and good contest!${NC}\n\n" > /dev/tty
