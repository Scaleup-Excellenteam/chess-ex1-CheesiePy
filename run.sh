#!/usr/bin/env bash
set -euo pipefail

##############################################################################
# CONFIG
##############################################################################
BUILD_DIR="build"          # out-of-tree build folder
SRC_DIR="$(dirname "$0")/Chess"        # path to CMakeLists.txt

##############################################################################
# Optional: wipe the old build for a clean compile
##############################################################################
echo "--- Wiping old build directory ---"
rm -rf "$BUILD_DIR"

##############################################################################
# 1. Configure
##############################################################################
echo "--- Configuring CMake ---"
cmake -S "$SRC_DIR" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release

##############################################################################
# 2. Build (parallel if we can detect CPU cores)
##############################################################################
echo "--- Building Project ---"
case "$(uname -s)" in
  Linux*)  JOBS=$(nproc) ;;
  Darwin*) JOBS=$(sysctl -n hw.ncpu) ;;
  *)       JOBS=1 ;;
esac

# This command builds ALL executables defined in your CMakeLists.txt
# (both 'Chess' and 'run_tests')
cmake --build "$BUILD_DIR" --parallel "$JOBS"

##############################################################################
# 3. Run the correct executable based on the script's argument
##############################################################################

# If the first argument to the script is "test", run the test executable.
if [[ "${1:-}" == "test" ]]; then
    TEST_EXE_PATH="$BUILD_DIR/run_tests"
    echo "--- Locating Test Executable ---"
    if [[ -x "$TEST_EXE_PATH" ]]; then
        echo "▶️  Running C++ tests..."
        exec "$TEST_EXE_PATH"
    else
        echo "❌ Could not find the test executable at $TEST_EXE_PATH"
        exit 1
    fi
else
    # Otherwise, run the main game executable as default.
    echo "--- Locating Main Game Executable ---"
    exe_path=""
    args=("$@")  # Capture any additional arguments for the main game

    # Single-config generators (Ninja, Makefiles)
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

    echo "▶️  Running main game: $exe_path ..."
    exec "$exe_path" "${args[@]}"
fi

echo "✅  Run completed successfully."