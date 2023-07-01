#ifndef UART_H_
#define UART_H_
// Define uart Regiseters
#define UART0_DR *(volatile unsigned int * const) (0x101f1000)
void Uart_Send_String(unsigned char* P_tx_str);

#endif	
