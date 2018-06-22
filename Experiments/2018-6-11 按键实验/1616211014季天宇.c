#include <reg51.h>
#define uint unsigned int
#define uchar unsigned char
sbit P2_4=P2^4;
sbit P3_6=P3^6;

void main(void){
	P2=0xff;
	while (P2_4!=1){
	P3_6=0;
	}
	P3_6=1;	
}