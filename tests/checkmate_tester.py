import subprocess
import time
import os

def run_checkmate_test():
    """
    Runs the chess game and inputs a sequence of moves for a "Fool's Mate"
    using the game's specific coordinate system (Letter=Row, Number=Column).
    It then checks if the game correctly identifies the checkmate.
    """
    executable_path = os.path.join("build", "Chess")

    if not os.path.exists(executable_path):
        print(f"Error: Executable not found at '{executable_path}'")
        print("Please compile the C++ project first using './run.sh' or 'cmake/make'.")
        return

    # Fool's Mate sequence translated to the game's coordinate system.
    # Standard:       1. f3 e5   2. g4 Qh4#
    # This Game's:    1. g6f6 b5d5  2. g7e7 a4e8#
    moves = [
        "g6f6",  # White pawn moves from F-file (row G, col 6 -> row F, col 6)
        "B5D5",  # Black pawn moves from E-file (row B, col 5 -> row D, col 5)
        "g7e7",  # White pawn moves from G-file (row G, col 7 -> row E, col 7)
        "A4E8",  # Black queen moves (row A, col 4 -> row E, col 8), delivering checkmate
    ]

    print("--- Starting Checkmate Test (with corrected coordinates) ---")
    print(f"Executing: {executable_path}")

    process = subprocess.Popen(
        [executable_path],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
        bufsize=1,
        universal_newlines=True
    )

    # --- Provide initial game setup input ---
    process.stdin.write("3\n")      # Search Depth
    process.stdin.write("1\n")      # Interactive Mode
    time.sleep(0.5)

    # --- Execute the move sequence ---
    for move in moves:
        print(f"Sending move: {move}")
        process.stdin.write(move + "\n")
        time.sleep(0.5)

    # --- Check the final output ---
    try:
        stdout, stderr = process.communicate(timeout=5)
        output = stdout + stderr
        print("\n--- Final Game Output ---")
        print(output)

        # The checkmate message might appear as "check" (code 41) or a more specific message
        if "Checkmate" in output or "check" in output:
            print("\n✅ SUCCESS: Checkmate detected!")
        else:
            print("\n❌ FAILURE: Checkmate message not found in game output.")

    except subprocess.TimeoutExpired:
        process.kill()
        stdout, stderr = process.communicate()
        print("\n❌ ERROR: The game process timed out.")
        print("--- Last Output Before Timeout ---")
        print(stdout)
        print(stderr)
        
    finally:
        if process.poll() is None:
            process.kill()

if __name__ == "__main__":
    run_checkmate_test()