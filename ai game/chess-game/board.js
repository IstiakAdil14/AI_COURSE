/**
 * Unicode symbols for chess pieces.
 */
const piecesUnicode = {
    'P': '♙', 'N': '♘', 'B': '♗', 'R': '♖', 'Q': '♕', 'K': '♔',
    'p': '♟', 'n': '♞', 'b': '♝', 'r': '♜', 'q': '♛', 'k': '♚'
};

/**
 * Initial board setup represented as a 2D array.
 * Uppercase letters represent white pieces, lowercase represent black.
 */
let board = [
    ['r','n','b','q','k','b','n','r'],
    ['p','p','p','p','p','p','p','p'],
    ['','','','','','','',''],
    ['','','','','','','',''],
    ['','','','','','','',''],
    ['','','','','','','',''],
    ['P','P','P','P','P','P','P','P'],
    ['R','N','B','Q','K','B','N','R']
];

const chessboard = document.getElementById('chessboard');
const statusDiv = document.getElementById('status');

/**
 * Renders the chessboard UI by creating div elements for each square,
 * displaying pieces using Unicode symbols, and applying styles for selection and highlights.
 */
function renderBoard() {
    chessboard.innerHTML = '';
    for (let row = 0; row < 8; row++) {
        for (let col = 0; col < 8; col++) {
            const square = document.createElement('div');
            square.classList.add('square');
            square.classList.add((row + col) % 2 === 0 ? 'light' : 'dark');
            square.dataset.row = row;
            square.dataset.col = col;
            const piece = board[row][col];
            if (piece) {
                square.textContent = piecesUnicode[piece];
            }
            if (selectedSquare && selectedSquare.row == row && selectedSquare.col == col) {
                square.classList.add('selected');
            }
            if (highlightedSquares.some(sq => sq.row === row && sq.col === col)) {
                square.classList.add('highlight');
            }
            square.addEventListener('click', onSquareClick);
            chessboard.appendChild(square);
        }
    }
}

/**
 * Array to keep track of squares currently highlighted (e.g., valid moves).
 */
let highlightedSquares = [];

/**
 * Clears all highlighted squares.
 */
function clearHighlights() {
    highlightedSquares = [];
}
