/*
 * stm32f103c6.h
 *
 *  Created on: Jul 9, 2023
 *      Author: ahmed
 */

#ifndef INC_STM32F103C6_H_
#define INC_STM32F103C6_H_

/*=========================================
 * Includes
==========================================*/
#include <stdint.h>

/*=========================================
 * Base addresses for Memories
==========================================*/

#define FLAS_MEM_BASE 	0x08000000UL 	// flash memory base address
#define SYS_MEM_BASE	0x1FFFF000UL  	// system memory base address
#define SRAM_BASE 		0x20000000UL    // sram base address
#define PERI_BASE 		0x40000000UL    // peripherals  base address
#define CPU_PERI_BASE 	0xE0000000UL 	// cortex m3 internal periphrals base address
#define NVIC_BASE		0xE000E100UL	// nvic base
/*=========================================
 * Base addresses Core peripherals
==========================================*/
#define NVIC_ISER0			*(volatile uint32_t *)(NVIC_BASE + 0x00)
#define NVIC_ISER1			*(volatile uint32_t *)(NVIC_BASE + 0x04)
#define NVIC_ISER2			*(volatile uint32_t *)(NVIC_BASE + 0x08)
#define NVIC_ICER0			*(volatile uint32_t *)(NVIC_BASE + 0x80)
#define NVIC_ICER1			*(volatile uint32_t *)(NVIC_BASE + 0x84)
#define NVIC_ICER2			*(volatile uint32_t *)(NVIC_BASE + 0x88)

/*=========================================
 * Base addresses AHB peripherals
==========================================*/

#define RCC_BASE 0x40021000UL // Reset and clock control RCC

/*=========================================
 * Base addresses APB1 peripherals
==========================================*/
#define USART2_BASE 0x40004800UL
#define USART3_BASE 0x40004400UL


/*=========================================
 * Base addresses APB2 peripherals
==========================================*/
// GPIO base addresses
#define GPIOA_BASE 0x40010800UL
#define GPIOB_BASE 0x40010C00UL
#define GPIOC_BASE 0x40011000UL
#define GPIOD_BASE 0x40011400UL
#define GPIOE_BASE 0x40011800UL
#define GPIOF_BASE 0x40011C00UL
#define GPIOG_BASE 0x40012000UL

// EXTI base addresses
#define EXTI_BASE 0x40010400UL

// AFIO BASE ADDRESSES
#define AFIO_BASE 0x40010000UL

// USART1
#define USART1_BASE	0x40013800UL




/*=========================================
 * Peripheral register
==========================================*/

//================= RCC =================
typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
}s_rcc_t;

//================= GPIO =================

typedef struct
{
	volatile uint32_t CRL; // Port configuration register low
	volatile uint32_t CRH; // Port configuration register high
	volatile uint32_t IDR; //
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
} s_gpio_t;

//================= AFIO =================

typedef struct
{
	volatile uint32_t EVCR;    // Port configuration register low
	volatile uint32_t MAPR;    // Port configuration register high
	volatile uint32_t EXTICR[4]; //
	volatile uint32_t RES0;  // RESERVED 4 BYTES
	volatile uint32_t MAPR2; // Port configuration register high
} s_afio_t;

//================= EXTI =================
typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
} s_exti_t;

//================= USART =================
typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;

}s_usart_t;




/*=========================================
 * Peripheral Instants:
==========================================*/

//================= GPIO =================

#define GPIOA	(s_gpio_t *)GPIOA_BASE
#define GPIOB	(s_gpio_t *)GPIOB_BASE
#define GPIOC	(s_gpio_t *)GPIOC_BASE
#define GPIOD	(s_gpio_t *)GPIOD_BASE
#define GPIOE	(s_gpio_t *)GPIOE_BASE
#define GPIOF	(s_gpio_t *)GPIOF_BASE
#define GPIOG	(s_gpio_t *)GPIOG_BASE

//================= RCC =================
#define RCC		((s_rcc_t*)RCC_BASE)

//================= EXTI =================
#define EXTI	((s_exti_t *)EXTI_BASE)

//================= AFIO =================
#define AFIO	((s_afio_t*)AFIO_BASE)

//================= USART =================
#define USART1	((s_usart_t*)USART1_BASE)
#define USART2	((s_usart_t*)USART2_BASE)
#define USART3	((s_usart_t*)USART3_BASE)

/*=========================================
 * Enable CLK Macros:
==========================================*/

#define RCC_GPIOA_CLK_EN()	(RCC->APB2ENR |= 1 << 2)  //IOPA enable is in bit 2
#define RCC_GPIOB_CLK_EN()	(RCC->APB2ENR |= 1 << 3)  //IOPB enable is in bit 3
#define RCC_GPIOC_CLK_EN()	(RCC->APB2ENR |= 1 << 4)  //IOPC enable is in bit 4
#define RCC_GPIOD_CLK_EN()	(RCC->APB2ENR |= 1 << 5)  //IOPD enable is in bit 5
#define RCC_GPIOE_CLK_EN()	(RCC->APB2ENR |= 1 << 6)  //IOPE enable is in bit 6

#define RCC_AFIO_CLK_EN()	(RCC->APB2ENR |= 1 << 0)  //AFIO enable is in bit 0

#define RCC_USART1_CLK_EN()	( RCC->APB2ENR |= (1<<14) )
#define RCC_USART2_CLK_EN()	( RCC->APB1ENR |= (1<<17) )
#define RCC_USART3_CLK_EN()	( RCC->APB1ENR |= (1<<18) )

//RCC_Reset
#define RCC_USART1_Reset()	( RCC->APB2RSTR |= (1<<14) )
#define RCC_USART2_Reset()	( RCC->APB1RSTR |= (1<<17) )
#define RCC_USART3_Reset()	( RCC->APB1RSTR |= (1<<18) )

/*=========================================
 * IVT:
==========================================*/
// EXTI
#define EXTI0_IRQ	6
#define EXTI1_IRQ	7
#define EXTI2_IRQ	8
#define EXTI3_IRQ	9
#define EXTI4_IRQ	10
#define EXTI5_IRQ	23
#define EXTI6_IRQ	23
#define EXTI7_IRQ	23
#define EXTI8_IRQ	23
#define EXTI9_IRQ	23
#define EXTI10_IRQ	40
#define EXTI11_IRQ	40
#define EXTI12_IRQ	40
#define EXTI13_IRQ	40
#define EXTI14_IRQ	40
#define EXTI15_IRQ	40

#define USART1_IRQ	37
#define USART2_IRQ	38
#define USART3_IRQ	39


/*=========================================
 * Mask NVIC :
==========================================*/

/*
 * 		Set-enable  | Clear-enable 	  Set-pending 		Clear-pending 	Active Bit
0-31 	ISER[0] 	| ICER[0] 			ISPR[0] 		ICPR[0] 		IABR[0]
32-63 	ISER[1] 	| ICER[1] 			ISPR[1] 		ICPR[1] 		IABR[1]
64-67 	ISER[2] 	| ICER[2] 			ISPR[2] 		ICPR[2] 		IABR[2]
 */
#define NVIC_IRQ6_EXTI0_EN()			(NVIC_ISER0 |= 1<<6)				// EXTI0 ---> PIN6 in NVIC
#define NVIC_IRQ7_EXTI1_EN()			(NVIC_ISER0 |= 1<<7)				// EXTI1 ---> PIN7 in NVIC
#define NVIC_IRQ8_EXTI2_EN()			(NVIC_ISER0 |= 1<<8)				// EXTI2 ---> PIN8 in NVIC
#define NVIC_IRQ9_EXTI3_EN()			(NVIC_ISER0 |= 1<<9)				// EXTI3 ---> PIN9 in NVIC
#define NVIC_IRQ10_EXTI4_EN()			(NVIC_ISER0 |= 1<<10)				// EXTI4 ---> PIN10 in NVIC
#define NVIC_IRQ23_EXTI5_9_EN()			(NVIC_ISER0 |= 1<<23)
#define NVIC_IRQ40_EXTI10_15_EN()		(NVIC_ISER1 |= 1<<8)
#define NVIC_IRQ37_USART1_EN()			(NVIC_ISER1 |= 1<<(USART1_IRQ - 32))
#define NVIC_IRQ38_USART2_EN()			(NVIC_ISER1 |= 1<<(USART2_IRQ - 32))
#define NVIC_IRQ39_USART3_EN()			(NVIC_ISER1 |= 1<<(USART3_IRQ - 32))



#define NVIC_IRQ6_EXTI0_DI()			(NVIC_ICER0 |= 1<<6)				// EXTI0 ---> PIN6 in NVIC
#define NVIC_IRQ7_EXTI1_DI()			(NVIC_ICER0 |= 1<<7)				// EXTI1 ---> PIN7 in NVIC
#define NVIC_IRQ8_EXTI2_DI()			(NVIC_ICER0 |= 1<<8)				// EXTI2 ---> PIN8 in NVIC
#define NVIC_IRQ9_EXTI3_DI()			(NVIC_ICER0 |= 1<<9)				// EXTI3 ---> PIN9 in NVIC
#define NVIC_IRQ10_EXTI4_DI()			(NVIC_ICER0 |= 1<<10)				// EXTI4 ---> PIN10 in NVIC
#define NVIC_IRQ23_EXTI5_9_DI()			(NVIC_ICER0 |= 1<<23)				// EXTI5, EXTI6, EXTI7, EXTI8, EXTI9 ---> PIN23 in NVIC
#define NVIC_IRQ40_EXTI10_15_DI()		(NVIC_ICER1 |= 1<<8)				// 40 - 32 = 8
#define NVIC_IRQ37_USART1_DI()			(NVIC_ICER1 |= 1<<(USART1_IRQ - 32))
#define NVIC_IRQ38_USART2_DI()			(NVIC_ICER1 |= 1<<(USART2_IRQ - 32))
#define NVIC_IRQ39_USART3_DI()			(NVIC_ICER1 |= 1<<(USART3_IRQ - 32))

#endif /* INC_STM32F103C6_H_ */
