#include <stdlib.h>
#include "../usart/usart.h"
#include "../TIMER0/timer0.h"
//#include <util/delay.h>
#include <stdint.h>

int main()
{
	unsigned long n=100;
	int8_t recenica [60];
	uint16_t duzina;
	int8_t novi_red[]= "\r\n";
	timer0InteruptInit();
    usartInit(9600);

    while(1)
    {
    	while(!usartAvailable())
    		;
    	timer0DelayMs(n);

        duzina = usartGetString(recenica);
        recenica[duzina] = '\0';

    	int8_t i;
    	int8_t nova_recenica[60];

    	for(i=0; i<duzina; i++)
    	{
    		if((recenica[i] > 96) && (recenica[i] <123))
    		{
    			nova_recenica[i] = recenica [i] - 32;
    	    }
    		else
    		{
    			nova_recenica[i]= recenica[i];
    		}
    	}

    nova_recenica[duzina] = 0;
    usartPutString(nova_recenica);
    usartPutString(novi_red);

    }
	return 0;
}
