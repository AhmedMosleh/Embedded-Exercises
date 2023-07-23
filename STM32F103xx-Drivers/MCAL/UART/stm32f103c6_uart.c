
/*
 * stm32f103x8_USART_driver.h
 *
 *  Created on: Apr 28, 2021
 *      Author: Keroles Shenouda
 *      Mastering Embedded System Online Diploma
 *      www.learn-in-depth.com
 */

#include "stm32f103c6_uart.h"


s_usartConfig_t *g_usartConfig= (void *) 0;



/*============================================================================
 * @Fn				-MCAL_UART_Init
 * @brief 			- Initializes UART (Supported feature ASYNCH. Only)
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- s_usartConfig_t: All UART Configuration EXTI_PinConfig_t
 * @retval 			-none
 * @Note				-Support for Now Asynch mode & Clock 8 MHZ S
 *============================================================================*/
void MCAL_UART_Init(s_usart_t *USARTx, s_usartConfig_t *usartConfig)
{
	g_usartConfig = usartConfig;
	uint32_t pclk, BRR;
	//	EN() the Clock for given USART peripheral

	if (USARTx == USART1)
		RCC_USART1_CLK_EN();

	else if (USARTx == USART2)
		RCC_USART2_CLK_EN();

	else if (USARTx == USART3)
		RCC_USART3_CLK_EN();

	// EN() USART Module
	//	USART_CR1  Bit 13 UE: USART EN()
	USARTx->CR1 |= 1 << 13;

	// EN() USART Tx and Rx engines according to the USART_Mode configuration item
	//	USART_CR1 Bit 3 TE: Transmitter EN() & Bit 2 RE: Receiver EN()
	USARTx->CR1 |= usartConfig->USART_Mode;

	// PAYLOAD Width
	//  USARTx->CR1  Bit 12 M: Word length
	USARTx->CR1 |= usartConfig->Payload_Length;

	// Configuration of parity control bit fields
	//  USARTx->CR1 	Bit 10 PCE: Parity control EN()     Bit 9 PS: Parity selection
	USARTx->CR1 |= usartConfig->Parity;

	// configure the number of stop bits
	// USART_CR2  Bits 13:12 STOP: STOP bits
	USARTx->CR2 |= usartConfig->StopBits;

	// USART hardware flow control
	// USART_CR3  Bit 9 CTSE: CTS EN()   Bit 8 RTSE: RTS EN()
	USARTx->CR3 |= usartConfig->HwFlowCtl;

	// Configuration of BRR(Baudrate register)
	// PCLK1 for USART2, 3
	// PCLK2 for USART1
	if (USARTx == USART1)
	{
		pclk = MCAL_RCC_GetPCLK2Freq();
	}
	else
	{
		pclk = MCAL_RCC_GetPCLK1Freq();
	}

	BRR = UART_BRR_Register(pclk, usartConfig->BaudRate);

	USARTx->BRR = BRR;

	// EN() / DI() Interrupt
	// USART_CR1
	if (usartConfig->IRQ_Enable != UART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |= (usartConfig->IRQ_Enable);
		//		EN() NVIC For USARTx IRQ
		if (USARTx == USART1)
			NVIC_IRQ37_USART1_EN();

		else if (USARTx == USART2)
			NVIC_IRQ38_USART2_EN();

		else if (USARTx == USART3)
			NVIC_IRQ39_USART3_EN();
	}
}
/*============================================================================
 * @fn				-MCAL_UART_DEInit
 * @brief 			- DEInitializes UART (Supported feature ASYNCH. Only)
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			-none
 * Note				-Reset the Model By RCC
 *============================================================================*/

void MCAL_UART_DeInit(s_usart_t *USARTx)
{
	if (USARTx == USART1)
	{
		RCC_USART1_Reset();
		NVIC_IRQ37_USART1_DI();
	}

	else if (USARTx == USART2)
	{
		RCC_USART2_Reset();
		NVIC_IRQ38_USART2_DI();
	}

	else if (USARTx == USART3)
	{
		RCC_USART3_Reset();
		NVIC_IRQ39_USART3_DI();
	}
}

/*********************************************************************
 * @fn					-MCAL_UART_SendData
 *
 * @brief				-Send Buffer on UART
 *
 * @param [in			-USARTx: where x can be (1..3 depending on device used)
 * @param[in]         	-pTxBuffer Buffer
 * @param[in]         	-PollingEn   EN() pooling or dsable it
 * @note              - Should initialize UART First
 * 						When transmitting with the parity EN()d (PCE bit set to 1 in the USART_CR1 register),
 *						the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
 *						because it is replaced by the parity.
 *						When receiving with the parity EN()d, the value read in the MSB bit is the received parity
 *						bit
 *
 *============================================================================*/

void MCAL_UART_SendData(s_usart_t *USARTx, uint16_t *pTxBuffer, enum Polling_mechism PollingEn)
{
	uint16_t *pdata;

	// wait until TXE flag is set in the SR
	if (PollingEn == enable)
		while (!(USARTx->SR & 1 << 7));

	// Check the USART_WordLength item for 9BIT or 8BIT in a frame
	if (g_usartConfig->Payload_Length == UART_Payload_Length_9B)
	{
		/*if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits
		* When transmitting with the parity EN()d (PCE bit set to 1 in the USART_CR1 register),
		* the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
		* because it is replaced by the parity.
		* When receiving with the parity EN()d, the value read in the MSB bit is the received parity
		* bit.
		*/
		USARTx->DR = (*pTxBuffer & (uint16_t)0x01FF);
	}
	else
	{
		// This is 8bit data transfer
		USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
	}
}

void MCAL_UART_WAIT_TC(s_usart_t *USARTx)
{
	// wait till TC flag is set in the SR
	while (!(USARTx->SR & 1 << 6));
}

void MCAL_UART_ReceiveData(s_usart_t *USARTx, uint16_t *pRxBuffer, enum Polling_mechism PollingEn)
{
	// Loop over until "Len" number of bytes are transferred
	// wait until RXNE flag is set in the SR
	if (PollingEn == enable)
	{
		while (!(USARTx->SR & 1 << 5));
	}

	// Check the USART_WordLength item for 9BIT or 8BIT in a frame
	if (g_usartConfig->Payload_Length == UART_Payload_Length_9B)
	{
		if (g_usartConfig->Parity == UART_Parity__NONE)
		{
			// no parity So all 9bit are considered data
			*((uint16_t *)pRxBuffer) = USARTx->DR;
		}
		else
		{
			// Parity is used, so, 8bits will be of user data and 1 bit is parity
			*((uint16_t *)pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);
		}
	}
	else
	{
		// This is 8bit data
		if (g_usartConfig->Parity == UART_Parity__NONE)
		{
			// no parity So all 8bit are considered data
			*((uint16_t *)pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);
		}
		else
		{
			// Parity is used, so,7 bits will be of user data and 1 bit is parity
			*((uint16_t *)pRxBuffer) = (USARTx->DR & (uint8_t)0X7F);
		}
	}
}

/**================================================================================================================
 * @Fn				-MCAL_UART_GPIO_Set_Pins
 * @brief 			- intialize GPIO Pins
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			-none
 * Note				-Should EN() the corresponding ALT  & GPIO  in RCC clock Also called after MCAL_UART_Init()
 *==================================================================================================================*/
void MCAL_UART_GPIO_Set_Pins(s_usart_t *USARTx)
{
	s_pinConfig_t PinCfg;

	if (USARTx == USART1)
	{
		// PA9 TX
		// PA10 RX
		// PA11 CTS
		// PA12 RTS

		// PA9 TX
		PinCfg.pin_number = GPIO_PIN_9;
		PinCfg.pin_mode = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.pin_output_speed = GPIO_SPEED_10M;
		MCAL_GPIO_INIT(GPIOA, &PinCfg);

		// PA10 RX
		PinCfg.pin_number = GPIO_PIN_10;
		PinCfg.pin_mode = GPIO_MODE_INPUT_AF;
		MCAL_GPIO_INIT(GPIOA, &PinCfg);

		if (g_usartConfig->HwFlowCtl == UART_HwFlowCtl_CTS || g_usartConfig->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			// PA11 CTS
			PinCfg.pin_number = GPIO_PIN_11;
			PinCfg.pin_mode = GPIO_MODE_INPUT_FL;
			MCAL_GPIO_INIT(GPIOA, &PinCfg);
		}

		if (g_usartConfig->HwFlowCtl == UART_HwFlowCtl_RTS || g_usartConfig->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			// PA12 RTS
			PinCfg.pin_number = GPIO_PIN_12;
			PinCfg.pin_mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.pin_output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_INIT(GPIOA, &PinCfg);
		}
	}
	else if (USARTx == USART2)
	{
		// PA2 TX
		// PA3 RX
		// PA0 CTS
		// PA1 RTS

		// PA2 TX
		PinCfg.pin_number = GPIO_PIN_2;
		PinCfg.pin_mode = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.pin_output_speed = GPIO_SPEED_10M;
		MCAL_GPIO_INIT(GPIOA, &PinCfg);

		// PA3 RX
		PinCfg.pin_number = GPIO_PIN_3;
		PinCfg.pin_mode = GPIO_MODE_INPUT_AF;
		MCAL_GPIO_INIT(GPIOA, &PinCfg);

		if (g_usartConfig->HwFlowCtl == UART_HwFlowCtl_CTS || g_usartConfig->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			// PA0 CTS
			PinCfg.pin_number = GPIO_PIN_0;
			PinCfg.pin_mode = GPIO_MODE_INPUT_FL;
			MCAL_GPIO_INIT(GPIOA, &PinCfg);
		}

		if (g_usartConfig->HwFlowCtl == UART_HwFlowCtl_RTS || g_usartConfig->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			// PA1 RTS
			PinCfg.pin_number = GPIO_PIN_1;
			PinCfg.pin_mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.pin_output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_INIT(GPIOA, &PinCfg);
		}
	}
	else if (USARTx == USART3)
	{
		// PB10 TX
		// PB11 RX
		// PB13 CTS
		// PA14 RTS

		// PB10 TX
		PinCfg.pin_number = GPIO_PIN_10;
		PinCfg.pin_mode = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.pin_output_speed = GPIO_SPEED_10M;
		MCAL_GPIO_INIT(GPIOB, &PinCfg);

		// PB11 RX
		PinCfg.pin_number = GPIO_PIN_11;
		PinCfg.pin_mode = GPIO_MODE_INPUT_AF;
		MCAL_GPIO_INIT(GPIOB, &PinCfg);

		if (g_usartConfig->HwFlowCtl == UART_HwFlowCtl_CTS || g_usartConfig->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			// PB13 CTS
			PinCfg.pin_number = GPIO_PIN_13;
			PinCfg.pin_mode = GPIO_MODE_INPUT_FL;
			MCAL_GPIO_INIT(GPIOB, &PinCfg);
		}
		if (g_usartConfig->HwFlowCtl == UART_HwFlowCtl_RTS || g_usartConfig->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			// PA14 RTS
			PinCfg.pin_number = GPIO_PIN_14;
			PinCfg.pin_mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.pin_output_speed = GPIO_SPEED_10M;
			MCAL_GPIO_INIT(GPIOB, &PinCfg);
		}
	}
}

// ISR
void USART1_IRQHandler(void)
{

	g_usartConfig->P_IRQ_CallBack();
}

void USART2_IRQHandler(void)
{
	g_usartConfig->P_IRQ_CallBack();
}
void USART3_IRQHandler(void)
{
	g_usartConfig->P_IRQ_CallBack();
}
