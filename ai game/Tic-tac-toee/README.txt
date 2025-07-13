Tic-Tac-Toe Game Project Documentation

Folder: Tic-tac-toee/
This folder contains the files for a simple web-based Tic-Tac-Toe game.

Files:

1. index.html
- The main HTML page for the Tic-Tac-Toe game.
- Contains:
  - Game interface with a 3x3 grid board.
  - Status display area.
  - Restart button.
  - Links to CSS and JavaScript files.

2. script.js
- Contains the JavaScript logic for the Tic-Tac-Toe game.
- Implements:
  - board array representing the 3x3 grid.
  - human and ai player symbols.
  - winCombos array defining winning combinations.
  - startGame to reset the board and status.
  - renderBoard to display the board and attach click handlers.
  - makeMove to handle human move, AI response, and check for winner.
  - getBestMove using minimax algorithm to find optimal AI move.
  - minimax function implementing the minimax algorithm for AI decision making.
  - checkWinner to determine if there's a winner or tie.

3. style.css
- Contains the CSS styles for the Tic-Tac-Toe game.
- Styles include:
  - Body font, text alignment, and background color.
  - Heading margin.
  - Board styled as a 3x3 grid with gaps and fixed width.
  - Cell styling with size, background, font size, flex centering, cursor, and border.
  - Cell hover effect with background color change.
  - Button styling with margin and padding.

This project provides a basic playable Tic-Tac-Toe game in the browser.
