Rock-Paper-Scissors (RPS) Game Project Documentation

Folder: rps/
This folder contains the files for a simple web-based Rock-Paper-Scissors game.

Files:

1. index.html
- The main HTML page for the RPS game.
- Contains:
  - Game interface with buttons for Rock, Paper, Scissors, and Restart.
  - Result display area.
  - Links to CSS and JavaScript files.

2. script.js
- Contains the JavaScript logic for the RPS game.
- Implements:
  - moves array and winMap object defining game rules.
  - playerHistory array and scores for player and AI.
  - aiMove function that predicts player's next move based on history and counters it.
  - play function to handle a round, update scores, and display results.
  - restartGame function to reset the game state.

3. style.css
- Contains the CSS styles for the RPS game.
- Styles include:
  - Body font, text alignment, padding, and background color.
  - Heading color.
  - Button padding, margin, font size, and cursor style.
  - Result text font size and margin.

This project provides a basic playable Rock-Paper-Scissors game in the browser.
