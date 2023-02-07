#include "stm32l476xx.h"
#include "uart.h"

#include <stdio.h>
#include <stdint.h>




char key;
int main(void)
{
	uart2_rxtx_init();
	while(1)
	{
		ledon();
		key= uart2_read();
		if (key =='o')

			ledon();
		else
			ledoff();

	}
	return 0;
}





