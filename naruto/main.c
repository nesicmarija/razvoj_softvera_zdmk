#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include "../usart/usart.h"

int16_t Operation(int8_t operator, uint16_t op1, uint16_t op2)
{
	int16_t res = 0;

	switch (operator)
	{
		case '+':
			res = op1 + op2;
			break;
		case '-':
			res = op1 - op2;
			break;
		case '*':
			res = op1 * op2;
			break;
		case '/':
			res = op1 / op2;
			break;
		default:
			res = -1;
	}

	return res;
}

void ConvertToHex(int8_t *s, uint16_t num)
{
	uint16_t temp = num;
	uint8_t index = 0;

	while (temp > 0)
	{
		if (temp % 16 < 10)
			s[index] = temp % 16 + '0';
		else
			s[index] = (temp % 16 - 10) + 'A'; // (10, 15) - 10 = (0, 5) + 'A'
		temp = temp / 16;
		index++;
	}

	/* 1. nacin
	 * 	for (int8_t i = 0; i < index; i ++)
	 * 	{
	 * 		temp_str[i] = s[index - 1 - i];
	 * 	}
	 *
	 * 	for (int8_t i = 0; i < index; i++)
	 * 	{
	 * 		s[i] = temp_str[i];
	 * 	}
	 *
	 * */
	// 2.nacin pomocu dodatne pomocne promenljive
	// 3. nacin
	for (int8_t i = 0; i < index/2; i++)
	{
		s[i] ^= s[index - 1 - i]; // s[i] = s[i] ^ s[index - 1 - i];
		s[index - 1 - i] ^= s[i];
		s[i] ^= s[index - 1 - i];
	}

	s[index] = '\0';
}

int main()
{
	int8_t str[64];
	/*int16_t number1;
	int16_t number2;
	int8_t operator;*/
	uint16_t decimal_number;
	usartInit(9600);

	while(1)
	{
		usartPutString("Uneti broj: \r\n");
		while (!usartAvailable())
		;
		_delay_ms(100);

		/*number1 = usartParseInt();
		operator = usartGetChar();
		number2 = usartParseInt();

		sprintf(str, "%d %c %d = \0", number1, operator, number2);
		usartPutString("Uneli ste izraz = ");
		usartPutString(str);
		sprintf(str, "%d\0", Operation(operator, number1, number2));
		usartPutString(str);
		usartPutString("\r\n");*/

		decimal_number = usartParseInt();
		ConvertToHex(str, decimal_number);
		usartPutString("Konvertovan broj = 0x");
		usartPutString(str);
		usartPutString("\r\n");
	}
}
