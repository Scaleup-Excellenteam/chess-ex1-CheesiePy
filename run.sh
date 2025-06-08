#!/usr/bin/env bash
set -euo pipefail

##############################################################################
# CONFIG
##############################################################################
BUILD_DIR="build"          # out-of-tree build folder
SRC_DIR="$(dirname "$0")/Chess"        # path to CMakeLists.txt

##############################################################################
# Optional: wipe the old build (comment out for incremental rebuilds)
##############################################################################
rm -rf "$BUILD_DIR"

##############################################################################
# 1. configure
##############################################################################
cmake -S "$SRC_DIR" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release

##############################################################################
# 2. build (parallel if we can detect CPU cores)
##############################################################################
case "$(uname -s)" in
  Linux*)  JOBS=$(nproc) ;;
  Darwin*) JOBS=$(sysctl -n hw.ncpu) ;;
  *)       JOBS=1 ;;                   # Windows MSVC/NMake handles /MP itself
esac

cmake --build "$BUILD_DIR" --parallel "$JOBS"

##############################################################################
# 3. locate & run the executable
#    (Works for Ninja/Unix Makefiles and MSVC multi-config generators)
##############################################################################
exe_path=""

# Single-config generators (Ninja, Makefiles) place it right in $BUILD_DIR
if [[ -x "$BUILD_DIR/Chess" ]]; then
    exe_path="$BUILD_DIR/Chess"
elif [[ -x "$BUILD_DIR/Chess.exe" ]]; then
    exe_path="$BUILD_DIR/Chess.exe"
else
    # Multi-config (Visual Studio, Xcode): default to Release
    if [[ -x "$BUILD_DIR/Release/Chess.exe" ]]; then
        exe_path="$BUILD_DIR/Release/Chess.exe"
    elif [[ -x "$BUILD_DIR/Release/Chess" ]]; then
        exe_path="$BUILD_DIR/Release/Chess"
    fi
fi

if [[ -z "$exe_path" ]]; then
    echo "❌  Could not find the Chess executable after build."
    exit 1
fi

echo "▶️  Running $exe_path ..."
exec "$exe_path"
echo "✅  Build and run completed successfully."