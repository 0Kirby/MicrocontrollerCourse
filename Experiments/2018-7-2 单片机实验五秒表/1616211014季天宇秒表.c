#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit P2_4=P2^4;
uchar seg[]= {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
uchar time[]= {0xc0,0xc0,0xc0,0xc0};
uchar timer=0;
uchar second;
uchar minute;
uchar key;
uchar a;
uchar j=0xf7;

void delay(uint x)  
{
  uchar t;
    while(x--) 
      for(t=0;t<200;t++);
}												

void display(){
	for(a =0;a<4;a++)
			{
			j=_crol_(j,1);
			P2=j;		
			P0 = time[a];
			delay(1);
			}
}

void convert(){
	time[0]=seg[minute/10];
	time[1]=seg[minute%10];
	time[2]=seg[second/10];
	time[3]=seg[second%10];
}

void main(){
TMOD=0x01;
ET0=1;
EA=1;
second=50;
minute=59;
P2=0xf0;
P0=seg[0];
while(1)
{
   if (P2_4!=1){
   	
   		while (P2_4!=1);
		delay(20);
		key++;
		switch(key){
		case 1:
			TH0=0xee;
			TL0=0x00;
			TR0=1;
			break;
		case 2:
			TR0=0;
			convert();
			a=0;
			j=0xf7;
	
			while(P2_4==1){
			display();
			}
			break;
		case 3:
			key=0;
			second=0;
			minute=0;
			P2=0xf0;
			P0=seg[second];
			break;
		}
			
	}
}
}

void int_T0() interrupt 1{
	there:TR0=0;
	TH0=0xee;
	TL0=0x00;
	timer++;
	display();
	if(timer==80)
	{
		timer=0;
		second++;
		if(second>59)
	{
		second=0;
		minute++;
	}
		
	}
	
	if(minute==60)
	{
		TR0=0;
		second=0;
		minute=0;
		key=2;
		goto there;
	}

	else
	{
		TR0=1;
	}
	convert();
		//display();
}	 
