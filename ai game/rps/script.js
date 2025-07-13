/**
 * Array of possible moves in the game.
 */
const moves = ["rock", "paper", "scissors"];

/**
 * Mapping of which move beats which move.
 * Key beats the value.
 */
const winMap = {
  rock: "scissors",
  paper: "rock",
  scissors: "paper",
};

/**
 * History of player's moves to predict AI's next move.
 * This simple frequency-based prediction algorithm tracks the player's past moves
 * to anticipate their next move and counter it effectively.
 */
let playerHistory = [];

/**
 * Player's current score.
 */
let playerScore = 0;

/**
 * AI's current score.
 */
let aiScore = 0;

/**
 * Determines the AI's move based on player's move history.
 * If less than 3 moves in history, chooses randomly.
 * Otherwise, predicts player's most likely move and selects a move to beat it.
 * This heuristic approach aims to improve AI's chances by exploiting player tendencies.
 * @returns {string} AI's move choice.
 */
function aiMove() {
  if (playerHistory.length < 3) {
    return moves[Math.floor(Math.random() * 3)];
  }

  const count = { rock: 0, paper: 0, scissors: 0 };
  playerHistory.forEach((m) => count[m]++);

  const likelyMove = Object.keys(count).reduce((a, b) =>
    count[a] > count[b] ? a : b
  );

  for (let move of moves) {
    if (winMap[move] === likelyMove) {
      return move;
    }
  }
  return moves[Math.floor(Math.random() * 3)];
}

/**
 * Handles a round of the game when the player makes a move.
 * Updates scores, determines result message, and updates the display.
 * Ends the game when either player or AI reaches 5 points.
 * @param {string} playerMove - The player's chosen move.
 */
function play(playerMove) {
  if (playerScore >= 5 || aiScore >= 5) return;

  const aiChoice = aiMove();
  let result = "";

  playerHistory.push(playerMove);

  if (playerMove === aiChoice) {
    result = `It's a draw! You both chose ${playerMove}.`;
  } else if (winMap[playerMove] === aiChoice) {
    result = `You win! ${playerMove} beats ${aiChoice}.`;
    playerScore++;
  } else {
    result = `You lose! ${aiChoice} beats ${playerMove}.`;
    aiScore++;
  }

  if (playerScore >= 5) {
    result += " 🎉 You won the game!";
  } else if (aiScore >= 5) {
    result += " 🤖 AI wins the game!";
  }

  result += `<br>Score - You: ${playerScore}, AI: ${aiScore}`;
  document.getElementById("result").innerHTML = result;
}

/**
 * Resets the game state and clears the result display.
 */
function restartGame() {
  playerHistory = [];
  playerScore = 0;
  aiScore = 0;
  document.getElementById("result").innerHTML = "";
}
