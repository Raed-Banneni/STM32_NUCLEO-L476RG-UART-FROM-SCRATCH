#include "uart.h"
#define GPIOAEN		(1U<<0)
#define UART2EN		(1U<<17)

#define CR1_RE		(1U<<2)
#define CR1_TE		(1U<<3)
#define CR1_UE		(1U<<0)

#define ISR_TXE		(1U<<7) // tx empty bit of interrupt and status register
#define ISR_RXNE	(1U<<5) // Rx not empty bit of interrupt and status register


#define SYS_FREQ	80000000
#define APB1_CLK	SYS_FREQ
#define UART_BAUDRATE 	115200


#define PIN5		(1U<<5)
#define LED_PIN		PIN5


static void uart_set_baudrate(USART_TypeDef *USARTx , uint32_t periph_clk,uint32_t bauderate);
static uint16_t compute_uart_bd(uint32_t periph_clk , uint32_t baudrate);

void uart2_write(int ch);
char uart2_read(void);

int __io_putchar(int ch)
{
	uart2_write(ch);
	return (ch);
}
void ledon(void)
{

		GPIOA->ODR |=LED_PIN;
}
void ledoff(void)
{

		GPIOA->ODR &=~LED_PIN;
}

void led_init(void)
{
			RCC->AHB2ENR |=GPIOAEN;
			GPIOA->MODER |=(1U<<10);
			GPIOA->MODER &=~(1U<<11);
}
void uart2_rxtx_init(void)
{
	/*********************configure uart gpio pin*********************/

	/*enable clock access to gpioa*/
	RCC->AHB2ENR |=GPIOAEN;

	/*set PA2 to alternate function*/
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |=(1U<<5);

	/*Set PA2 alternate function type to UART_TX (AF7)*/
	GPIOA->AFR[0] |=(1U<<8);
	GPIOA->AFR[0] |=(1U<<9);
	GPIOA->AFR[0] |=(1U<<10);
	GPIOA->AFR[0] &=~(1U<<11);


	/*set PA3 to alternate function*/
	GPIOA->MODER &=~(1U<<6);
	GPIOA->MODER |=(1U<<7);

	/*Set PA3 alternate function type to UART_RX (AF7)*/
		GPIOA->AFR[0] |=(1U<<12);
		GPIOA->AFR[0] |=(1U<<13);
		GPIOA->AFR[0] |=(1U<<14);
		GPIOA->AFR[0] &=~(1U<<15);


	/***********************Configure uart module **********************/

	/*Enable clock access to uart2 */
	RCC->APB1ENR1 |=UART2EN;

	/*configure baud rate*/

	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);

	/*configure the transfer direction*/
	USART2->CR1 = (CR1_TE | CR1_RE);

	/*enable uart module*/
	USART2->CR1 |=CR1_UE;
}

static void uart_set_baudrate(USART_TypeDef *USARTx , uint32_t periph_clk,uint32_t bauderate)
{
	USARTx->BRR =compute_uart_bd(periph_clk,bauderate);
}
static uint16_t compute_uart_bd(uint32_t periph_clk , uint32_t baudrate)
{
	return ((periph_clk + (baudrate/2U))/baudrate);
}
void uart2_write(int ch)
{
	// make sure transmit data register is empty
	while (!(USART2->ISR & ISR_TXE)){}
	//write to transmit data register
	USART2->TDR = (ch & 0xFF);
}
char uart2_read(void)
{
	// make sure receive data register is empty
		while (!(USART2->ISR & ISR_RXNE)){}
		//write to transmit data register
		return(USART2->RDR);
}




