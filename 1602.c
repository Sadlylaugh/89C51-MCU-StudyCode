#include "reg51.h"
#define uchar unsigned char
	
uchar code line1[]="dopodname";
uchar code line2[]="Sadlylaugh";

sbit dula=P2^6;
sbit wela=P2^7;
sbit RS=P1^0;
sbit RW=P1^1;
sbit E=P2^5;
//sbit BF=P0^7;
void delay(int ms)
{
	uchar i=110;
	for(ms;ms>0;ms--)
		for(i=110;i>0;i--);
}

//void wait();
void wcom(uchar com)
{
	RS=0;
	RW=0;
	P0=com;
	E=1;
	delay(5);
	E=0;
}

void wdata(uchar datas)
{
	RS=1;
	RW=0;
	P0=datas;
	E=1;
	delay(5);
	E=0;
}

void init()
{
	wcom(0x0c);
	wcom(0x06);
	wcom(0x0e);
	wcom(0x38);
	wcom(0x01);
}

//void wait()
//{
////	P0 = 0xFF;
//	
//	do
//	{
//		RS = 0;
//		RW = 1;
//		E = 0;
//		E = 1;
//	}while (BF == 1);
//	E = 0;

//}

void main()
{
	uchar i;
	init();
	wcom(0x80);
	for(i=0;i<9;i++)
	{
		wdata(line1[i]);
	}
	wcom(0x80+0x40);
	for(i=0;i<10;i++)
	{
		wdata(line2[i]);
	}
	while(1);
}