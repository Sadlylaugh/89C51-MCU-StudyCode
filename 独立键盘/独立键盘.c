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
sbit dula=P2^6;//dula ��ѡ
sbit wela=P2^7;//wela	λѡ
uchar ms=0;//ʮ����λ��һ����λ
uint second=0;//��λ��һ����λ
uchar code number[]={  //�����ֵĶ�ѡ���ݣ�������Ϊ0��9
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
char numbers[]={		//�����ʮ�������黯
	//������Ϊʮ��λ����λ
	0,0,0,0,0,0};
uchar code digits[]={ 
  //��λ��λѡ�������ݣ�������Ϊ��λ��ʮ��λ
0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
void pickup()
{
	uchar i;
	uint p;
	numbers[5]=ms%10;//���λ��Ϊʮ����λ����
	numbers[4]=ms/10;//�����ڶ�λ��Ϊ�ٺ���λ����
	p=second;
	for(i=4;i>0;i--)//�����λ��ʼȡ���λ�ϵ�����
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
		P0=number[numbers[i-1]];//�Ӹ�λ��ʼ�Ͷ�ѡ����
		if(i==4)
		{
			dp=1;
		}
		dula=0;
		P0=0xff;
		wela=1;
		P0=digits[6-i];//ȷ��λѡ���Ӹ�λ��ʼ
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

