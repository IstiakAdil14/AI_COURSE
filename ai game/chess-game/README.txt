Chess Game Project Documentation

Folder: chess-game/
This folder contains the files for a simple web-based chess game where a user plays against the computer AI.

Files:

1. ai.js
- Contains AI logic for the computer player.
- Implements the minimax algorithm with alpha-beta pruning to evaluate moves.
- Functions include:
  - copyBoard: creates a deep copy of the board state.
  - makeMoveOnBoard: applies a move to a given board state.
  - isTerminal: checks if the game is over (king missing).
  - evaluateBoard: evaluates board material for scoring.
  - minimax: recursive minimax algorithm with pruning.
  - computerMove: selects and makes the best move for the computer.
  - suggestMove: suggests the best move for the user.

2. board.js
- Manages the chess board state and rendering.
- Defines:
  - piecesUnicode: Unicode symbols for chess pieces.
  - board: initial board setup as a 2D array.
  - renderBoard: renders the board squares and pieces on the webpage.
  - highlightedSquares and clearHighlights: manage UI highlights.
- Handles user interaction highlights on the board.

3. main.js
- Contains the main game logic and user interaction handlers.
- Manages:
  - selectedSquare, currentPlayer, gameOver state variables.
  - onSquareClick: handles user clicks and moves.
  - getValidMovesForPiece: returns valid moves for a selected piece.
  - makeMove: updates the board state.
  - checkGameOver: checks for game end conditions.
  - showSuggestion: updates UI for move suggestions.
- Initializes the game by rendering the board and showing suggestions.

4. moves.js
- Implements move validation and generation logic.
- Functions include:
  - isPieceColor: checks if a piece belongs to a player.
  - isValidMove and isValidMoveOnBoard: validate moves on global and passed board states.
  - isPathClear and isPathClearOnBoard: check if path between squares is clear.
  - generateAllMoves: generates all valid moves for a player on a given board state.
- Uses simplified chess rules (no castling, en passant, or promotion).

5. index.html
- The main HTML page for the chess game.
- Includes the chessboard container, status display, and links to CSS and JavaScript files.
- Loads the scripts in the order: board.js, moves.js, ai.js, main.js.

6. style.css
- Contains the CSS styles for the chess game.
- Styles the chessboard, squares, pieces, highlights, and status display.

Note:
- The file script.js was removed as it contained redundant code duplicating other files and was not used in the project.

This project provides a basic playable chess game with AI opponent and user interface in the browser.
