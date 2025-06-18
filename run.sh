#!/usr/bin/env bash
set -euo pipefail

##############################################################################
# CONFIG
##############################################################################
BUILD_DIR="build"
SRC_DIR="$(dirname "$0")/Chess"

##############################################################################
# Build Process
##############################################################################
echo "--- Wiping and Rebuilding Project ---"
rm -rf "$BUILD_DIR"
cmake -S "$SRC_DIR" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release
cmake --build "$BUILD_DIR" --parallel "$(nproc || sysctl -n hw.ncpu || echo 1)"

##############################################################################
# Run Logic
##############################################################################
ARGUMENT="${1:-game}" # Default to 'game' if no argument is provided

if [[ "$ARGUMENT" == "test" ]]; then
    # Run the checkmate test
    echo "▶️  Running Checkmate test..."
    exec "$BUILD_DIR/run_tests"
elif [[ "$ARGUMENT" == "check" ]]; then
    # Run the check test
    echo "▶️  Running Check Condition test..."
    exec "$BUILD_DIR/run_check_test"
elif [[ "$ARGUMENT" == "castling" ]]; then
    # Run the new castling test
    echo "▶️  Running Castling test..."
    exec "$BUILD_DIR/run_castling_test"
else
    # Run the main game by default
    echo "▶️  Running main game..."
    exec "$BUILD_DIR/Chess"
fi

echo "✅ Run completed."