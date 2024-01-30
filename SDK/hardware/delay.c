#include "delay.h"
#include "intrins.h"
void delay_ms(unsigned int ms)
{
	unsigned char data i, j;
	while(ms--)
	{
	
	_nop_();
	_nop_();
	i = 33;
	j = 66;
	do
	{
		while (--j);
	} while (--i);


	}
}
