#include <stdlib.h>
#include "../usart/usart.h"
#include <util/delay.h>
#include <stdint.h>

int main()
{
	int8_t str [64];
	int16_t number;
    usartInit(9600);

    while(1)
    {
    	usartPutString("Uneti broj: \r\n ");
    	while(!usartAvailable())
    		;
    	_delay_ms(100);

    	number = usartParseInt();

    	sprintf(str, "%d\0", number);
    	usartPutString("Uneli ste broj - ");
    	usartPutString(str);
		usartPutString("\r\n");

    }
	return 0;
}
