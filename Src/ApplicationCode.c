/*
 * ApplicationCode.c
 *
 *  Created on: Dec 30, 2023 (updated 11/12/2024) Thanks Donavon! 
 *      Author: Xavion
 */

#include "ApplicationCode.h"

/* Static variables */


extern void initialise_monitor_handles(void); 

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#endif // COMPILE_TOUCH_FUNCTIONS

static uint8_t player1_wins;
static uint8_t player2_wins;

void ApplicationInit(void)
{
	initialise_monitor_handles(); // Allows printf functionality
    LTCD__Init();
    LTCD_Layer_Init(0);
    LCD_Clear(0,LCD_COLOR_WHITE);
    Button_Init();

    #if COMPILE_TOUCH_FUNCTIONS == 1
	InitializeLCDTouch();

	// This is the orientation for the board to be direclty up where the buttons are vertically above the screen
	// Top left would be low x value, high y value. Bottom right would be low x value, low y value.
	StaticTouchData.orientation = STMPE811_Orientation_Portrait_2;

	#endif // COMPILE_TOUCH_FUNCTIONS
}

void LCD_Visual_Demo(void)
{
	visualDemo();
}

#if COMPILE_TOUCH_FUNCTIONS == 1
void LCD_Touch_Polling_Demo(void)
{
	LCD_Clear(0,LCD_COLOR_GREEN);
	while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			if (StaticTouchData.x < 120) {
				LCD_Clear(0, LCD_COLOR_RED);
			}
			else {
				LCD_Clear(0, LCD_COLOR_BLUE);
			}
		} else {
			/* Touch not pressed */
			printf("Not Pressed\n\n");
			LCD_Clear(0, LCD_COLOR_GREEN);
		}
	}
}
#endif // COMPILE_TOUCH_FUNCTIONS

static uint8_t player1_wins;
static uint8_t player2_wins;
static int8_t mode;
static RNG_HandleTypeDef rng_instance;
static RNG_HandleTypeDef* hrng = &rng_instance;
static int8_t player;
static uint8_t drop_column;
static int8_t** board;
static uint32_t last_drop_time;
static uint8_t win_status;

void start(void) {
    startScreen();
    mode = getLeftRightScreenInput();
    if (mode == -1) {
        hrng->Instance = RNG;
        hrng->Lock = HAL_UNLOCKED;
        HAL_RNG_Init(hrng);
    }
    while (1) {
        game();
    }
}

uint8_t rngAIMove() {
    uint32_t random_number;
    HAL_RNG_GenerateRandomNumber(hrng, &random_number);
    return random_number % 7;
}

uint8_t optimalMove() { //EXTRA CREDIT
	//first check if computer can win
	for (int i = 0; i < COLUMNS; i++) {
		if (dropPiece(board, i, -1)) {
			int8_t winner = checkWin(board);
			undropPiece(board, i);
			if (winner) {
				return i;
			}
		}
	}
	//then check if the player can win
	for (int i = 0; i < COLUMNS; i++) {
		if (dropPiece(board, i, 1)) {
			int8_t winner = checkWin(board);
			undropPiece(board, i);
			if (winner) {
				return i;
			}
		}
	}
	//else just randomly pick one biased toward the center
	return (rngAIMove() + rngAIMove())/2;
}

void game(void) {
    board = createEmptyBoard();
    player = 1;
    drop_column = 3;
    uint16_t start_time = HAL_GetTick();
    while (1) {
        displayBoard(drop_column, player, board);
        if (!(player == -1 && mode == -1)) {
            int8_t move = getLeftRightScreenInput();
            HAL_Delay(500);
            if (!((drop_column == 0 && move == -1) || (drop_column == 6 && move == 1))) {
                drop_column += move;
            }
        } else {
            drop_column = optimalMove();
            while (player_turn()) {
            	drop_column = (drop_column + 1) % 7;
            }
            HAL_Delay(500);
            displayBoard(drop_column, player, board);
        }
        int8_t winner = checkWin(board);
        if (winner != 0) {
        	uint16_t elapsed_time = (HAL_GetTick() - start_time) / 1000;
        	win_status = 1;
            if (winner == 1) {
                player1_wins++;
            } else if (winner == -1){
                player2_wins++;
            }
            winScreen(winner, player1_wins, player2_wins, elapsed_time);
            while (win_status) {
            	HAL_Delay(100);
            }
            break;
        }
    }
}


uint8_t player_turn() {
    if (dropPiece(board, drop_column, player)) {
        player *= -1;
        drop_column = 3;
        displayBoard(drop_column, player, board);
        return 0;
    }
    return 1;
}

void EXTI0_IRQHandler() {
    uint32_t current_time = HAL_GetTick();
    if (current_time - last_drop_time < 500) {
        return;
    }
    last_drop_time = current_time;
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);
    if (!win_status) {
    	if (!(player == -1 && mode == -1)) {
    		player_turn();
    	}
    } else {
    	win_status = 0;
    }
}



