#include "reg51.h"
#include "intrins.h"
#define uchar unsigned char
#define uint unsigned int
void delay(uint i)
{
	uchar t;
	while (i--)
	{
	for(t=0;t<120;t++);
	}
}
void main()
{
	P1=0xff;
	delay(500);
	P1=0xfe;
	delay(500);
}