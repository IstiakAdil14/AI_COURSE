/**
 * Creates a deep copy of the board state array.
 * @param {Array} boardState - The current board state.
 * @returns {Array} A new copy of the board state.
 */
function copyBoard(boardState) {
    return boardState.map(row => row.slice());
}

/**
 * Executes a move on the given board state by moving a piece from one position to another.
 * @param {Array} boardState - The board state to modify.
 * @param {number} fromRow - Starting row index.
 * @param {number} fromCol - Starting column index.
 * @param {number} toRow - Destination row index.
 * @param {number} toCol - Destination column index.
 */
function makeMoveOnBoard(boardState, fromRow, fromCol, toRow, toCol) {
    boardState[toRow][toCol] = boardState[fromRow][fromCol];
    boardState[fromRow][fromCol] = '';
}

/**
 * Checks if the game is in a terminal state (either king is missing).
 * @param {Array} boardState - The current board state.
 * @returns {boolean} True if the game is over, false otherwise.
 */
function isTerminal(boardState) {
    // Terminal if either king missing
    let whiteKing = false;
    let blackKing = false;
    for (let row = 0; row < 8; row++) {
        for (let col = 0; col < 8; col++) {
            if (boardState[row][col] === 'K') whiteKing = true;
            if (boardState[row][col] === 'k') blackKing = true;
        }
    }
    return !whiteKing || !blackKing;
}

/**
 * Evaluates the board state by calculating a simple material score.
 * Positive values favor black, negative values favor white.
 * @param {Array} boardState - The current board state.
 * @returns {number} The evaluation score.
 */
function evaluateBoard(boardState) {
    // Simple material evaluation
    const values = {
        'p': 1, 'n': 3, 'b': 3, 'r': 5, 'q': 9, 'k': 0,
        'P': -1, 'N': -3, 'B': -3, 'R': -5, 'Q': -9, 'K': 0
    };
    let score = 0;
    for (let row = 0; row < 8; row++) {
        for (let col = 0; col < 8; col++) {
            const piece = boardState[row][col];
            if (piece) {
                score += values[piece] || 0;
            }
        }
    }
    return score;
}

/**
 * Minimax algorithm with alpha-beta pruning to evaluate board states.
 * This algorithm recursively explores possible moves to a certain depth,
 * pruning branches that cannot yield better results to optimize performance.
 * It helps the AI select the best move by maximizing its advantage while minimizing the opponent's.
 * @param {Array} boardState - The current board state.
 * @param {number} depth - The depth to search.
 * @param {number} alpha - Alpha value for pruning.
 * @param {number} beta - Beta value for pruning.
 * @param {boolean} maximizingPlayer - True if maximizing player, false otherwise.
 * @returns {number} The evaluation score.
 */
function minimax(boardState, depth, alpha, beta, maximizingPlayer) {
    if (depth === 0 || isTerminal(boardState)) {
        return evaluateBoard(boardState);
    }
    if (maximizingPlayer) {
        let maxEval = -Infinity;
        const moves = generateAllMoves('b', boardState);
        for (const move of moves) {
            const newBoard = copyBoard(boardState);
            makeMoveOnBoard(newBoard, move.fromRow, move.fromCol, move.toRow, move.toCol);
            const eval = minimax(newBoard, depth - 1, alpha, beta, false);
            maxEval = Math.max(maxEval, eval);
            alpha = Math.max(alpha, eval);
            if (beta <= alpha) break;
        }
        return maxEval;
    } else {
        let minEval = Infinity;
        const moves = generateAllMoves('w', boardState);
        for (const move of moves) {
            const newBoard = copyBoard(boardState);
            makeMoveOnBoard(newBoard, move.fromRow, move.fromCol, move.toRow, move.toCol);
            const eval = minimax(newBoard, depth - 1, alpha, beta, true);
            minEval = Math.min(minEval, eval);
            beta = Math.min(beta, eval);
            if (beta <= alpha) break;
        }
        return minEval;
    }
}

/**
 * Executes the computer's move by selecting the best move using minimax.
 * This function limits the search depth for performance reasons.
 */
function computerMove() {
    const depth = 3; // Limited depth for performance
    let bestMove = null;
    let bestValue = -Infinity;

    const moves = generateAllMoves('b');
    for (const move of moves) {
        const newBoard = copyBoard(board);
        makeMoveOnBoard(newBoard, move.fromRow, move.fromCol, move.toRow, move.toCol);
        const value = minimax(newBoard, depth - 1, -Infinity, Infinity, false);
        if (value > bestValue) {
            bestValue = value;
            bestMove = move;
        }
    }
    if (bestMove) {
        makeMove(bestMove.fromRow, bestMove.fromCol, bestMove.toRow, bestMove.toCol);
    }
}

/**
 * Suggests the best move for the user (white) using minimax.
 * @returns {Object|null} The best move object or null if none found.
 */
function suggestMove() {
    const depth = 3;
    let bestMove = null;
    let bestValue = Infinity;

    const moves = generateAllMoves('w');
    for (const move of moves) {
        const newBoard = copyBoard(board);
        makeMoveOnBoard(newBoard, move.fromRow, move.fromCol, move.toRow, move.toCol);
        const value = minimax(newBoard, depth - 1, -Infinity, Infinity, true);
        if (value < bestValue) {
            bestValue = value;
            bestMove = move;
        }
    }
    return bestMove;
}
