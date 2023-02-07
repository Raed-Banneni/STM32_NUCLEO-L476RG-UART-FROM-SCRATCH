#include "stm32l476xx.h"
#include "uart.h"

#include <stdio.h>
#include <stdint.h>




char key;
int main(void)
{
	led_init();
	uart2_rxtx_init();
	/*if you want to use the receive mode */

	while(1)
	{
		ledon();
		key= uart2_read();
		if (key =='o')

			ledon();
		else
			ledoff();


	//if you want to use the transfer mode
	/*

	 while(1)
	{
	//the printf uses the __io_putchar function declared in uart.c  to send a whole string
		printf("hello from stm32 ............ \n\r");
		/*
	or for single character transfer  test use this :
		uart2_write('1');
		for (int i=0;i < 100000;i++){} // delay
	*/
	}
	return 0;
}





