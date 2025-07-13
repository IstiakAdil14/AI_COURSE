/**
 * Checks if a piece belongs to the specified color.
 * @param {string} piece - The piece character.
 * @param {string} color - 'w' for white, 'b' for black.
 * @returns {boolean} True if the piece matches the color, false otherwise.
 */
function isPieceColor(piece, color) {
    if (color === 'w') return piece === piece.toUpperCase();
    else return piece === piece.toLowerCase();
}

/**
 * Validates if a move is legal for the current board state.
 * This function implements simplified chess move validation rules,
 * excluding castling, en passant, and promotion for simplicity.
 * @param {number} fromRow - Starting row index.
 * @param {number} fromCol - Starting column index.
 * @param {number} toRow - Destination row index.
 * @param {number} toCol - Destination column index.
 * @param {string} player - Player color ('w' or 'b').
 * @returns {boolean} True if the move is valid, false otherwise.
 */
function isValidMove(fromRow, fromCol, toRow, toCol, player) {
    const piece = board[fromRow][fromCol];
    if (!piece) return false;
    if (!isPieceColor(piece, player)) return false;
    const target = board[toRow][toCol];
    if (target && isPieceColor(target, player)) return false;

    const dr = toRow - fromRow;
    const dc = toCol - fromCol;

    switch (piece.toLowerCase()) {
        case 'p': // Pawn
            const direction = piece === 'P' ? -1 : 1;
            // Move forward
            if (dc === 0 && dr === direction && !target) return true;
            // Initial double move
            if (dc === 0 && dr === 2 * direction && !target && !board[fromRow + direction][fromCol]) {
                if ((piece === 'P' && fromRow === 6) || (piece === 'p' && fromRow === 1)) return true;
            }
            // Capture
            if (Math.abs(dc) === 1 && dr === direction && target && !isPieceColor(target, player)) return true;
            return false;
        case 'n': // Knight
            if ((Math.abs(dr) === 2 && Math.abs(dc) === 1) || (Math.abs(dr) === 1 && Math.abs(dc) === 2)) return true;
            return false;
        case 'b': // Bishop
            if (Math.abs(dr) === Math.abs(dc) && isPathClear(fromRow, fromCol, toRow, toCol)) return true;
            return false;
        case 'r': // Rook
            if ((dr === 0 || dc === 0) && isPathClear(fromRow, fromCol, toRow, toCol)) return true;
            return false;
        case 'q': // Queen
            if ((Math.abs(dr) === Math.abs(dc) || dr === 0 || dc === 0) && isPathClear(fromRow, fromCol, toRow, toCol)) return true;
            return false;
        case 'k': // King
            if (Math.abs(dr) <= 1 && Math.abs(dc) <= 1) return true;
            return false;
    }
    return false;
}

/**
 * Checks if the path between two squares is clear (no pieces in between).
 * This is used for sliding pieces like bishops, rooks, and queens.
 * @param {number} fromRow - Starting row index.
 * @param {number} fromCol - Starting column index.
 * @param {number} toRow - Destination row index.
 * @param {number} toCol - Destination column index.
 * @returns {boolean} True if path is clear, false otherwise.
 */
function isPathClear(fromRow, fromCol, toRow, toCol) {
    const dr = Math.sign(toRow - fromRow);
    const dc = Math.sign(toCol - fromCol);
    let r = fromRow + dr;
    let c = fromCol + dc;
    while (r !== toRow || c !== toCol) {
        if (board[r][c] !== '') return false;
        r += dr;
        c += dc;
    }
    return true;
}

/**
 * Validates if a move is legal on a given board state.
 * Similar to isValidMove but operates on a provided board state.
 * @param {Array} boardState - The board state to check.
 * @param {number} fromRow - Starting row index.
 * @param {number} fromCol - Starting column index.
 * @param {number} toRow - Destination row index.
 * @param {number} toCol - Destination column index.
 * @param {string} player - Player color ('w' or 'b').
 * @returns {boolean} True if the move is valid, false otherwise.
 */
function isValidMoveOnBoard(boardState, fromRow, fromCol, toRow, toCol, player) {
    const piece = boardState[fromRow][fromCol];
    if (!piece) return false;
    if (!isPieceColor(piece, player)) return false;
    const target = boardState[toRow][toCol];
    if (target && isPieceColor(target, player)) return false;

    const dr = toRow - fromRow;
    const dc = toCol - fromCol;

    switch (piece.toLowerCase()) {
        case 'p': // Pawn
            const direction = piece === 'P' ? -1 : 1;
            if (dc === 0 && dr === direction && !target) return true;
            if (dc === 0 && dr === 2 * direction && !target && !boardState[fromRow + direction][fromCol]) {
                if ((piece === 'P' && fromRow === 6) || (piece === 'p' && fromRow === 1)) return true;
            }
            if (Math.abs(dc) === 1 && dr === direction && target && !isPieceColor(target, player)) return true;
            return false;
        case 'n': // Knight
            if ((Math.abs(dr) === 2 && Math.abs(dc) === 1) || (Math.abs(dr) === 1 && Math.abs(dc) === 2)) return true;
            return false;
        case 'b': // Bishop
            if (Math.abs(dr) === Math.abs(dc) && isPathClearOnBoard(boardState, fromRow, fromCol, toRow, toCol)) return true;
            return false;
        case 'r': // Rook
            if ((dr === 0 || dc === 0) && isPathClearOnBoard(boardState, fromRow, fromCol, toRow, toCol)) return true;
            return false;
        case 'q': // Queen
            if ((Math.abs(dr) === Math.abs(dc) || dr === 0 || dc === 0) && isPathClearOnBoard(boardState, fromRow, fromCol, toRow, toCol)) return true;
            return false;
        case 'k': // King
            if (Math.abs(dr) <= 1 && Math.abs(dc) <= 1) return true;
            return false;
    }
    return false;
}

/**
 * Checks if the path between two squares is clear on a given board state.
 * Similar to isPathClear but operates on a provided board state.
 * @param {Array} boardState - The board state to check.
 * @param {number} fromRow - Starting row index.
 * @param {number} fromCol - Starting column index.
 * @param {number} toRow - Destination row index.
 * @param {number} toCol - Destination column index.
 * @returns {boolean} True if path is clear, false otherwise.
 */
function isPathClearOnBoard(boardState, fromRow, fromCol, toRow, toCol) {
    const dr = Math.sign(toRow - fromRow);
    const dc = Math.sign(toCol - fromCol);
    let r = fromRow + dr;
    let c = fromCol + dc;
    while (r !== toRow || c !== toCol) {
        if (boardState[r][c] !== '') return false;
        r += dr;
        c += dc;
    }
    return true;
}

/**
 * Generates all valid moves for a player on a given board state.
 * This function iterates over all pieces of the player and generates all legal moves
 * according to simplified chess rules.
 * @param {string} player - Player color ('w' or 'b').
 * @param {Array} [boardState=board] - Board state to generate moves from.
 * @returns {Array} Array of move objects with fromRow, fromCol, toRow, toCol.
 */
function generateAllMoves(player, boardState = board) {
    const moves = [];
    for (let row = 0; row < 8; row++) {
        for (let col = 0; col < 8; col++) {
            const piece = boardState[row][col];
            if (piece && isPieceColor(piece, player)) {
                for (let r = 0; r < 8; r++) {
                    for (let c = 0; c < 8; c++) {
                        if (isValidMoveOnBoard(boardState, row, col, r, c, player)) {
                            moves.push({fromRow: row, fromCol: col, toRow: r, toCol: c});
                        }
                    }
                }
            }
        }
    }
    return moves;
}
