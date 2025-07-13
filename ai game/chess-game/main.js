/**
 * Currently selected square on the board.
 * @type {Object|null}
 */
let selectedSquare = null;

/**
 * Current player: 'w' for user (white), 'b' for computer (black).
 * @type {string}
 */
let currentPlayer = 'w'; // 'w' = user (white), 'b' = computer (black)

/**
 * Flag indicating if the game is over.
 * @type {boolean}
 */
let gameOver = false;

/**
 * Handles click events on a chessboard square.
 * Manages piece selection, move validation, move execution, and turn switching.
 * @param {Event} e - The click event.
 */
function onSquareClick(e) {
    if (gameOver) return;
    const row = parseInt(e.currentTarget.dataset.row);
    const col = parseInt(e.currentTarget.dataset.col);
    const piece = board[row][col];

    if (selectedSquare) {
        // Try to move selected piece to clicked square
        if (isValidMove(selectedSquare.row, selectedSquare.col, row, col, currentPlayer)) {
            makeMove(selectedSquare.row, selectedSquare.col, row, col);
            selectedSquare = null;
            clearHighlights();
            renderBoard();
            if (checkGameOver()) return;
            currentPlayer = 'b';
            statusDiv.textContent = "Computer thinking...";
            setTimeout(() => {
                computerMove();
                renderBoard();
                if (checkGameOver()) return;
                currentPlayer = 'w';
                statusDiv.textContent = "Your turn";
                showSuggestion();
            }, 200);
        } else {
            // Invalid move, deselect
            selectedSquare = null;
            clearHighlights();
            renderBoard();
        }
    } else {
        // Select piece if it belongs to current player
        if (piece && isPieceColor(piece, currentPlayer)) {
            selectedSquare = {row, col};
            highlightedSquares = getValidMovesForPiece(row, col, currentPlayer);
            renderBoard();
        }
    }
}

/**
 * Returns an array of valid moves for a piece at the given position.
 * @param {number} row - Row index of the piece.
 * @param {number} col - Column index of the piece.
 * @param {string} player - Player color ('w' or 'b').
 * @returns {Array} Array of valid move positions.
 */
function getValidMovesForPiece(row, col, player) {
    const moves = [];
    for (let r = 0; r < 8; r++) {
        for (let c = 0; c < 8; c++) {
            if (isValidMove(row, col, r, c, player)) {
                moves.push({row: r, col: c});
            }
        }
    }
    return moves;
}

/**
 * Executes a move on the board by moving a piece from one position to another.
 * @param {number} fromRow - Starting row index.
 * @param {number} fromCol - Starting column index.
 * @param {number} toRow - Destination row index.
 * @param {number} toCol - Destination column index.
 */
function makeMove(fromRow, fromCol, toRow, toCol) {
    board[toRow][toCol] = board[fromRow][fromCol];
    board[fromRow][fromCol] = '';
}

/**
 * Checks if the game is over by verifying if either king is missing.
 * Updates the status message and gameOver flag accordingly.
 * @returns {boolean} True if the game is over, false otherwise.
 */
function checkGameOver() {
    // Simplified: check if either king is missing
    let whiteKing = false;
    let blackKing = false;
    for (let row = 0; row < 8; row++) {
        for (let col = 0; col < 8; col++) {
            if (board[row][col] === 'K') whiteKing = true;
            if (board[row][col] === 'k') blackKing = true;
        }
    }
    if (!whiteKing) {
        statusDiv.textContent = "Game over. You lost.";
        gameOver = true;
        return true;
    }
    if (!blackKing) {
        statusDiv.textContent = "Game over. You won!";
        gameOver = true;
        return true;
    }
    return false;
}

/**
 * Displays move suggestions to the user.
 * Currently only updates status text and could be extended to highlight moves.
 */
function showSuggestion() {
    if (gameOver || currentPlayer !== 'w') {
        statusDiv.textContent = "Your turn";
        return;
    }
    // Remove text suggestion, just show highlights on board
    // Optionally, could highlight best move squares here if desired
}

// Initialize the board and show initial suggestions.
renderBoard();
showSuggestion();
