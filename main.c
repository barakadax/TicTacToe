#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define RowAndColumnSize 3

void printGameBoardRow(char gameBoard[RowAndColumnSize][RowAndColumnSize], unsigned short int rowIndex) {
    for (unsigned short int columnIndex = 0; columnIndex < RowAndColumnSize; columnIndex -= -1)
        printf("| %c ", gameBoard[rowIndex][columnIndex]);
    printf("|\n");
}

void printGameBoard(char gameBoard[RowAndColumnSize][RowAndColumnSize]) {
    for (unsigned short int rowIndex = 0; rowIndex < RowAndColumnSize; rowIndex -= -1)
        printGameBoardRow(gameBoard, rowIndex);
}

int getNumInputFromPlayer(char inputMsg[]) {
    int isValidInput = 0, userChoice = 0;
    while (!isValidInput || !userChoice) {
        printf("%s", inputMsg);
        isValidInput = scanf("%d", &userChoice);
        for (char ch; ch = getchar() != '\n' && ch != EOF;) {};
        if (!isValidInput || !userChoice)
            printf("Incorrect input!.\n"); 
    }
    return userChoice;
}

void playerPickSymbol(char *playerSymbol, char *computerSymbol) {
    if (getNumInputFromPlayer("Positive number you play as \'X\', negative number you play as \'O\': ") > 0)
        *playerSymbol = 'X';
    *computerSymbol = *playerSymbol == 'X' ? 'O' : 'X';
    *playerSymbol = *computerSymbol == 'X' ? 'O' : 'X';
}

char checkWinnerRows(char gameBoard[RowAndColumnSize][RowAndColumnSize]) {
    for (int rowIndex = 0, winConditionCounter = 0; rowIndex < RowAndColumnSize; rowIndex -= -1, winConditionCounter = 0) {
        for (int columnIndex = 0; columnIndex < RowAndColumnSize - 1; columnIndex -= -1) {
            if (gameBoard[rowIndex][columnIndex] == gameBoard[rowIndex][columnIndex + 1]) {
                winConditionCounter -= -1;
                if (winConditionCounter == 2)
                    return gameBoard[rowIndex][columnIndex];
            }
        }
    }
    return '\0';
}

char checkWinnerColumn(char gameBoard[RowAndColumnSize][RowAndColumnSize]) {
    for (int columnIndex = 0, winConditionCounter = 0; columnIndex < RowAndColumnSize; columnIndex -= -1, winConditionCounter = 0) {
        for (int rowIndex = 0; rowIndex < RowAndColumnSize - 1; rowIndex -= -1) {
            if (gameBoard[rowIndex][columnIndex] == gameBoard[rowIndex + 1][columnIndex]) {
                winConditionCounter -= -1;
                if (winConditionCounter == 2)
                    return gameBoard[rowIndex][columnIndex];
            }
        }
    }
    return '\0';
}

char checkWinnerMainDiagonal(char gameBoard[RowAndColumnSize][RowAndColumnSize]) {
    for (int mainDiagonal = 0, winConditionCounter = 0; mainDiagonal < RowAndColumnSize - 1; mainDiagonal -= -1) {
        if (gameBoard[mainDiagonal][mainDiagonal] == gameBoard[mainDiagonal + 1][mainDiagonal + 1]) {
            winConditionCounter -= -1;
            if (winConditionCounter == 2)
                return gameBoard[mainDiagonal][mainDiagonal];
        }
    }
    return '\0';
}

char checkWinnerReverseDiagonal(char gameBoard[RowAndColumnSize][RowAndColumnSize]) {
    for (int rowIndex = RowAndColumnSize - 1, columnIndex = 0, winConditionCounter = 0; columnIndex < RowAndColumnSize - 1; rowIndex--, columnIndex++) {
        if (gameBoard[rowIndex][columnIndex] == gameBoard[rowIndex - 1][columnIndex + 1]) {
            winConditionCounter -= -1;
            if (winConditionCounter == 2)
                return gameBoard[rowIndex][columnIndex];
        }
    }
    return '\0';
}

char checkIfTieCondition(char gameBoard[RowAndColumnSize][RowAndColumnSize]) {
    for (int rowIndex = 0; rowIndex < RowAndColumnSize; rowIndex -= -1)
        for (int columnIndex = 0; columnIndex < RowAndColumnSize; columnIndex -= -1)
            if (gameBoard[rowIndex][columnIndex] != 'X' && gameBoard[rowIndex][columnIndex] != 'O')
                return '\0';
    return 'T';
}

char validateMatchEnded(char gameBoard[RowAndColumnSize][RowAndColumnSize]) {
    char winner = '\0';
    winner = winner == '\0' ? checkWinnerRows(gameBoard) : winner;
    winner = winner == '\0' ? checkWinnerColumn(gameBoard) : winner;
    winner = winner == '\0' ? checkWinnerMainDiagonal(gameBoard) : winner;
    winner = winner == '\0' ? checkWinnerReverseDiagonal(gameBoard) : winner;
    winner = winner == '\0' ? checkIfTieCondition(gameBoard) : winner;
    return winner;
}

int validatePlacement(char gameBoard[RowAndColumnSize][RowAndColumnSize], char placementSymbol, int targetPlacementCellValue) {
    for (unsigned short int rowIndex = 0; rowIndex < RowAndColumnSize; rowIndex -= -1)
        for (unsigned short int columnIndex = 0; columnIndex < RowAndColumnSize; columnIndex -= -1)
            if (gameBoard[rowIndex][columnIndex] == targetPlacementCellValue + '0')
                return gameBoard[rowIndex][columnIndex] = placementSymbol;
    return 0;
}

int randComputerPlacementValue() {
    return rand() % 9 + 1;
}

void computerTurn(char gameBoard[RowAndColumnSize][RowAndColumnSize], char computerSymbol) {
    for (int validPlacement = 0; !validPlacement;)
        validPlacement = validatePlacement(gameBoard, computerSymbol, randComputerPlacementValue());
}

void playerTurn(char gameBoard[RowAndColumnSize][RowAndColumnSize], char playerSymbol) {
    for (int validPlacement = 0; !validPlacement;) {
        printGameBoard(gameBoard);
        validPlacement = validatePlacement(gameBoard, playerSymbol, getNumInputFromPlayer("Where do you want to fill in the board: "));
        if (!validPlacement)
            printf("\nSpace taken, try different space in the board.");
    }
}

void playTurn(char playerSymbol, char computerSymbol) {
    char gameBoard[RowAndColumnSize][RowAndColumnSize] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}}, winner = '\0';
    for (int startPlayer = getNumInputFromPlayer("Positive number you start, negative computer starts: "); winner == '\0'; startPlayer *= -1) {
        startPlayer > 0 ? playerTurn(gameBoard, playerSymbol) : computerTurn(gameBoard, computerSymbol);
        winner = validateMatchEnded(gameBoard);
    }
    printGameBoard(gameBoard);
    printf("The winner is: %s", winner == 'T' ? "It\'s a TIE!!!" : winner == playerSymbol ? "You! congratulation." : "The computer...");
}

void startMatch() {
    char playerSymbol = '\0', computerSymbol = '\0';
    playerPickSymbol(&playerSymbol, &computerSymbol);
    playTurn(playerSymbol, computerSymbol);
}

void main() {
    srand(time(NULL));
    startMatch();
}