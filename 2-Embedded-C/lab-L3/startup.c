/*
 ******************************************************************************
 * @file           : Startup.c
 * @author         : Ahmed Mostafa Mosleh
 * @brief          : Main program body
 ******************************************************************************
 */
 
#include "Platform_Types.h"
extern uint32_t main(void);
extern uint32_t stack_top;
extern uint32_t _E_text;
extern uint32_t _E_DATA;
extern uint32_t _S_DATA;
extern uint32_t _S_BSS;
extern uint32_t _E_BSS;

void Reset_Handler(void);
void Default_Handler(void);
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler"))) ;
void H_Fault_Handler(void) __attribute__((weak, alias("Default_Handler")));

uint32_t vectors[] __attribute__((section(".vectors"))) =  {
    (uint32_t) &stack_top,
    (uint32_t) &Reset_Handler,
    (uint32_t) &NMI_Handler,
    (uint32_t) &H_Fault_Handler,
};

void Reset_Handler(void) {
    uint32_t DATA_size = (uint8_t *) &_E_DATA - (uint8_t *) &_S_DATA;
    uint8_t* P_src = (uint8_t*) &_E_text; // i think it should be _E_text + 4byte to be at the start of .data section
    uint8_t* P_dis = (uint8_t*) &_S_DATA;

    for (uint32_t i = 0; i < DATA_size; i++)
    {
        *(uint8_t*)P_dis++ = *(uint8_t*)P_src++; 
    }

    uint32_t DATA_bss = (uint8_t *) &_E_BSS - (uint8_t *) &_S_BSS;
    P_dis = (uint8_t*) &_S_BSS;
    
    for (uint32_t i = 0; i < DATA_size; i++)
    {
        *(uint8_t*)P_dis++ = (uint8_t) 0; 
    }

    main();
}

void Default_Handler(void) { 
    Reset_Handler();
}