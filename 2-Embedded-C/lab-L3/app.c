/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 */

#include "Platform_Types.h"
// add of RCC ox4002 1000
// add of GPIO Port A 0x4001 0800
#define RCC_BASE 	0x40021000
#define PORTA_BASE 	0x40010800

#define APB2ENR 	*(vuint32 *) (RCC_BASE+0x18)
#define GPIOA_ODR	*(vuint32 *) (PORTA_BASE+0x0C)
#define CRH 		*(vuint32 *) (PORTA_BASE+0x04)

typedef  union {
	vuint32 PORTA;

	struct {
		vuint32 reserved:13;
		vuint32 b13:1;
		vuint32 b14:1;
	} Pins;

} U_POARTA;

volatile 	U_POARTA* const PA = (volatile U_POARTA* ) (0x40010800+0x0C);
static 		vuint32 arr[100];
const 		vuint32 var = 1000;

int main() {
	APB2ENR |= (1<<2);
	CRH &= 0xff0fffff;
	CRH |= 0x00200000; // take care
	
	PA->Pins.b13 = 0;
	int i = 0;

	while(1) {
		GPIOA_ODR ^= (1 << 13);
		for(i = 0; i < 5000; i++);
	}
	return 0;
}
