#include<reg52.h>
#include<intrins.h>
typedef unsigned char uchar;
typedef unsigned int  uint;
uchar code table[] = {0xf9,0xa4,0xb0,0x99};//1234
void delay(uchar t)
{
	uchar i;
	while(t--)
	{
		for(i = 0;i<100;i++);
	}
} 

void main()
{
	uint a;
	uchar j=0xf7;
	while(1)
	{	
	
		for(a = 0;a<4;a++)
			{
			j=_crol_(j,1);
			//P2=0x07;		
			P0 = table[a];
			P2=j;
			delay(1);

			}
	}
}
