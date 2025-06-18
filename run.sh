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
    echo "▶️  Running Checkmate test..."
    exec "$BUILD_DIR/run_tests"
elif [[ "$ARGUMENT" == "check" ]]; then
    echo "▶️  Running Check Condition test..."
    exec "$BUILD_DIR/run_check_test"
elif [[ "$ARGUMENT" == "castling" ]]; then
    echo "▶️  Running Castling test..."
    exec "$BUILD_DIR/run_castling_test"
elif [[ "$ARGUMENT" == "draw" ]]; then
    echo "▶️  Running Draw Condition test..."
    exec "$BUILD_DIR/run_draw_test"
elif [[ "$ARGUMENT" == "pvc" ]]; then
    # Run the new pvc test
    echo "▶️  Running Player vs. Computer test..."
    exec "$BUILD_DIR/run_pvc_test"
else
    # Run the main game by default
    echo "▶️  Running main game..."
    exec "$BUILD_DIR/Chess"
fi

echo "✅ Run completed."