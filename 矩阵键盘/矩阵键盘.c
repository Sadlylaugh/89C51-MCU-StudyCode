#include <t89c51Rx2.h>
#define uchar unsigned char
sbit dula=P2^6;		 //U1控制端，段选
sbit wela=P2^7;		 //U2控制端，位选
sbit led1=P1^0;
sbit led2=P1^1;
sbit led3=P1^2;
sbit led4=P1^3;
sbit led5=P1^4;
sbit led6=P1^5;
sbit led7=P1^6;
sbit led8=P1^7;


void delay(int ms)
{
	uchar i=110;
	for(ms;ms>0;ms--)
		for(i;i>0;i--);
}
//void show(uchar i)
//{
//	switch(i)
//	{
//		case 1:
//			led1=0;
//		break;
//		case 2:
//			led2=0;
//		break;
//		case 3:
//			led3=0;
//		break;
//		case 4:
//			led4=0;
//		break;
//		case 5:
//			led5=0;
//		break;
//		case 6:
//			led6=0;
//		break;
//		case 7:
//			led7=0;
//		break;
//		case 8:
//			led8=0;
//		break;
//	}
//}
uchar code number[]={  //各数字的段选数据，从0到9
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
0x07,0x7f,0x6f};
uchar code digits[]={   //各位的位选开启数据，从1位到6位
0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
void ShowNum(uchar figure)
{
	P0=number[figure];
	dula=1;
	dula=0;


}
void keyscan()
{
		uchar temp,led;
		P3=0xfe;
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{
			delay(10);
			temp=P3;
			temp=temp&0xf0;
			if(temp!=0xf0)
			{
				switch(temp)
				{
					case 0xee:
						led=1;
						break;
					case 0xde:
						led=2;
						break;
					case 0xbe:
						led=3;
						break;
					case 0x7e:
						led=4;
						break;
				}
			}
			while(temp!=0xf0)
			{
				temp=P3;
				temp=temp&0xf0;
			}
			ShowNum(led);
		}

		P3=0xfd;
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{
			delay(12);
			temp=P3;
			temp=temp&0xf0;
			if(temp!=0xf0)
			{
				switch(temp)
				{
					case 0xed:
						led=5;
						break;
					case 0xdd:
						led=6;
						break;
					case 0xbd:
						led=7;
						break;
					case 0x7d:
						led=8;
						break;
				}
		 }
			while(temp!=0xf0)
			{
				temp=P3;
				temp=temp&0xf0;
			}
			ShowNum(led);

	 }
}

void main()
{
	P0=0;
	dula=1;
	dula=0;
	P0=0xc0;
	wela=1;
	wela=0;
	while(1)
	{
		keyscan();
	}
}
	