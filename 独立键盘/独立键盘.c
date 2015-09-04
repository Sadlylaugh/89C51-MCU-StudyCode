//#include<reg51.h>
//sbit LED=P1^0;
//sbit p=P3^4;
//char i;
//void delay(int time);
//void main()
//{
//	LED=1;
//	while(1)
//	{
//		if(p==0)
//		{
//			delay(10);
//			if(p==0)
//			{
//				LED=0;
//			}
//		}
//		else
//			LED=1;
//	}
//}
//void delay(int time)
//{
//	for(time;time>0;time--)
//		for(i=110;i>0;i--);
//}

#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
sbit key1=P3^4;
sbit key2=P3^5;
sbit key3=P3^6;
sbit key4=P3^7;
sbit dp=P0^7;
uchar r;
sbit dula=P2^6;//dula 段选
sbit wela=P2^7;//wela	位选
uchar ms=0;//十毫秒位，一共两位
uint second=0;//秒位，一共四位
uchar code number[]={  //各数字的段选数据，从左到右为0到9
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
char numbers[]={		//将秒和十毫秒数组化
	//从左到右为十万位到个位
	0,0,0,0,0,0};
uchar code digits[]={ 
  //各位的位选开启数据，从左到右为个位到十万位
0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
void pickup()
{
	uchar i;
	uint p;
	numbers[5]=ms%10;//最低位设为十毫秒位数字
	numbers[4]=ms/10;//倒数第二位设为百毫秒位数字
	p=second;
	for(i=4;i>0;i--)//从最低位开始取秒各位上的数字
	{
		numbers[i-1]=p%10;
		p=p/10;
	}
}
void delay(uint i)
{
	uint j=110;
	for(i;i>0;i--)
		for(j;j>0;j--);
}
	
void show()
{
	uchar i=0;
	for(i=6;i>0;i--)
	{
		dula=1;
		P0=number[numbers[i-1]];//从个位开始送段选数据
		if(i==4)
		{
			dp=1;
		}
		dula=0;
		P0=0xff;
		wela=1;
		P0=digits[6-i];//确定位选，从个位开始
		wela=0;
		delay(1);
		r++;
		if(r==9)
			ms++;
	}
}
void key()
{
	if(key1==0)
	{
		delay(10);
		ms++;
		if(key1==0)
		{
			while(!key1)
			{
				show();
			}
			TR0=~TR0;
		}
	}
	if(key2==0)
	{
		delay(10);
		ms++;
		if(key2==0)
		{
			while(!key);
			second=0;
			ms=0;
			show();
		}
		TR0=0;
	}
			
}
void init()
{
	TH0=(65536-10000)/256;
	TL0=(65536-10000)%256;
}
void T0_() interrupt 1
{
	init();
	if(ms==99)
	{
		ms=0;
		second++;
	}
	else
		ms++;
	pickup();
}

void main()
{
	TMOD=0x01;//0000 0001
	init();
	EA=1;
	ET0=1;
	TR0=0;
	while(1)
	{
		key();
		show();
	}
}

