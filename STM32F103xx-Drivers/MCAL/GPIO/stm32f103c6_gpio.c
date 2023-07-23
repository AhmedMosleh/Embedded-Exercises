/*================================================================
 * @file           : stm32f103c6_gpio.c
 * @author         : Ahmed Mostafa Mosleh
 * @brief          : gpio driver
 *================================================================*/

#include "stm32f103c6_gpio.h"


/*=========================================
 * Internal Functions in MCAL GPIO Driver
==========================================*/

uint8_t MACL_PIN_POS(uint16_t pinNum);

/*================================================================
 * @Function:	-MACL_PIN_POS_CR
 * @brief:
 * @param [in]:
 * @param [out]:
 * @retval:
 * Note:
 *================================================================*/

uint8_t MACL_PIN_POS_CR(uint16_t pinNum)
{
	switch (pinNum)
	{
	case GPIO_PIN_0:
	case GPIO_PIN_8:
		return 0;
		break;
	case GPIO_PIN_1:
	case GPIO_PIN_9:
		return 4;
		break;
	case GPIO_PIN_2:
	case GPIO_PIN_10:
		return 8;
		break;
	case GPIO_PIN_3:
	case GPIO_PIN_11:
		return 12;
		break;
	case GPIO_PIN_4:
	case GPIO_PIN_12:
		return 16;
		break;
	case GPIO_PIN_5:
	case GPIO_PIN_13:
		return 20;
		break;
	case GPIO_PIN_6:
	case GPIO_PIN_14:
		return 24;
		break;

	case GPIO_PIN_7:
	case GPIO_PIN_15:
		return 28;
		break;
	default:
		break;
	}
	return 0;
}

/*================================================================================================================
 * @Fn           : MCAL_GPIO_Init
 * @brief        : Initializes the GPIOx PINy according to the specified parameters in PinConfig
 * @param [in 1] : GPIOx: where x can be (A..E depending on device used) to select GPIO peripheral
 * @param [in 2] : PinConfig pointer to a GPIO_PinConfig_t structure that contains
 * Note          : Stm32F103C6 MCU has GPIO A, B, C, D, E Modules
 * 				   But LQFP48 Package has only GPIO A, B, PART of C/D exported as external PINs from the Module
 *===============================================================================================================*/

void MCAL_GPIO_INIT(s_gpio_t *gpiox, s_pinConfig_t *pinConfig)
{
	// GPIOx_CRL (0:7) | GPIOx_CRL (8:15)
	volatile uint32_t *GPIOx_CRLH = (pinConfig->pin_number < GPIO_PIN_8) ? (&(gpiox->CRL)) : (&(gpiox->CRH));

	// get the shift position in configuration REG (cr).
	uint8_t pin_pos_cr = MACL_PIN_POS_CR(pinConfig->pin_number);
	// Rest configuration bits of the given pin
	(*GPIOx_CRLH) &= ~(0xFUL << pin_pos_cr);

	// set configuration bits of the given pins as following:
	//bits                          | cnf1 | cnf0 | mode1 | mode0 | PxODR 	| output => cnf1&cnf0
	//GPIO_MODE_ANALOG 0x0u         |  0   |  0   |	  0   |   0   |  n/a	|
	//GPIO_MODE_INPUT_FL 0x1u       |  0   |  1   |	  0   |   0   |  n/a	|
	//GPIO_MODE_INPUT_PU 0x2u       |  1   |  0   |	  0   |   0   |   1		|
	//GPIO_MODE_INPUT_PD 0x3u       |  1   |  0   |	  0   |   0   |   0		|
	//GPIO_MODE_OUTPUT_PP 0x4u      |  0   |  0   |	  0   |   1   |  n/a	| 4 => 0
	//GPIO_MODE_OUTPUT_OD 0x5u      |  0   |  1   |	  0   |   0   |  n/a	| 5 => 1
	//GPIO_MODE_OUTPUT_AF_PP 0x6u   |  1   |  0   |	  1   |   1   |  n/a	| 6 => 2
	//GPIO_MODE_OUTPUT_AF_OD 0x7u   |  1   |  1   |	  1   |   1   |  n/a	| 7 => 3
	//GPIO_MODE_INPUT_AF 0x8u       |  0   |  1   |	  0   |   0   |  n/a	|

	// template variable to contain configuration
	uint8_t temp_config = 0;

	switch (pinConfig->pin_mode)
	{
	// if pin is output:
	case GPIO_MODE_OUTPUT_PP:
	case GPIO_MODE_OUTPUT_OD:
	case GPIO_MODE_OUTPUT_AF_PP:
	case GPIO_MODE_OUTPUT_AF_OD:
		// there is a linear relation ship between
		temp_config = ((pinConfig->pin_mode - 4) << 2 ) | (pinConfig->pin_output_speed & (0x0f));
		break;
		// if pin is input:
	case GPIO_MODE_ANALOG:
	case GPIO_MODE_INPUT_FL:
		//case GPIO_MODE_INPUT_AF:
		temp_config = ((pinConfig->pin_mode) << 2 );
		break;
	case GPIO_MODE_INPUT_PU:
		temp_config = ((pinConfig->pin_mode) << 2 );
		gpiox->ODR |= (pinConfig->pin_number);
		break;
	case GPIO_MODE_INPUT_PD:
		temp_config = ((pinConfig->pin_mode - 4) << 2 );
		gpiox->ODR &= ~(pinConfig->pin_number);
		break;
	default:
		break;
	}
	// assign temp config to configuration reg
	// note the temp_config is 8 bits if we do the following we will over write anther pin configuration.
	(*GPIOx_CRLH) |= (temp_config << pin_pos_cr);

}

/**================================================================
 * @Fn				- MCAL_GPIO_DeInit
 * @brief			- Reset all the GPIO Registers
 * @param [in] 		- GPIOx: where x can be (A..E depending on device used) to select GPIO peripheral
 * @retval 			- None
 * Note				- None
 */
void MCAL_GPIO_DE_INIT(s_gpio_t *gpiox)
{
	/* GPIOx->CRL = 0x44444444;
	 * GPIOx->CRH = 0x44444444;
	 * GPIOx->IDR = ; (Read only)
	 * GPIOx->ODR = 0x00000000;
	 * GPIOx->BSRR = 0x00000000;
	 * GPIOx->BRR = 0x00000000;
	 * GPIOx->LCKR = 0x00000000;
	 */

	if(gpiox == GPIOA)
	{
		RCC->APB2RSTR |= (1<<2);
		RCC->APB2RSTR &= ~(1<<2);
	}
	else if (gpiox == GPIOB)
	{
		RCC->APB2RSTR |= (1<<3);
		RCC->APB2RSTR &= ~(1<<3);
	}
	else if (gpiox == GPIOC)
	{
		RCC->APB2RSTR |= (1<<4);
		RCC->APB2RSTR &= ~(1<<4);
	}
	else if (gpiox == GPIOD){
		RCC->APB2RSTR |= (1<<5);
		RCC->APB2RSTR &= ~(1<<5);
	}
	else if (gpiox == GPIOE)
	{
		RCC->APB2RSTR |= (1<<6);
		RCC->APB2RSTR &= ~(1<<6);
	}


}

/**================================================================
 * @Fn				- MCAL_GPIO_ReadPin
 * @brief			- Read Specific PIN
 * @param [in] 		- GPIOx: where x can be (A..E depending on device used) to select GPIO peripheral
 * @param [in] 		- PinNumber: Set Pin Number according to @ref GPIO_PINS_define
 * @retval 			- The input pin value (two values based on @ref GPIO_PIN_state)
 * Note				- None
 */
uint8_t MCAL_GPIO_READ_PIN(s_gpio_t *gpiox, uint16_t pinNum)
{

	if((gpiox->IDR) & pinNum)
	{
		return GPIO_PIN_SET;
	}
	return GPIO_PIN_RESET;

}
/**================================================================
 * @Fn				- MCAL_GPIO_ReadPort
 * @brief			- Read Specific PORT
 * @param [in] 		- GPIOx: where x can be (A..E depending on device used) to select GPIO peripheral
 * @retval 			- The input port value
 * Note				- None
 */
uint16_t MCAL_GPIO_READ_PORT(s_gpio_t *gpiox)
{
	return (uint16_t)(gpiox->IDR);
}

/**================================================================
 * @Fn				- MCAL_GPIO_WritePin
 * @brief			- Write on Specific pin
 * @param [in] 		- GPIOx: where x can be (A..E depending on device used) to select GPIO peripheral
 * @param [in] 		- PinNumber: specific the port bit to read @ref GPIO_PINS_define
 * @param [in] 		- Value: Pin value
 * @retval 			- None
 * Note				- None
 */
void MCAL_GPIO_WRITE_PIN(s_gpio_t *gpiox, uint16_t pinNum, uint8_t value)
{
	if (value)
	{
		//gpiox->ODR |= PinNumber;
		//OR by using BSRR register
		gpiox->BSRR = (uint32_t)pinNum;
	}
	gpiox->BRR = (uint32_t)pinNum;
}

/**================================================================
 * @Fn				- MCAL_GPIO_WritePort
 * @brief			- Write on Specific PORT
 * @param [in] 		- GPIOx: where x can be (A..E depending on device used) to select GPIO peripheral
 * @param [in] 		- Value: Port value
 * @retval 			- None
 * Note				- None
 */
void MCAL_GPIO_WRITE_PORT(s_gpio_t *gpiox, uint16_t value)
{
	gpiox->ODR = (uint32_t)value;
}

/**================================================================
 * @Fn				- MCAL_GPIO_TogglePin
 * @brief			- Toggle Specific pin
 * @param [in] 		- GPIOx: where x can be (A..E depending on device used) to select GPIO peripheral
 * @param [in] 		- PinNumber: specific the port bit to read @ref GPIO_PINS_define
 * @retval 			- None
 * Note				- None
 */
void MCAL_GPIO_TOGGLE_PIN(s_gpio_t *gpiox, uint16_t pinNum)
{
	gpiox->ODR ^= (pinNum);
}


/**================================================================
 * @Fn				- MCAL_GPIO_LockPin
 * @brief			- The locking mechanism allows the IO configuration to be frozen
 * @param [in] 		- GPIOx: where x can be (A..E depending on device used) to select GPIO peripheral
 * @param [in] 		- PinNumber: specific the port bit to read @ref GPIO_RETURN_LOCK
 * @retval 			- OK if pin configure is locked Or ERROR if pin is not locked (OK & ERROR are defined @ref GPIO_RETURN_LOCK)
 * Note				- None
 */
uint8_t MCAL_GPIO_LOCK_PIN(s_gpio_t *gpiox, uint16_t pinNum)
{
	//Set LCKK[16]
	volatile uint32_t temp = 1<<16;

	//Set the LCKy
	temp |= pinNum;

	//Write 1
	gpiox->LCKR = temp;

	//Write 0
	gpiox->LCKR = pinNum;

	//Write 1
	gpiox->LCKR = temp;

	//Read 0
	temp = gpiox->LCKR;

	//Read 1 (this read is optional but confirms that the lock is active)
	if((uint32_t)gpiox->LCKR & 1<<16)
	{
		return GPIO_RETURN_LOCK_Enabled;
	}
	else
	{
		return GPIO_RETURN_LOCK_ERROR;
	}
}
