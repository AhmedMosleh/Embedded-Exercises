#include "UART.h"

unsigned char str[100] = "ahmed mostafa mosleh";
const unsigned char str2[100] = "ahmed mostafa mosleh";
// static int x;
// static int y;
// int x;
int main() {
	Uart_Send_String(str);
	Uart_Send_String("\n");
}