/*
 * stm32f103c6_interrupt.c
 *
 *  Created on: Jul 20, 2023
 *      Author: ahmed
 */


#include "stm32f103c6_interrupt.h"

#define AFIO_EXTI(x) (	(x == GPIOA)?0:(x == GPIOB)?1:(x == GPIOC)?2:(x == GPIOD)?3:-1)

void (*g_p_ISR[15])(void);

static void Update_EXTI(s_exti_pin_Config_t* EXTI_Config);
static void Enable_NVIC (uint16_t IRQ);
static void Disable_NVIC (uint16_t IRQ);
/**================================================================
 * @Fn				- MCAL_EXTI_GPIO_Init
 * @brief			- This Is Used To Initialize EXTI From Specific GPIO PIN and Specify Mask/Trigger Condition and IRQ CallBack
 * @param [in] 		- EXTI_Config: set by @ref EXTI_define, EXTI_Trigger_define and EXTI_IRQ_define
 * @retval 			- None
 * Note				- None
 */
void MCAL_EXTI_GPIO_INIT(s_exti_pin_Config_t* INT_config) {
	Update_EXTI(INT_config);
}


/**================================================================
 * @Fn				- MCAL_EXTI_GPIO_DeInit
 * @brief			- Reset EXTI Registers and NVIC corresponding IRQ Mask
 * @retval 			- None
 * Note				- None
 */
void MCAL_EXIT_GPIO_DEINIT(void) {
	EXTI->IMR 	= 0x00000000;		// Reset value as data-sheet
	EXTI->EMR	= 0x00000000;
	EXTI->RTSR 	= 0x00000000;
	EXTI->FTSR 	= 0x00000000;
	EXTI->SWIER = 0x00000000;
	EXTI->PR 	= 0xFFFFFFFF;		// This bit is cleared by writing one on it.

	/* Disable All EXTI IRQ From NVIC */
	NVIC_IRQ6_EXTI0_DI();
	NVIC_IRQ6_EXTI0_DI();
	NVIC_IRQ7_EXTI1_DI();
	NVIC_IRQ8_EXTI2_DI();
	NVIC_IRQ9_EXTI3_DI();
	NVIC_IRQ10_EXTI4_DI();
	NVIC_IRQ23_EXTI5_9_DI();

}


/**================================================================
 * @Fn				- MCAL_EXTI_GPIO_Update
 * @brief			- This Is Used To Update EXTI From Specific GPIO PIN and Specify Mask/Trigger Condition and IRQ CallBack
 * @param [in] 		- EXTI_Config: set by @ref EXTI_define, EXTI_Trigger_define and EXTI_IRQ_define
 * @retval 			- None
 * Note				- None
 */
void MCAL_EXTI_GPIO_Update(s_exti_pin_Config_t * INT_config) {
	Update_EXTI(INT_config);
}

static void Update_EXTI(s_exti_pin_Config_t * INT_config) {

	// 1- Configure GPIO To Be Alternative Function Input FL:
	s_pinConfig_t pin_config;
	pin_config.pin_number = INT_config->exti_pin.gpio_pin;
	pin_config.pin_mode = GPIO_MODE_INPUT_FL;
	MCAL_GPIO_INIT(INT_config->exti_pin.gpiox,&pin_config);

	//2- Update AFIO to Route between EXTI Line With Port A,B,C,D
	uint8_t EXTICR_idx = INT_config->exti_pin.exti_num / 4;
	uint8_t EXTICR_pos = (INT_config->exti_pin.exti_num % 4) *4;

	AFIO->EXTICR[EXTICR_idx] &= ~(0xf << EXTICR_pos);

	AFIO->EXTICR[EXTICR_idx] |= ((AFIO_EXTI(INT_config->exti_pin.gpiox) & 0xf) << EXTICR_pos);


	// 3- configure Rising / Falling Edge Register
	EXTI->RTSR &= ~(1 << INT_config->exti_pin.exti_num);
	EXTI->FTSR &= ~(1 << INT_config->exti_pin.exti_num);

	if(INT_config->edge_case == EXTI_RT)
	{
		EXTI->RTSR |= (1 << INT_config->exti_pin.exti_num);
	}
	else if (INT_config->edge_case == EXTI_FT)
	{
		EXTI->FTSR |= (1 << INT_config->exti_pin.exti_num);
	}
	else if (INT_config->edge_case == EXTI_RFT)
	{
		EXTI->FTSR |= (1 << INT_config->exti_pin.exti_num);
		EXTI->RTSR |= (1 << INT_config->exti_pin.exti_num);
	}

	// 3- ISR:
	g_p_ISR[INT_config->exti_pin.exti_num] = INT_config->p_ISR;
	// 5- NVIC enable/ disable:
	if(INT_config->enable == EXTI_IRQ_Enable)
	{
		EXTI->IMR |= (1 << INT_config->exti_pin.exti_num);
		Enable_NVIC(INT_config->exti_pin.ivt_num);
	}
	else if(INT_config->enable == EXTI_IRQ_Disable)
	{
		EXTI->IMR &= ~(1 << INT_config->exti_pin.exti_num);
		Disable_NVIC(INT_config->exti_pin.ivt_num);
	}
}



/*=========================================
 * ISR:
==========================================*/

// EXTI0
void EXTI0_IRQHandler (void)
{
	/* Clear By Writing "1" into the bit Pending Register (EXTI_PR) */
	EXTI->PR |= 1 << 0;

	/* Call IRQ_CallBack */
	g_p_ISR[0]();

}

// EXTI1
void EXTI1_IRQHandler (void)
{
	/* Clear By Writing "1" into the bit Pending Register (EXTI_PR) */
	EXTI->PR |= 1 << 1;

	/* Call IRQ_CallBack */
	g_p_ISR[1]();

}

// EXTI2
void EXTI2_IRQHandler (void)
{
	/* Clear By Writing "1" into the bit Pending Register (EXTI_PR) */
	EXTI->PR |= 1 << 2;

	/* Call IRQ_CallBack */
	g_p_ISR[2]();

}

// EXTI3
void EXTI3_IRQHandler (void)
{
	/* Clear By Writing "1" into the bit Pending Register (EXTI_PR) */
	EXTI->PR |= 1 << 3;

	/* Call IRQ_CallBack */
	g_p_ISR[3]();

}

// EXTI4
void EXTI4_IRQHandler (void)
{
	/* Clear By Writing "1" into the bit Pending Register (EXTI_PR) */
	EXTI->PR |= 1 << 4;

	/* Call IRQ_CallBack */
	g_p_ISR[4]();

}

// EXTI5 ---> EXTI9
void EXTI9_5_IRQHandler (void)
{
	if (EXTI->PR & 1<<5)	{EXTI->PR |= (1<<5); g_p_ISR[5]();}
	if (EXTI->PR & 1<<6)	{EXTI->PR |= (1<<6); g_p_ISR[6]();}
	if (EXTI->PR & 1<<7)	{EXTI->PR |= (1<<7); g_p_ISR[7]();}
	if (EXTI->PR & 1<<8)	{EXTI->PR |= (1<<8); g_p_ISR[8]();}
	if (EXTI->PR & 1<<9)	{EXTI->PR |= (1<<9); g_p_ISR[9]();}
}

// EXTI10 ---> EXTI15
void EXTI15_10_IRQHandler (void)
{
	if (EXTI->PR & 1<<10)	{EXTI->PR |= (1<<10); g_p_ISR[10]();}
	if (EXTI->PR & 1<<11)	{EXTI->PR |= (1<<11); g_p_ISR[11]();}
	if (EXTI->PR & 1<<12)	{EXTI->PR |= (1<<12); g_p_ISR[12]();}
	if (EXTI->PR & 1<<13)	{EXTI->PR |= (1<<13); g_p_ISR[13]();}
	if (EXTI->PR & 1<<14)	{EXTI->PR |= (1<<14); g_p_ISR[14]();}
	if (EXTI->PR & 1<<15)	{EXTI->PR |= (1<<15); g_p_ISR[15]();}
}

static void Enable_NVIC (uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_EN();
		break;
	case 1:
		NVIC_IRQ7_EXTI1_EN();
		break;
	case 2:
		NVIC_IRQ8_EXTI2_EN();
		break;
	case 3:
		NVIC_IRQ9_EXTI3_EN();
		break;
	case 4:
		NVIC_IRQ10_EXTI4_EN();
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_EN();
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_EN();
		break;
	}
}

static void Disable_NVIC (uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_DI();
		break;
	case 1:
		NVIC_IRQ7_EXTI1_DI();
		break;
	case 2:
		NVIC_IRQ8_EXTI2_DI();
		break;
	case 3:
		NVIC_IRQ9_EXTI3_DI();
		break;
	case 4:
		NVIC_IRQ10_EXTI4_DI();
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_DI();
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_DI();
		break;
	}
}

