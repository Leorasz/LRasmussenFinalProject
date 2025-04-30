/*
 * Game_Logic.c
 *
 *  Created on: Apr 17, 2025
 *      Author: leo
 */
#include "Game_Logic.h"

int8_t** createEmptyBoard() {
    //6 rows, 7 columns
    int8_t** res = (int8_t**)malloc(ROWS*sizeof(int8_t*)); //pointer to all the pointers for each row
    for (int i = 0; i < ROWS; i++) {
        res[i] = (int8_t*)calloc(COLUMNS, sizeof(int8_t)); //calloc sets em to 0
    }
    return res;

}

void freeBoard(int8_t** board) {
    for (int i = 0; i < ROWS; i++) {
        free(board[i]);
    }
    free(board);
}

uint8_t dropPiece(int8_t** board, uint8_t column, int8_t player) { //return is whether or not it was successful
    for (int i = ROWS - 1; i > -1; i--) { //0 is the highest row, so start from bottom up to save computation
        if (!board[i][column]) {
            board[i][column] = player;
            return 1;
        }
    }
    return 0;
}

void undropPiece(int8_t** board, uint8_t column) {
	for (int i = 0; i < ROWS; i++) {
		if (board[i][column]) {
			board[i][column] = 0;
			break;
		}
	}
}

int8_t checkWin(int8_t** board) {
	if (checkTie(board)) {
		return 2;
	}
    //4 directions for winning- downleft, down, downright, right
    int8_t downleft = checkWinDirection(board, -1, 1);
    int8_t down = checkWinDirection(board, 0, 1);
    int8_t downright = checkWinDirection(board, 1, 1);
    int8_t right = checkWinDirection(board, 1, 0);
    //with the way i have it set up this gives the right answer, unless something gets really messed up
    int8_t big_winner = downleft + down + downright + right;
    if (big_winner > 0) {
    	return 1;
    } else if (big_winner < 0) {
    	return -1;
    } else {
    	return 0;
    }
}

uint8_t checkTie(int8_t** board) {
	for (int i = 0; i < ROWS; i++) {
		if (board[0][i] == 0) {
			return 0;
		}
	}

	return 1;
}

int8_t checkWinDirection(int8_t** board, int8_t x_change, int8_t y_change) {
    for (int i = 0; i < ROWS - y_change * (INAROW - 1); i++) {
        int j_start = 0;
        int j_end = COLUMNS;
        if (x_change == -1) {
            j_start = INAROW - 1;
        } else if (x_change == 1) {
            j_end = COLUMNS - INAROW + 1;
        }
        for (int j = j_start; j < j_end; j++) {
            int8_t sum = 0;
            for (int k = 0; k < INAROW; k++) {
                sum += board[i + y_change * k][j + x_change * k];
            }
            if (sum == INAROW) return 1;    // Player 1 wins
            if (sum == -INAROW) return -1;  // Player -1 wins
        }
    }
    return 0;  // No win
}
