/*
 * Game_Logic.h
 *
 *  Created on: Apr 17, 2025
 *      Author: leo
 */

#ifndef INC_GAME_LOGIC_H_
#define INC_GAME_LOGIC_H_
#include <stdint.h>
#include <stdlib.h>

#define ROWS 6
#define COLUMNS 7
#define INAROW 4 //how many in a row to win- the name of the game is ("Connect %i", inarow)

int8_t** createEmptyBoard();
void freeBoard(int8_t** board);
uint8_t dropPiece(int8_t** board, uint8_t column, int8_t player);
void undropPiece(int8_t** board, uint8_t column);
int8_t checkWin(int8_t** board);
uint8_t checkTie(int8_t** board);
int8_t checkWinDirection(int8_t** board, int8_t x_change, int8_t y_change);

#endif /* INC_GAME_LOGIC_H_ */
