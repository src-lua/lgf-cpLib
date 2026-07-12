#!/bin/bash
# ============================================================
#  Atualiza os binários do portable (linux + macos)
# ============================================================

set -euo pipefail
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
GENERATOR_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"

# Cores + spinner (com guard de TTY) compartilhados.
source "$GENERATOR_DIR/../scripts/common.sh"

printf "\n${PURPLE}Atualizando binários do portable...${NC}\n\n"

# macOS
printf "  ${YELLOW}macOS${NC}\n"

cd "$GENERATOR_DIR"
cargo build --release 2>&1 | grep -E "Compiling|Finished|error"
cp target/release/notebook-gen "$SCRIPT_DIR/macos/bin/notebook-gen"
printf "  ${GREEN}✓${NC} notebook-gen (macOS)\n"

rm -f "$SCRIPT_DIR/macos/bin/typst"
cp "$(realpath "$(which typst)")" "$SCRIPT_DIR/macos/bin/typst"
printf "  ${GREEN}✓${NC} typst $(typst --version | head -1) (macOS)\n"

# Linux x86_64 (musl)
printf "\n  ${YELLOW}Linux x86_64${NC}\n"

CARGO_TARGET_X86_64_UNKNOWN_LINUX_MUSL_LINKER=x86_64-linux-musl-gcc \
  cargo build --release --target x86_64-unknown-linux-musl 2>&1 | grep -E "Compiling|Finished|error"
cp target/x86_64-unknown-linux-musl/release/notebook-gen "$SCRIPT_DIR/linux/bin/notebook-gen"
printf "  ${GREEN}✓${NC} notebook-gen (Linux musl)\n"

TYPST_VERSION="$(typst --version | grep -oE '[0-9]+\.[0-9]+\.[0-9]+')"
TYPST_TMP="$(mktemp /tmp/typst-linux.XXXXXX.tar.xz)"
spin_start "Baixando typst v${TYPST_VERSION} para Linux"
curl -sL "https://github.com/typst/typst/releases/download/v${TYPST_VERSION}/typst-x86_64-unknown-linux-musl.tar.xz" -o "$TYPST_TMP"
spin_stop
rm -f "$SCRIPT_DIR/linux/bin/typst"
tar -xJf "$TYPST_TMP" --strip-components=1 -C "$SCRIPT_DIR/linux/bin/" "typst-x86_64-unknown-linux-musl/typst"
rm -f "$TYPST_TMP"
printf "${CLR}  ${GREEN}✓${NC} typst v${TYPST_VERSION} (Linux musl)\n"

printf "\n${GREEN}Portable atualizado!${NC}\n\n"
