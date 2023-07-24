/*
 * Keypad.c
 *
 *  Created on: 18/7/2023
 *      Author: Ahmed Mosleh
 */

#include "keypad.h"

uint32_t keypad_R[] = {R0, R1, R2, R3}; // Rows of the keypad
uint32_t keypad_C[] = {C0, C1, C2, C3}; // Columns of the keypad

uint8_t chr[4][4] =	{{'7','8','9','/'},
		{'4','5','6','*'},
		{'1','2','3','-'},
		{'$','0','=','+'}};

/* ========================================== */
/* ========== Functions Definitions ========= */
/* ========================================== */

void HAL_KEYPAD_INIT(void)
{
	// ALL ROWS and COLUMNS are OUTPUT

	GPIO_PinConfig_t PinConfig;

	PinConfig.GPIO_PinNumber = R0;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_OD;
	PinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	PinConfig.GPIO_PinNumber = R1;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_OD;
	PinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	PinConfig.GPIO_PinNumber = R2;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_OD;
	PinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	PinConfig.GPIO_PinNumber = R3;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_OD;
	PinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	PinConfig.GPIO_PinNumber = C0;
	PinConfig.GPIO_MODE = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	PinConfig.GPIO_PinNumber = C1;
	PinConfig.GPIO_MODE = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	PinConfig.GPIO_PinNumber = C2;
	PinConfig.GPIO_MODE = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	PinConfig.GPIO_PinNumber = C3;
	PinConfig.GPIO_MODE = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	//	MCAL_GPIO_WritePort(KEYPAD_PORT, 0xFF);
}

// Function to get the key pressed on the Keypad
// And return it as char to send it to LCD



static uint8_t KP_GET_COL(void)
{
	if (MCAL_GPIO_ReadPin(KEYPAD_PORT, C0) == GPIO_PIN_RESET)
		return 0;
	else if (MCAL_GPIO_ReadPin(KEYPAD_PORT, C1) == GPIO_PIN_RESET)
		return 1;
	else if (MCAL_GPIO_ReadPin(KEYPAD_PORT, C2) == GPIO_PIN_RESET)
		return 2;
	else if (MCAL_GPIO_ReadPin(KEYPAD_PORT, C3) == GPIO_PIN_RESET)
		return 3;
	return -1;
}


static uint8_t KP_GET_ROW(uint8_t col)
{
	for(uint8_t i = 0; i < 4; i++) {
		MCAL_GPIO_WritePin(KEYPAD_PORT, keypad_R[0], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, keypad_R[1], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, keypad_R[2], GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, keypad_R[3], GPIO_PIN_SET);

		MCAL_GPIO_WritePin(KEYPAD_PORT, keypad_R[i], GPIO_PIN_SET);

		if(MCAL_GPIO_ReadPin(KEYPAD_PORT, keypad_R[col]) == GPIO_PIN_RESET)
			return i;
	}
	return -1;
}


char HAL_KEYPAD_GET_KEY(void)
{
	// write 0 to rows
	MCAL_GPIO_WritePin(KEYPAD_PORT, keypad_R[0], GPIO_PIN_SET);
	MCAL_GPIO_WritePin(KEYPAD_PORT, keypad_R[1], GPIO_PIN_SET);
	MCAL_GPIO_WritePin(KEYPAD_PORT, keypad_R[2], GPIO_PIN_SET);
	MCAL_GPIO_WritePin(KEYPAD_PORT, keypad_R[3], GPIO_PIN_SET);
	// check if any col be 0 => pressed
	sint8_t col = -1;
	sint8_t row = -1;
	while(col == -1) {
		col = KP_GET_COL();
	}

	// check which button in col
	row = KP_GET_ROW(col);
	return chr[row][col];


}
