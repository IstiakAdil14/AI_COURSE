let board = ["", "", "", "", "", "", "", "", ""];
const human = "O";
const ai = "X";
const winCombos = [
  [0, 1, 2],
  [3, 4, 5],
  [6, 7, 8],
  [0, 3, 6],
  [1, 4, 7],
  [2, 5, 8],
  [0, 4, 8],
  [2, 4, 6],
];

/**
 * Initializes the game by resetting the board and clearing the status message,
 * then renders the empty board on the UI.
 */
function startGame() {
  board = ["", "", "", "", "", "", "", "", ""];
  document.getElementById("status").innerText = "";
  renderBoard();
}

/**
 * Renders the current state of the board on the UI by creating cell elements
 * and attaching click event listeners for player moves.
 */
function renderBoard() {
  const boardEl = document.getElementById("board");
  boardEl.innerHTML = "";
  board.forEach((cell, index) => {
    const cellEl = document.createElement("div");
    cellEl.classList.add("cell");
    cellEl.innerText = cell;
    cellEl.addEventListener("click", () => makeMove(index));
    boardEl.appendChild(cellEl);
  });
}

/**
 * Handles a player's move at the specified index, updates the board,
 * triggers the AI's move if the game is not over, and updates the UI and status.
 */
function makeMove(index) {
  if (board[index] === "" && !checkWinner(board)) {
    board[index] = human;
    if (!checkWinner(board)) {
      const bestMove = getBestMove(board);
      board[bestMove] = ai;
    }
    renderBoard();
    const winner = checkWinner(board);
    if (winner) {
      document.getElementById("status").innerText =
        winner === "tie" ? "It's a tie!" : `${winner} wins!`;
    }
  }
}

/**
 * Determines the best move for the AI player using the minimax algorithm
 * by evaluating all possible moves and selecting the one with the highest score.
 */
function getBestMove(newBoard) {
  let bestScore = -Infinity;
  let move;
  for (let i = 0; i < newBoard.length; i++) {
    if (newBoard[i] === "") {
      newBoard[i] = ai;
      let score = minimax(newBoard, 0, false);
      newBoard[i] = "";
      if (score > bestScore) {
        bestScore = score;
        move = i;
      }
    }
  }
  return move;
}

/**
 * Implements the minimax algorithm to recursively evaluate the game board
 * and return a score representing the best achievable outcome for the AI or human player.
 */
function minimax(board, depth, isMaximizing) {
  let result = checkWinner(board);
  if (result) {
    if (result === ai) return 10 - depth;
    else if (result === human) return depth - 10;
    else return 0;
  }

  if (isMaximizing) {
    let best = -Infinity;
    for (let i = 0; i < board.length; i++) {
      if (board[i] === "") {
        board[i] = ai;
        best = Math.max(best, minimax(board, depth + 1, false));
        board[i] = "";
      }
    }
    return best;
  } else {
    let best = Infinity;
    for (let i = 0; i < board.length; i++) {
      if (board[i] === "") {
        board[i] = human;
        best = Math.min(best, minimax(board, depth + 1, true));
        board[i] = "";
      }
    }
    return best;
  }
}

/**
 * Checks the current board for a winner or a tie by evaluating all winning combinations.
 * Returns the winner symbol ("X" or "O"), "tie" if no empty cells remain, or null if the game is ongoing.
 */
function checkWinner(b) {
  for (let combo of winCombos) {
    const [a, b1, c] = combo;
    if (b[a] && b[a] === b[b1] && b[a] === b[c]) {
      return b[a];
    }
  }
  if (b.every((cell) => cell !== "")) return "tie";
  return null;
}

startGame();
