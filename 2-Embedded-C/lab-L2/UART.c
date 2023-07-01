#include "UART.h"
void Uart_Send_String(unsigned char* P_tx_str) {
	while (*P_tx_str != '\0') {
		UART0_DR = (volatile int) (*P_tx_str);
		P_tx_str++;
	}
}
