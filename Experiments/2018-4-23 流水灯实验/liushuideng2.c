#include "reg51.h"
#include "intrins.h"
#define uchar unsigned char
#define uint unsigned int
unsigned char code TABLE[]=
{ 
0x7E,0xBD,0xDB,0xE7,0x00         
}; 
unsigned char i; 
uint state;

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
  start:P2=0xff;
state=0;
P1=0xfe;
while(1)
{ if((P2&0x01)==0) 
state=1;
switch(state){
 case 1:
{ 
while(1)
{ 

if((P2&0x01)==0)
goto start; 
if(TABLE[i]!=0x00) 
{ 
P1=TABLE[i];     
i++;
delay(500);
}
else
{ 
i=0; 
}
}
}
case 0:
delay(500);
P1=_crol_(P1,1);
}
}
}
