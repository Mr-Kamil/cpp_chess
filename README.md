## cpp_chess – UCI Compatible Chess Engine

cpp_chess is a chess engine built from scratch in C++, designed to be compatible with the UCI (Universal Chess Interface) protocol. This project implements the NegaMax algorithm and utilizes bitboards for board representation, similar to professional chess engines.

**Status:** Work in progress...

---
This chess_engine was tested with the Arena Chess GUI - you can download it from two websites: 
<br />http://www.playwitharena.de/
<br />https://www.fileeagle.com/software/1598/Arena
<br />
### To run and play against this chess engine:
 - Download the Arena Chess GUI
 - Install the Arena Chess GUI
 - Clone the cpp_chess repository:
   ```batch
   git clone https://github.com/Mr-Kamil/cpp_chess
   cd cpp_chess
   ```
 - Compile the project:
   ```batch
   g++ uci.cpp chess_rules.cpp -o cpp_chess
   ```
 - Open the Arena GUI and install a new engine.
 - Point the engine path to cpp_chess.exe.
 - You are ready to play ;)

---
## TODO:
- Implement pawn promotion
- Enforce threefold repetition rule
- Implement castling mechanics
- Update Negamax algorithm
- Write unit tests
- Update logging mechanics

---
## Features:
-  **UCI Protocol Support** – Communicates with GUI interfaces like ChessBase, Arena, or CuteChess. Implemented main commands.
-  **Custom Chess Rules Engine** – Implements move validation, board representation, and game state management.
-  **Nega Max Algorithm** – A custom-built AI designed for efficient position evaluation and decision-making.
-  **Optimized Bitboard Representation** – Uses bitboards for efficient move generation and evaluation.
-  **Move Ordering & Search Optimizations** – Implementation of search depth, transposition tables, and pruning techniques.

