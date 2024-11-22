//
//  TT19_L8_FloresNuth
//  COSC 1337-001
//
//  Created by Mercedes Flores Nuth on 11/2/24.
//

#include <iostream>
#include <vector>
#include <iomanip>  // for formatting percentages

class Board {
private:
    int rows;
    int cols;
    int winLength;
    std::vector<std::vector<char>> grid;

public:
    Board(int r, int c, int w) : rows(r), cols(c), winLength(w), grid(r, std::vector<char>(c, '*')) {}

    int getCols() const { return cols; }

    // Display board
    void displayBoard() const {
        // Display column numbers
        for (int i = 1; i <= cols; ++i) std::cout << i << " ";
        std::cout << "\n";

        // Display each row
        for (const auto& row : grid) {
            for (char cell : row) std::cout << cell << " ";
            std::cout << "\n";
        }
    }

    // Drop a token in the selected column
    bool dropToken(int column, char token) {
        if (column < 0 || column >= cols) return false; // invalid column

        for (int row = rows - 1; row >= 0; --row) {
            if (grid[row][column] == '*') { // check for empty spot
                grid[row][column] = token; // place token
                return true;
            }
        }
        return false; // column is full
    }

    // Check for win
    bool checkWin(char token) {
        // Check horizontal
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c <= cols - winLength; ++c) {
                bool win = true;
                for (int i = 0; i < winLength; ++i) {
                    if (grid[r][c + i] != token) {
                        win = false;
                        break;
                    }
                }
                if (win) return true;
            }
        }

        // Check vertical
        for (int c = 0; c < cols; ++c) {
            for (int r = 0; r <= rows - winLength; ++r) {
                bool win = true;
                for (int i = 0; i < winLength; ++i) {
                    if (grid[r + i][c] != token) {
                        win = false;
                        break;
                    }
                }
                if (win) return true;
            }
        }

        // Check diagonal (top-left to bottom-right)
        for (int r = 0; r <= rows - winLength; ++r) {
            for (int c = 0; c <= cols - winLength; ++c) {
                bool win = true;
                for (int i = 0; i < winLength; ++i) {
                    if (grid[r + i][c + i] != token) {
                        win = false;
                        break;
                    }
                }
                if (win) return true;
            }
        }

        // Check diagonal (top-right to bottom-left)
        for (int r = 0; r <= rows - winLength; ++r) {
            for (int c = winLength - 1; c < cols; ++c) {
                bool win = true;
                for (int i = 0; i < winLength; ++i) {
                    if (grid[r + i][c - i] != token) {
                        win = false;
                        break;
                    }
                }
                if (win) return true;
            }
        }

        return false;
    }

    // Check if the board is full
    bool isBoardFull() const {
        for (int c = 0; c < cols; ++c) {
            if (grid[0][c] == '*') return false;
        }
        return true;
    }

    // Reset for new game
    void resetBoard() {
        for (auto& row : grid) {
            std::fill(row.begin(), row.end(), '*');
        }
    }
};

// Two-player gane
void playGame(Board& gameBoard, char player1, char player2, int& p1Wins, int& p2Wins, int& ties) {
    char currentPlayer = player1;
    bool gameWon = false;

    while (!gameWon && !gameBoard.isBoardFull()) {
        int column;
        gameBoard.displayBoard();
        std::cout << "Player (" << currentPlayer << "), choose column (1-" << gameBoard.getCols() << "): ";
        std::cin >> column;

        if (column == 0) {
            std::cout << "Player forfeits! Ending game.\n";
            if (currentPlayer == player1) p2Wins++;
            else p1Wins++;
            return;
        }

        if (gameBoard.dropToken(column - 1, currentPlayer)) {
            gameWon = gameBoard.checkWin(currentPlayer);
            if (!gameWon) {
                currentPlayer = (currentPlayer == player1) ? player2 : player1; // players take turns
            }
        } else {
            std::cout << "Invalid move. Try again.\n";
        }
    }

    gameBoard.displayBoard();

    if (gameWon) {
        std::cout << "Congratulations! Player (" << currentPlayer << ") has won the game!\n";
        if (currentPlayer == player1) p1Wins++;
        else p2Wins++;
    } else {
        std::cout << "It's a tie! Cat's game.\n";
        ties++;
    }
}

// Display statistics
void displayStatistics(int p1Wins, int p2Wins, int ties) {
    int totalGames = p1Wins + p2Wins + ties;
    std::cout << "\nGame Statistics:\n";
    std::cout << "Player 1 wins: " << p1Wins << " (" << std::fixed << std::setprecision(2)
              << (static_cast<double>(p1Wins) / totalGames) * 100 << "%)\n";
    std::cout << "Player 2 wins: " << p2Wins << " (" << std::fixed << std::setprecision(2)
              << (static_cast<double>(p2Wins) / totalGames) * 100 << "%)\n";
    std::cout << "Ties: " << ties << " (" << std::fixed << std::setprecision(2)
              << (static_cast<double>(ties) / totalGames) * 100 << "%)\n";
}

int main() {
    int rows = 6;
    int cols = 7;
    int winLength = 4;
    char player1 = 'M';
    char player2 = 'F';

    int p1Wins = 0, p2Wins = 0, ties = 0;
    char playAgain = 'y';

    while (playAgain == 'y' || playAgain == 'Y') {
        // Create game board and play
        Board gameBoard(rows, cols, winLength);
        playGame(gameBoard, player1, player2, p1Wins, p2Wins, ties);

        // Display game statistics
        displayStatistics(p1Wins, p2Wins, ties);

        // Ask if players want to play again
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> playAgain;
    }

    std::cout << "Thank you for playing Connect-4! Goodbye.\n";
    return 0;
}

//
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//Player (M), choose column (1-7): 2
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* M * * * * *
//Player (F), choose column (1-7): 2
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* F * * * * *
//* M * * * * *
//Player (M), choose column (1-7): 3
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* F * * * * *
//* M M * * * *
//Player (F), choose column (1-7): 1
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* F * * * * *
//F M M * * * *
//Player (M), choose column (1-7): 4
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* F * * * * *
//F M M M * * *
//Player (F), choose column (1-7): 1
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//F F * * * * *
//F M M M * * *
//Player (M), choose column (1-7): 5
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//F F * * * * *
//F M M M M * *
//Congratulations! Player (M) has won the game!
//
//Game Statistics:
//Player 1 wins: 1 (100.00%)
//Player 2 wins: 0 (0.00%)
//Ties: 0 (0.00%)
//Do you want to play again? (y/n): y
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//Player (M), choose column (1-7): 3
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * M * * * *
//Player (F), choose column (1-7): 4
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * M F * * *
//Player (M), choose column (1-7): 2
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* M M F * * *
//Player (F), choose column (1-7): 5
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* M M F F * *
//Player (M), choose column (1-7): 1
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//M M M F F * *
//Player (F), choose column (1-7): 6
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//M M M F F F *
//Player (M), choose column (1-7): 2
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* M * * * * *
//M M M F F F *
//Player (F), choose column (1-7): 6
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* M * * * F *
//M M M F F F *
//Player (M), choose column (1-7): 1
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//M M * * * F *
//M M M F F F *
//Player (F), choose column (1-7): 7
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//M M * * * F *
//M M M F F F F
//Congratulations! Player (F) has won the game!
//
//Game Statistics:
//Player 1 wins: 1 (50.00%)
//Player 2 wins: 1 (50.00%)
//Ties: 0 (0.00%)
//Do you want to play again? (y/n): y
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//Player (M), choose column (1-7): 2
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* M * * * * *
//Player (F), choose column (1-7): 3
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* M F * * * *
//Player (M), choose column (1-7): 4
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* M F M * * *
//Player (F), choose column (1-7): 2
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* F * * * * *
//* M F M * * *
//Player (M), choose column (1-7): 2
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* M * * * * *
//* F * * * * *
//* M F M * * *
//Player (F), choose column (1-7): 5
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* M * * * * *
//* F * * * * *
//* M F M F * *
//Player (M), choose column (1-7): 6
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* M * * * * *
//* F * * * * *
//* M F M F M *
//Player (F), choose column (1-7): 5
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* M * * * * *
//* F * * F * *
//* M F M F M *
//Player (M), choose column (1-7): 4
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* M * * * * *
//* F * M F * *
//* M F M F M *
//Player (F), choose column (1-7): 1
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* M * * * * *
//* F * M F * *
//F M F M F M *
//Player (M), choose column (1-7): 3
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* M * * * * *
//* F M M F * *
//F M F M F M *
//Player (F), choose column (1-7):
//5
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* M * * F * *
//* F M M F * *
//F M F M F M *
//Player (M), choose column (1-7): 3
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* M M * F * *
//* F M M F * *
//F M F M F M *
//Player (F), choose column (1-7): 4
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* M M F F * *
//* F M M F * *
//F M F M F M *
//Player (M), choose column (1-7): 2
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* M * * * * *
//* M M F F * *
//* F M M F * *
//F M F M F M *
//Player (F), choose column (1-7): 1
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* M * * * * *
//* M M F F * *
//F F M M F * *
//F M F M F M *
//Player (M), choose column (1-7): 4
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* M * M * * *
//* M M F F * *
//F F M M F * *
//F M F M F M *
//Player (F), choose column (1-7): 3
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* M F M * * *
//* M M F F * *
//F F M M F * *
//F M F M F M *
//Player (M), choose column (1-7): 1
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* M F M * * *
//M M M F F * *
//F F M M F * *
//F M F M F M *
//Player (F), choose column (1-7): 2
//1 2 3 4 5 6 7
//* * * * * * *
//* F * * * * *
//* M F M * * *
//M M M F F * *
//F F M M F * *
//F M F M F M *
//Congratulations! Player (F) has won the game!
//
//Game Statistics:
//Player 1 wins: 1 (33.33%)
//Player 2 wins: 2 (66.67%)
//Ties: 0 (0.00%)
//Do you want to play again? (y/n): y
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//Player (M), choose column (1-7): 1
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//M * * * * * *
//Player (F), choose column (1-7): 2
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//M F * * * * *
//Player (M), choose column (1-7): 1
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//M * * * * * *
//M F * * * * *
//Player (F), choose column (1-7): 4
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//M * * * * * *
//M F * F * * *
//Player (M), choose column (1-7): 5
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//M * * * * * *
//M F * F M * *
//Player (F), choose column (1-7): 6
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//M * * * * * *
//M F * F M F *
//Player (M), choose column (1-7): 2
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//M M * * * * *
//M F * F M F *
//Player (F), choose column (1-7): 4
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//M M * F * * *
//M F * F M F *
//Player (M), choose column (1-7): 3
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//M M * F * * *
//M F M F M F *
//Player (F), choose column (1-7): 6
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//M M * F * F *
//M F M F M F *
//Player (M), choose column (1-7): 3
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//M M M F * F *
//M F M F M F *
//Player (F), choose column (1-7): 5
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//M M M F F F *
//M F M F M F *
//Player (M), choose column (1-7): 7
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* * * * * * *
//M M M F F F *
//M F M F M F M
//Player (F), choose column (1-7): 2
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* F * * * * *
//M M M F F F *
//M F M F M F M
//Player (M), choose column (1-7): 4
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* F * M * * *
//M M M F F F *
//M F M F M F M
//Player (F), choose column (1-7): 5
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//* F * M F * *
//M M M F F F *
//M F M F M F M
//Player (M), choose column (1-7): 1
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//M F * M F * *
//M M M F F F *
//M F M F M F M
//Player (F), choose column (1-7): 3
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * * * *
//M F F M F * *
//M M M F F F *
//M F M F M F M
//Player (M), choose column (1-7): 5
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * M * *
//M F F M F * *
//M M M F F F *
//M F M F M F M
//Player (F), choose column (1-7): 7
//1 2 3 4 5 6 7
//* * * * * * *
//* * * * * * *
//* * * * M * *
//M F F M F * *
//M M M F F F F
//M F M F M F M
//Congratulations! Player (F) has won the game!
//
//Game Statistics:
//Player 1 wins: 1 (25.00%)
//Player 2 wins: 3 (75.00%)
//Ties: 0 (0.00%)
//Do you want to play again? (y/n): n
//Thank you for playing Connect-4! Goodbye.
//Program ended with exit code: 0
