#include "reg51.h"
#include "intrins.h"
#define uchar unsigned char
#define uint unsigned int

uchar seg[]= {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
uchar time[]= {0xf9,0xa4,0xbf,0xb0,0x99,0xbf,0x92,0x82};
uchar alarm[]= {0xc0,0xc0,0xbf,0xc0,0xc0,0xbf,0xc0,0xc0};

uint i,value,count;
uint hour=23,minute=59,second=21;
uint ahour=0,aminute=0,asecond=0;
uchar m=0x7f;

sbit P2_0=P2^0;
sbit P2_1=P2^1;
sbit P2_2=P2^2;
sbit P2_3=P2^3;
sbit P2_4=P2^4;
sbit P2_5=P2^5;
sbit P2_6=P2^6;
sbit P2_7=P2^7;
sbit P3_0=P3^0;
sbit P3_2=P3^2;
sbit P3_3=P3^3;

void plus();
void minus();

void delay(uint x) {
	uchar t;
	while(x--)
		for(t=0; t<120; t++);
}

void convert() {
	time[0]=seg[hour/10];
	time[1]=seg[hour%10];
	time[3]=seg[minute/10];
	time[4]=seg[minute%10];
	time[6]=seg[second/10];
	time[7]=seg[second%10];
	alarm[0]=seg[ahour/10];
	alarm[1]=seg[ahour%10];
	alarm[3]=seg[aminute/10];
	alarm[4]=seg[aminute%10];
	alarm[6]=seg[asecond/10];
	alarm[7]=seg[asecond%10];
}

void alarmcheck() {
	if(hour==ahour&minute==aminute&second==asecond)
		P3_0=1;
}

void plus() {
	if (P2_1!=1)
		++value;
	while (P2_1!=1);
}

void minus() {
	if (P2_2!=1)
		--value;
	while (P2_2!=1);
}
void flash() {
	for(i=0; i<8; i++) {
		P1=m;
		P0=time[i];
		m=_crol_(m,1);
		delay(5);
	}
}

void aflash() {
	for(i=0; i<8; i++) {
		P1=m;
		P0=alarm[i];
		m=_crol_(m,1);
		delay(5);
	}
}

void elipse() {
	count++;
	if (count==26) {
		count=0;
		second++;
	}
	if (second>59) {
		second=0;
		minute++;
	}
	if (minute>59) {
		minute=0;
		hour++;
	}
	if (hour>23) hour=0;
}
void function() interrupt 0 {
	EA=0;
	EX0=0;
	P2_4=1;
	delay(500);
	i=0;
	m=0x01;
	while(P3_2!=0) {
		convert();
		flash();
		value=second;
		plus();
		if(value>59)
			value=0;
		minus();
		if(value<0)
			value=59;
		second=value;
	}
	delay(500);
	P2_4=0;
	P2_5=1;
	while(P3_2!=0) {
		convert();
		flash();
		value=minute;
		plus();
		if(value>59)
			value=0;
		minus();
		if(value<0)
			value=59;
		minute=value;
	}
	delay(500);
	P2_5=0;
	P2_6=1;
	while(P3_2!=0) {
		convert();
		flash();
		value=hour;
		plus();
		if(value>23)
			value=0;
		minus();
		if(value<0)
			value=23;
		hour=value;
	}
	P2_6=0;
	EX0=1;
}

void alarmset() interrupt 2 {
	P3_0=0;
	EA=0;
	EX1=0;
	P2_4=1;
	P2_7=1;
	delay(500);
	i=0;
	m=0x01;
	while(P3_3!=0) {
		convert();
		aflash();
		value=asecond;
		plus();
		if(value>59)
			value=0;
		minus();
		if(value<0)
			value=59;
		asecond=value;
	}
	delay(500);
	P2_4=0;
	P2_5=1;
	while(P3_3!=0) {
		convert();
		aflash();
		value=aminute;
		plus();
		if(value>59)
			value=0;
		minus();
		if(value<0)
			value=59;
		aminute=value;
	}
	delay(500);
	P2_5=0;
	P2_6=1;
	while(P3_3!=0) {
		convert();
		aflash();
		value=ahour;
		plus();
		if(value>23)
			value=0;
		minus();
		if(value<0)
			value=23;
		ahour=value;
	}
	P2_6=0;
	P2_7=0;
	EX1=1;
}


void main() {
	EA=1;
	EX0=1;
	EX1=1;
	IT0=1;
	IT1=1;
	IP=0;
	P3_0=0;
	P2=0x0f;
	m=0x01;
	TMOD=0x01;
	TH0=(65536-54015)/256;
	TL0=(65536-54015)%256;
	ET0=0;
	TR0=1;
	while(1) {
		EA=1;
		convert();
		elipse();
		flash();
		alarmcheck();
	}
}

