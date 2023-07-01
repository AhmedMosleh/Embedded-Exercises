/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Ahmed Mostafa Mosleh 
 * @brief          : Main program body
 ******************************************************************************
 */

#include "Platform_Types.h"
// add of RCC ox4002 1000
// add of GPIO Port A 0x4001 0800

#define SYSCTL_RCGC2_R 	    (*(vuint32_t *) (0x400FE000))
#define GPIO_PORTF_DIR_R    (*(vuint32_t *) (0x40025000+0x3fc))
#define GPIO_PORTF_DEN_R    (*(vuint32_t *) (0x40025000+0x400))
#define GPIO_PORTF_DATA_R   (*(vuint32_t *) (0x40025000+0x51c))

int main() {
    SYSCTL_RCGC2_R = 0x20;
    vuint32_t i;
    for(i = 0; i < 200; i++);        

    GPIO_PORTF_DIR_R |= 1 << 3;
    GPIO_PORTF_DEN_R |= 1 << 3;

	while(1) {
        GPIO_PORTF_DATA_R ^= 1 << 3;
        for(i = 0; i < 5000; i++);        
	}
	return 0;
}
