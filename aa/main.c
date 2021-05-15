#include <stdlib.h>
#include "../usart/usart.h"
#include "../TIMER0/timer0.h"
//#include <util/delay.h>
#include <stdint.h>

int main()
{
	unsigned long n=100;
	int8_t str [64];
	int16_t number;
	timer0InteruptInit();
    usartInit(9600);

    while(1)
    {
    	usartPutString("Uneti broj: \r\n ");
    	while(!usartAvailable())
    		;
    	timer0DelayMs(n);


    	number = usartParseInt();

    	sprintf(str, "%d\0", number);
    	usartPutString("Uneli ste broj - ");
    	usartPutString(str);
		usartPutString("\r\n");

    }
	return 0;
}
