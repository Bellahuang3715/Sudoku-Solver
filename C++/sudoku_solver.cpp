#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>
#include <array>
#include <unordered_set>

using namespace std;

#define BOARD_SIZE 9

int cellSize = sqrt(BOARD_SIZE);
char board[BOARD_SIZE][BOARD_SIZE] = {{'5', '3', ' ', ' ', '7', ' ', ' ', ' ', ' '}, {'6', ' ', ' ', '1', '9', '5', ' ', ' ', ' '}, {' ', '9', '8', ' ', ' ', ' ', ' ', '6', ' '}, {'8', ' ', ' ', ' ', '6', ' ', ' ', ' ', '3'}, {'4', ' ', ' ', '8', ' ', '3', ' ', ' ', '1'}, {'7', ' ', ' ', ' ', '2', ' ', ' ', ' ', '6'}, {' ', '6', ' ', ' ', ' ', ' ', '2', '8', ' '}, {' ', ' ', ' ', '4', '1', '9', ' ', ' ', '5'}, {' ', ' ', ' ', ' ', '8', ' ', ' ', '7', '9'}};
char solution[BOARD_SIZE][BOARD_SIZE] = {{'5', '3', '4', '6', '7', '8', '9', '1', '2'}, {'6', '7', '2', '1', '9', '5', '3', '4', '8'}, {'1', '9', '8', '3', '4', '2', '5', '6', '7'}, {'8', '5', '9', '7', '6', '1', '4', '2', '3'}, {'4', '2', '6', '8', '5', '3', '7', '9', '1'}, {'7', '1', '3', '9', '2', '4', '8', '5', '6'}, {'9', '6', '1', '5', '3', '7', '2', '8', '4'}, {'2', '8', '7', '4', '1', '9', '6', '3', '5'}, {'3', '4', '5', '2', '8', '6', '1', '7', '9'}};

bool validSudoku();
bool empty_space(char &board);
bool valid_in_row(char &board, int row, char num);
bool valid_in_col(char &board, int col, char num);
bool valid_position(char &board, int row, int col, char num);
bool sudoku_solver(char board[][BOARD_SIZE]);
std::pair<char, char> next_empty_position(char board[][BOARD_SIZE], int row, int col);
void printBoard(char &board);


/* check if the given sudoku board is valid */

bool validSudoku() {
    int row = 0, col = 0;
    std::unordered_set<char> rowSeen;
    std::unordered_set<char> colSeen;
    std::unordered_set<char> cellSeen;

    // check if the rows and colums are valid
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            char rowNum = board[row][col];
            char colNum = board[col][row];
            if (rowNum != ' ') {
                if ((rowSeen.find(rowNum) != rowSeen.end())) {
                    return false;
                }
                rowSeen.insert(rowNum);
            }
            if (colNum != ' ') {
                if ((colSeen.find(colNum) != colSeen.end())) {
                    return false;
                }
                colSeen.insert(colNum);
            }
        }
        rowSeen.clear();
        colSeen.clear();
    }

    // check if the cells are valid
    int rowOffset = 0, colOffset = 0;
    int iteration = 1;
    while (iteration <= 9) {
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                char cellNum = board[row + rowOffset][col + colOffset];
                if (cellNum != ' ') {
                    if (cellSeen.find(cellNum) != cellSeen.end()) {
                        return false;
                    }
                    cellSeen.insert(cellNum);
                }
            }
        }
        colOffset += 3;
        if (iteration % 3 == 0) {
            rowOffset += 3;
            colOffset = 0;
        }
        cellSeen.clear();
        iteration++;
    }
    return true;
}


/* check if there is any more empty spaces on the sudoku board */

bool empty_space(char board[][BOARD_SIZE]) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == ' ') {
                return true;
            }
        }
    }
    return false;
}


/* helper functions for checking validity */

bool valid_in_row(char board[][BOARD_SIZE], int row, char num) {
    for (int col = 0; col < BOARD_SIZE; col++) {
        if (board[row][col] == num) {
            return false;
        }
    }
    return true;
}

bool valid_in_col(char board[][BOARD_SIZE], int col, char num) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        if (board[row][col] == num) {
            return false;
        }
    }
    return true;
}

bool valid_in_cell(char board[][BOARD_SIZE], int rowOffset, int colOffset, char num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row + rowOffset][col + colOffset] == num) {
                return false;
            }
        }
    }
    return true;
}


/* function that calls on other helper functions to ensure that the number in the current position is valid */

bool valid_position(char board[][BOARD_SIZE], int row, int col, char num) {
    return (valid_in_row(board, row, num)) && (valid_in_col(board, col, num)) && (valid_in_cell(board, row - row % 3 ,col - col % 3, num));
}


/* function that utilizes backtracking to solve the sudoku */

bool sudoku_solver(char board[][BOARD_SIZE]) {
    std::pair<char, char> current_position = next_empty_position(board, 0, 0);
    int row = current_position.first, col = current_position.second;
    // if no more empty spaces can be found, sudoku solved
    if (!empty_space(board)) {
        return true;
    }
    // try numbers 1-9 in each empty space
    for (int num = 1; num <= 9; num++) {
        char charNum = '0' + num;
        // if number is valid, put it in current position
        if (valid_position(board, row, col, charNum)) {
            board[row][col] = charNum;
            // call function recursively to go to other empty positions
            if (sudoku_solver(board))
                return true;
            board[row][col] = ' ';
        }
   }
   return false;
}


/* find the next empty position on the sudoku board */

std::pair<char, char> next_empty_position(char board[][BOARD_SIZE], int row, int col) {
    for (int i = row; i < BOARD_SIZE; i++) {
        for (int j = col; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                return std::make_pair(i, j);
            }
        }
    }
    return std::make_pair(-1, -1);
}


/* print the sudoku board */

void printBoard(char board[][BOARD_SIZE]) {
    cout << " ----------------------- " << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (j % cellSize == 0) {
                cout << "| ";
            }
            cout << board[i][j] << " ";
        }
        cout << "|";
        if ((i+1) % cellSize == 0) {
            cout << endl << " ----------------------- ";
        }
        cout << endl;
    }
    cout << endl << endl;
}


/* MAIN */

int main() {
    cout << "Original array: " << endl;
    printBoard(board);
    cout << "Expected solution: " << endl;
    printBoard(solution);
    // given sudoku board may NOT be valid
    if (!validSudoku()) {
        cout << "The given sudoku board is NOT valid" << endl;
    }
    else {
        cout << "The given sudoku board is valid" << endl;
    }
    // a valid sukoku board is NOT necesary solvable
    if (sudoku_solver(board)) {
        cout << "Solved sudoku: " << endl;
        printBoard(board);
    }
    else {
        cout << "No possible solution exists for given sudoku board" << endl;
        printBoard(board);
    }
    return 0;
}