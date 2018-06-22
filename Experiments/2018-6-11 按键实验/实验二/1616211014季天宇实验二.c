#include "reg51.h"
#define uchar unsigned char
#define uint unsigned int
sbit P2_4=P2^4;
uchar a=1;
uchar keyval;
uchar seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x01};
uchar end=0xc0;
uchar i;

void delay(uint x)  
{
  uchar t;
    while(x--) 
      for(t=0;t<120;t++);
	  }

void key_scan(void){
	P2=0xff;
	if (P2_4!=1){
		delay(50);
		keyval=1;
	}
	while (P2_4!=1){
        {
		P0=end;
		P2=0xf7;	 
       }  
	}
}

void L1(){
	P2=0xf7;
	end=seg[a++];
	if(a==10)
		a=0;
}

void main(void)
{
	P2=0xf7;
	keyval=0;
	P0=seg[0];
	while(1)
	{
	key_scan();
	if(keyval==1){
		L1();
		keyval=0;
	}     	
		P0=end;
		P2=0xf7;
		delay(2);	         
	}
}