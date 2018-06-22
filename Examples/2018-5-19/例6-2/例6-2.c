#include<reg51.h>
#define uchar unsigned char
void Delay(unsigned int i)
{
	uchar j;
	for(;i>0;i--)
		for(j=0;j<125;j++)
		{;}
}

void main()
{
	uchar display[9]={0xff,0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
	unsigned int a;
	for(;;)
	{
		EA=1;
		EX0=1;
		EX1=1;
		IT0=1;
		IT1=1;
		IP=0;
		for(a=0;a<9;a++)
		{
			Delay(500);
			P1=display[a];
		}
	}
}

void int0_isr(void) interrupt 0 using 1
{
	uchar n;
	for(n=0;n<10;n++)
	{
		P1=0x0f;
		Delay(500);
		P1=0xf0;
		Delay(500);
	}
}

void int1_isr(void) interrupt 2 using 2
{
	uchar m;
	for(m=0;m<10;m++)
	{
		P1=0xff;
		Delay(500);
		P1=0;
		Delay(500);
	}
}