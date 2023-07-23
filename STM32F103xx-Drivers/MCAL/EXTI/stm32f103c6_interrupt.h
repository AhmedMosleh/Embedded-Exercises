/*
 * stm32f103c6_interrupt.h
 *
 *  Created on: Jul 20, 2023
 *      Author: ahmed
 */

#ifndef INC_STM32F103C6_INTERRUPT_H_
#define INC_STM32F103C6_INTERRUPT_H_

/*=========================================
 * Includes
==========================================*/

#include "stm32f103c6.h"
#include "stm32f103c6_gpio.h"

/*=========================================
 * Configuration Stucts:
==========================================*/

typedef struct
{
	s_gpio_t* gpiox;
	uint16_t gpio_pin;
	uint8_t exti_num; // could be uint16_t
	uint8_t ivt_num;
}s_exti_gpio_t;


typedef struct
{
	s_exti_gpio_t exti_pin; // Specifics the EXTI GPIO Mapping
							// This parameter must be set based on @ref EXTI_define

	uint8_t edge_case;		// Specifics RISING or FALLING or Both trigger
							// This parameter must be set based on @ref EXTI_Trigger_define

	uint8_t enable;			// Enable or Disable the EXTI IRQ (That will enable the IRQ mask in EXTI and also on the NVIC Interrupt contoller)
							// This parameter must be set based on @ref EXTI_IRQ_define
	void(*p_ISR)(void); 	// Set the c Function() which will be called once the IRQ happen
}s_exti_pin_Config_t;



/*=========================================
 * Macros Configuration References:
 *==========================================*/

#define EXTI0		0
#define EXTI1		1
#define EXTI2		2
#define EXTI3		3
#define EXTI4		4
#define EXTI5		5
#define EXTI6		6
#define EXTI7		7
#define EXTI8		8
#define EXTI9		9
#define EXTI10		10
#define EXTI11		11
#define EXTI12		12
#define EXTI13		13
#define EXTI14		14
#define EXTI15		15

//@ref EXTI_IRQ_define
#define EXTI_IRQ_Enable					1
#define EXTI_IRQ_Disable				0

//@ref EXTI_Trigger_define

#define EXTI_RT		0
#define EXTI_FT		1
#define EXTI_RFT	2

//@ ref EXTI_define

//EXTI0
#define EXTI0PA0        (s_exti_gpio_t){EXTI0, GPIOA, GPIO_PIN_0, EXTI0_IRQ}
#define EXTI0PB0        (s_exti_gpio_t){EXTI0, GPIOB, GPIO_PIN_0, EXTI0_IRQ}
#define EXTI0PC0        (s_exti_gpio_t){EXTI0, GPIOC, GPIO_PIN_0, EXTI0_IRQ}
#define EXTI0PD0        (s_exti_gpio_t){EXTI0, GPIOD, GPIO_PIN_0, EXTI0_IRQ}


//EXTI1
#define EXTI1PA1        (s_exti_gpio_t){EXTI1, GPIOA, GPIO_PIN_1, EXTI1_IRQ}
#define EXTI1PB1        (s_exti_gpio_t){EXTI1, GPIOB, GPIO_PIN_1, EXTI1_IRQ}
#define EXTI1PC1        (s_exti_gpio_t){EXTI1, GPIOC, GPIO_PIN_1, EXTI1_IRQ}
#define EXTI1PD1        (s_exti_gpio_t){EXTI1, GPIOD, GPIO_PIN_1, EXTI1_IRQ}


//EXTI2
#define EXTI2PA2        (s_exti_gpio_t){EXTI2, GPIOA, GPIO_PIN_2, EXTI2_IRQ}
#define EXTI2PB2        (s_exti_gpio_t){EXTI2, GPIOB, GPIO_PIN_2, EXTI2_IRQ}
#define EXTI2PC2        (s_exti_gpio_t){EXTI2, GPIOC, GPIO_PIN_2, EXTI2_IRQ}
#define EXTI2PD2        (s_exti_gpio_t){EXTI2, GPIOD, GPIO_PIN_2, EXTI2_IRQ}


//EXTI3
#define EXTI3PA3        (s_exti_gpio_t){EXTI3, GPIOA, GPIO_PIN_3, EXTI3_IRQ}
#define EXTI3PB3        (s_exti_gpio_t){EXTI3, GPIOB, GPIO_PIN_3, EXTI3_IRQ}
#define EXTI3PC3        (s_exti_gpio_t){EXTI3, GPIOC, GPIO_PIN_3, EXTI3_IRQ}
#define EXTI3PD3        (s_exti_gpio_t){EXTI3, GPIOD, GPIO_PIN_3, EXTI3_IRQ}


//EXTI4
#define EXTI4PA4        (s_exti_gpio_t){EXTI4, GPIOA, GPIO_PIN_4, EXTI4_IRQ}
#define EXTI4PB4        (s_exti_gpio_t){EXTI4, GPIOB, GPIO_PIN_4, EXTI4_IRQ}
#define EXTI4PC4        (s_exti_gpio_t){EXTI4, GPIOC, GPIO_PIN_4, EXTI4_IRQ}
#define EXTI4PD4        (s_exti_gpio_t){EXTI4, GPIOD, GPIO_PIN_4, EXTI4_IRQ}


//EXTI5
#define EXTI5PA5        (s_exti_gpio_t){EXTI5, GPIOA, GPIO_PIN_5, EXTI5_IRQ}
#define EXTI5PB5        (s_exti_gpio_t){EXTI5, GPIOB, GPIO_PIN_5, EXTI5_IRQ}
#define EXTI5PC5        (s_exti_gpio_t){EXTI5, GPIOC, GPIO_PIN_5, EXTI5_IRQ}
#define EXTI5PD5        (s_exti_gpio_t){EXTI5, GPIOD, GPIO_PIN_5, EXTI5_IRQ}


//EXTI6
#define EXTI6PA6        (s_exti_gpio_t){EXTI6, GPIOA, GPIO_PIN_6, EXTI6_IRQ}
#define EXTI6PB6        (s_exti_gpio_t){EXTI6, GPIOB, GPIO_PIN_6, EXTI6_IRQ}
#define EXTI6PC6        (s_exti_gpio_t){EXTI6, GPIOC, GPIO_PIN_6, EXTI6_IRQ}
#define EXTI6PD6        (s_exti_gpio_t){EXTI6, GPIOD, GPIO_PIN_6, EXTI6_IRQ}


//EXTI7
#define EXTI7PA7        (s_exti_gpio_t){EXTI7, GPIOA, GPIO_PIN_7, EXTI7_IRQ}
#define EXTI7PB7        (s_exti_gpio_t){EXTI7, GPIOB, GPIO_PIN_7, EXTI7_IRQ}
#define EXTI7PC7        (s_exti_gpio_t){EXTI7, GPIOC, GPIO_PIN_7, EXTI7_IRQ}
#define EXTI7PD7        (s_exti_gpio_t){EXTI7, GPIOD, GPIO_PIN_7, EXTI7_IRQ}


//EXTI8
#define EXTI8PA8        (s_exti_gpio_t){EXTI8, GPIOA, GPIO_PIN_8, EXTI8_IRQ}
#define EXTI8PB8        (s_exti_gpio_t){EXTI8, GPIOB, GPIO_PIN_8, EXTI8_IRQ}
#define EXTI8PC8        (s_exti_gpio_t){EXTI8, GPIOC, GPIO_PIN_8, EXTI8_IRQ}
#define EXTI8PD8        (s_exti_gpio_t){EXTI8, GPIOD, GPIO_PIN_8, EXTI8_IRQ}


//EXTI9
#define EXTI9PA9        (s_exti_gpio_t){EXTI9, GPIOA, GPIO_PIN_9, EXTI9_IRQ}
#define EXTI9PB9        (s_exti_gpio_t){EXTI9, GPIOB, GPIO_PIN_9, EXTI9_IRQ}
#define EXTI9PC9        (s_exti_gpio_t){EXTI9, GPIOC, GPIO_PIN_9, EXTI9_IRQ}
#define EXTI9PD9        (s_exti_gpio_t){EXTI9, GPIOD, GPIO_PIN_9, EXTI9_IRQ}


//EXTI10
#define EXTI10PA10      (s_exti_gpio_t){EXTI10, GPIOA, GPIO_PIN_10, EXTI10_IRQ}
#define EXTI10PB10      (s_exti_gpio_t){EXTI10, GPIOB, GPIO_PIN_10, EXTI10_IRQ}
#define EXTI10PC10      (s_exti_gpio_t){EXTI10, GPIOC, GPIO_PIN_10, EXTI10_IRQ}
#define EXTI10PD10      (s_exti_gpio_t){EXTI10, GPIOD, GPIO_PIN_10, EXTI10_IRQ}


//EXTI11
#define EXTI11PA11      (s_exti_gpio_t){EXTI11, GPIOA, GPIO_PIN_11, EXTI11_IRQ}
#define EXTI11PB11      (s_exti_gpio_t){EXTI11, GPIOB, GPIO_PIN_11, EXTI11_IRQ}
#define EXTI11PC11      (s_exti_gpio_t){EXTI11, GPIOC, GPIO_PIN_11, EXTI11_IRQ}
#define EXTI11PD11      (s_exti_gpio_t){EXTI11, GPIOD, GPIO_PIN_11, EXTI11_IRQ}


//EXTI12
#define EXTI12PA12      (s_exti_gpio_t){EXTI12, GPIOA, GPIO_PIN_12, EXTI12_IRQ}
#define EXTI12PB12      (s_exti_gpio_t){EXTI12, GPIOB, GPIO_PIN_12, EXTI12_IRQ}
#define EXTI12PC12      (s_exti_gpio_t){EXTI12, GPIOC, GPIO_PIN_12, EXTI12_IRQ}
#define EXTI12PD12      (s_exti_gpio_t){EXTI12, GPIOD, GPIO_PIN_12, EXTI12_IRQ}


//EXTI13
#define EXTI13PA13      (s_exti_gpio_t){EXTI13, GPIOA, GPIO_PIN_13, EXTI13_IRQ}
#define EXTI13PB13      (s_exti_gpio_t){EXTI13, GPIOB, GPIO_PIN_13, EXTI13_IRQ}
#define EXTI13PC13      (s_exti_gpio_t){EXTI13, GPIOC, GPIO_PIN_13, EXTI13_IRQ}
#define EXTI13PD13      (s_exti_gpio_t){EXTI13, GPIOD, GPIO_PIN_13, EXTI13_IRQ}


//EXTI14
#define EXTI14PA14      (s_exti_gpio_t){EXTI14, GPIOA, GPIO_PIN_14, EXTI14_IRQ}
#define EXTI14PB14      (s_exti_gpio_t){EXTI14, GPIOB, GPIO_PIN_14, EXTI14_IRQ}
#define EXTI14PC14      (s_exti_gpio_t){EXTI14, GPIOC, GPIO_PIN_14, EXTI14_IRQ}
#define EXTI14PD14      (s_exti_gpio_t){EXTI14, GPIOD, GPIO_PIN_14, EXTI14_IRQ}


//EXTI15
#define EXTI15PA15      (s_exti_gpio_t){EXTI15, GPIOA, GPIO_PIN_15, EXTI15_IRQ}
#define EXTI15PB15      (s_exti_gpio_t){EXTI15, GPIOB, GPIO_PIN_15, EXTI15_IRQ}
#define EXTI15PC15      (s_exti_gpio_t){EXTI15, GPIOC, GPIO_PIN_15, EXTI15_IRQ}
#define EXTI15PD15      (s_exti_gpio_t){EXTI15, GPIOD, GPIO_PIN_15, EXTI15_IRQ}

/*=========================================
 * APIs Supported by MCAL EXTI driver:
 *==========================================*/
void MCAL_EXTI_GPIO_INIT(s_exti_pin_Config_t* INT_config);
void MCAL_EXIT_GPIO_DEINIT(void);
void MCAL_EXTI_GPIO_Update(s_exti_pin_Config_t * INT_Config);


#endif /* INC_STM32F103C6_INTERRUPT_H_ */
