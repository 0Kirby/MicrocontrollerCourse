#include <AT89X51.H>
#include <intrins.H>
#define uchar unsigned char
#define uint unsigned int
uchar code DSY_CODE[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff};
uchar Num[]={10,10,10,1,2,3,4};
void delay(uint x)
{
uchar t;
while (x--)
for(t=0;t<120;t++);
}
void main(void)
{
uchar i,j,k=0,m=0xfe;
while(1)
{
for(i=0;i<20;i++)
{
for(j=0;j<4;j++)
{
P0=0xFF;P0=DSY_CODE[Num[(k+j)%7]];
P2=m;delay(5);
m=_crol_(m,1);
}
}
k=(k+1)%7;
}
}