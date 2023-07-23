/*
 * stm32f103c6_rcc.h
 *
 *  Created on: Jul 23, 2023
 *      Author: ahmed
 */

#ifndef INC_STM32F103C6_RCC_H_
#define INC_STM32F103C6_RCC_H_

#include "stm32f103c6.h"

#define HSE_CLK		(uint32_t)16000000
#define HSI_RC_CLK	(uint32_t)8000000

uint32_t MCAL_RCC_GetSYS_CLCKFreq(void);
uint32_t MCAL_RCC_GetHCLKFreq(void);
uint32_t MCAL_RCC_GetPCLK1Freq(void);
uint32_t MCAL_RCC_GetPCLK2Freq(void);

#endif /* INC_STM32F103C6_RCC_H_ */
