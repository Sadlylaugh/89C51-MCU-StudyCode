#include <REGX51.H>


#define uchar unsigned char
sbit dula=P2^6;		 //U1控制端，段选
sbit wela=P2^7;		 //U2控制端，位选
uchar code number[]={  //各数字的段选数据，从0到9
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
0x07,0x7f,0x6f};
uchar code digits[]={   //各位的位选开启数据，从1位到6位
0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
uchar p;
int i,j;

void Show(unsigned long);

void delay(uchar p);
void ShowNum(uchar,uchar);

void main()
{    
while(1)
	 Show(25458);
}

void Show(unsigned long num)
{
    unsigned long a=num;
    uchar count=0;

    while(a)  //确定num的位数
	{
        a=a/10;
        count++;
    }
    a=num;

     for(i=0;i<count;i++)
     {
        p=a%10;
        a=a/10;
        ShowNum(p,i);
     }
}

void ShowNum(uchar figure,uchar digit)
{
	if(digit>6)
	    return;	 //如果大于6位则不执行显示操作，位数规定从右往左
	else
	{
	dula=1;
	P0=number[figure];	//段选数据
	dula=0;
	P0=0xff;			//消影
	wela=1;
	P0=digits[digit]; //位选数据
	wela=0;
	}
}

