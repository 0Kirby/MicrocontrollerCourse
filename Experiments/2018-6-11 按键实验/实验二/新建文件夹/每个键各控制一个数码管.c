#include "reg51.h"
#include "intrins.h"
#define uchar unsigned char
#define uint unsigned int
sbit S1=P2^4;
sbit S2=P2^5;
sbit S3=P2^6;
sbit S4=P2^7;
uchar a=1,o1;
uchar b=1,o2;
uchar c=1,o3;
uchar d=1,o4;
uchar keyval;
uchar seg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x01};
uchar end[4]={0xc0,0xc0,0xc0,0xc0};
uchar i,j,m;

void delay(uint x)  
{
  uchar t;
    while(x--) 
      for(t=0;t<120;t++);
	  }

void key_scan(void){
	P2=0xf0;
	if ((P2&0xf0)!=0xf0){
		delay(50);
		if(S1==0)
			keyval=1;
		if(S2==0)
			keyval=2;
		if(S3==0)
			keyval=3;
		if(S4==0)
			keyval=4;
	}
	while ((P2&0xf0)!=0xf0){
	 for(j=0;j<4;j++)
        {
        m=_crol_(m,1);
		P0=end[j];
		P2=m;	 
       }  
	}
}

void L1(){
	P2=0xf7;
	end[0]=seg[a++];
	if(a==10)
		a=0;
}
void L2(){
	P2=0xfb;
	end[1]=seg[b++];
	if(b==10)
		b=0;
}
void L3(){
	P2=0xfd;
	end[2]=seg[c++];
	if(c==10)
		c=0;
}
void L4(){
	P2=0xfe;
	end[3]=seg[d++];
	if(d==10)
		d=0;
}

void main(void)
{
	keyval=0;
	m=0xf7;
	P0=seg[0];
	while(1)
	{
	key_scan();
	switch(keyval){
	case 1:
		L1();
		keyval=0;
		break;
	case 2:
		L2();
		keyval=0;
		break;
	case 3:
		L3();
		keyval=0;
		break;
	case 4:
		L4();
		keyval=0;
		break;
	}     	
        for(j=0;j<4;j++)
        {
        m=_crol_(m,1);
		P0=end[j];
		P2=m;
		delay(2);	 
       }  
	}
}