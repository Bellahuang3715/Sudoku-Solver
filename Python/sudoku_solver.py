from __future__ import print_function
import math

# global variables

sudoku = [      [5, 3, 0, 0, 7, 0, 0, 0, 0],
                [6, 0, 0, 1, 9, 5, 0, 0, 0],
                [0, 9, 8, 0, 0, 0, 0, 6, 0],
                [8, 0, 0, 0, 6, 0, 0, 0, 3],
                [4, 0, 0, 8, 0, 3, 0, 0, 1],
                [7, 0, 0, 0, 2, 0, 0, 0, 6],
                [0, 6, 0, 0, 0, 0, 2, 8, 0],
                [0, 0, 0, 4, 1, 9, 0, 0, 5],
                [0, 0, 0, 0, 8, 0, 0, 7, 9]    ]

solution = [    [5, 3, 4, 6, 7, 8, 9, 1, 2],
                [6, 7, 2, 1, 9, 5, 3, 4, 8],
                [1, 9, 8, 3, 4, 2, 5, 6, 7],
                [8, 5, 9, 7, 6, 1, 4, 2, 3],
                [4, 2, 6, 8, 5, 3, 7, 9, 1],
                [7, 1, 3, 9, 2, 4, 8, 5, 6],
                [9, 6, 1, 5, 3, 7, 2, 8, 4],
                [2, 8, 7, 4, 1, 9, 6, 3, 5],
                [3, 4, 5, 2, 8, 6, 1, 7, 9]     ]

boardSize = len(sudoku)
cellSize = math.sqrt(boardSize)

# print the sudoku board
def print_board(board):
    print(" ----------------------- ")
    for i in range(boardSize):
        for j in range(boardSize):
            if j % cellSize == 0:
                print("| ", end="")
            print(board[i][j], end=" ")
        print("|", end="")
        if (i+1) % cellSize == 0:
            print()
            print(" ----------------------- ", end="")
        print()
    print("\n" * 2) 


# Function that finds the next empty space in the sudoku board

def empty_space(board):
    for row in range(boardSize):
        for col in range(boardSize):
            if board[row][col] == 0:
                return (row, col)
    return None


# Function that checks whether the current position is valid

def sudoku_solver(board):
    find = empty_space(board)
    if not find:
        return True
    else:
        row, col = find
    for num in range(1, 10):
        if valid_position(board, num, (row, col)):
            board[row][col] = num
            if sudoku_solver(board):
                return True
            board[row][col] = 0
    return False


# Function that checks if the number is valid in current position

def valid_position(board, num, pos):
    # Check row
    for col in range(len(board[0])):
        if board[pos[0]][col] == num and pos[1] != col:
            return False
    # Check column
    for row in range(len(board)):
        if board[row][pos[1]] == num and pos[0] != row:
            return False
    # Check box
    box_x = pos[1] // 3
    box_y = pos[0] // 3
    for i in range(box_y*3, box_y*3 + 3):
        for j in range(box_x * 3, box_x*3 + 3):
            if board[i][j] == num and (i,j) != pos:
                return False
    return True


# MAIN
def main():
    print("Original array: ")
    print_board(sudoku)
    print("Expected solution: ")
    print_board(solution)
    print("Solved sudoku board: ")
    sudoku_solver(sudoku)
    print_board(sudoku)

# Call on Main Function
main()
