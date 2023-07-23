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
 * Comman Macros
==========================================*/

#define	GET_BIT(reg,n)				(((reg)>>(n))&1)
#define SET_BIT(reg,n)				(reg|=(1<<n))
#define CLR_BIT(reg,n)				(reg&=~(1<<n))
#define TOGGLE_BIT(reg,n)			(reg^=(1<<n))

#define	GET_REG(reg)				(reg)
#define SET_REG(reg)				((reg)=0XFF)
#define CLR_REG(reg)				((reg)=0X00)
#define TOGGLE_REG(reg)				((reg)^=0xFF) //((reg)~=(reg))
#define ASSIGN_REG(reg,value)		((reg)=(value))

#define	GET_LOW_NIB(reg)			((reg)&0X0F)
#define SET_LOW_NIB(reg)			((reg)|=0X0F)
#define CLR_LOW_BIT(reg)			((reg)&=0XF0)
#define TOGGLE_LOW_NIB(reg)			((reg)^=0X0F)
#define ASSIGN_LOW_NIB(reg,value)	((reg)=(((reg)&0XF0)|((value)&0x0F))) //??

#define	GET_HIGH_NIB(reg)			(((reg)&0XF0)>>4)
#define SET_HIGH_NIB(reg)			((reg)|=0XF0)
#define CLR_HIGH_BIT(reg)			((reg)&=0X0F)
#define TOGGLE_HIGH_NIB(reg)		((reg)^=0XF0)
#define ASSIGN_HIGH_NIB(reg)		((reg)=((value<<4)|(reg&0X0F)))

/*=========================================
 * Base addresses for Memories
==========================================*/

#define FLAS_MEM_BASE 	0x08000000UL 	// flash memory base address
#define SYS_MEM_BASE	0x1FFFF000UL  	// system memory base address
#define SRAM_BASE 		0x20000000UL    // sram base address
#define PERI_BASE 		0x40000000UL    // peripherals  base address
#define CPU_PERI_BASE 	0xE0000000UL 	// cortex m3 internal periphrals base address

/*=========================================
 * Base addresses AHB peripherals
==========================================*/

#define RCC_BASE 0x40021000UL // Reset and clock control RCC

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
	volatile uint32_t EXTICR1; //
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t RES0;  // RESERVED 4 BYTES
	volatile uint32_t MAPR2; // Port configuration register high
} s_afio_t;

//================= EXTI =================
typedef struct
{
	volatile uint32_t IMR;  // Port configuration register low
	volatile uint32_t EMR;  // Port configuration register high
	volatile uint32_t RTSR; //
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
} s_exti_t;



/*=========================================
 * Peripheral Instants:
==========================================*/
#define GPIOA	(s_gpio_t *)GPIOA_BASE
#define GPIOB	(s_gpio_t *)GPIOB_BASE
#define GPIOC	(s_gpio_t *)GPIOC_BASE
#define GPIOD	(s_gpio_t *)GPIOD_BASE
#define GPIOE	(s_gpio_t *)GPIOE_BASE
#define GPIOF	(s_gpio_t *)GPIOF_BASE
#define GPIOG	(s_gpio_t *)GPIOG_BASE

#define RCC		((s_rcc_t*)RCC_BASE)

#define EXTI	((s_exti_t *)EXTI_BASE)

#define AFIO	((s_afio_t*)AFIO_BASE)




/*=========================================
 * RCC Macros:
==========================================*/

#define RCC_GPIOA_CLK_EN()	(SET_BIT(RCC->APB2ENR,2))
#define RCC_GPIOB_CLK_EN()	(SET_BIT(RCC->APB2ENR,3))
#define RCC_GPIOC_CLK_EN()	(SET_BIT(RCC->APB2ENR,4))
#define RCC_GPIOD_CLK_EN()	(SET_BIT(RCC->APB2ENR,5))
#define RCC_GPIOE_CLK_EN()	(SET_BIT(RCC->APB2ENR,6))

#define AFIO_CLK_EN()		(SET_BIT(RCC->APB2ENR,0))


#endif /* INC_STM32F103C6_H_ */
