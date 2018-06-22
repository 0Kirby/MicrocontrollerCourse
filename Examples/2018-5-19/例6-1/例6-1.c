#include<reg51.h>
#define uchar  unsigned char
void Delay(unsigned int i)
{
	unsigned int j;
	for(;i>0;i--)
	for(j=0;j<333;j++)
	{;}
	}
	void main()
	{
	EA=1;
	EX0=1;
	IT0=1;
	while(1)
	{P1=0;}
}

void int0()  interrupt 0  using 1
	{
		uchar  m;
		EX0=0;
	for(m=0;m<5;m++)
	{
	P1=0x0f;
	Delay(400);
	P1=0xf0;
	Delay(400);
	EX0=1;
	}
	}