#include <REGX51.H>


#define uchar unsigned char
sbit dula=P2^6;		 //U1���ƶˣ���ѡ
sbit wela=P2^7;		 //U2���ƶˣ�λѡ
uchar code number[]={  //�����ֵĶ�ѡ���ݣ���0��9
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
0x07,0x7f,0x6f};
uchar code digits[]={   //��λ��λѡ�������ݣ���1λ��6λ
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

    while(a)  //ȷ��num��λ��
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
	    return;	 //�������6λ��ִ����ʾ������λ���涨��������
	else
	{
	dula=1;
	P0=number[figure];	//��ѡ����
	dula=0;
	P0=0xff;			//��Ӱ
	wela=1;
	P0=digits[digit]; //λѡ����
	wela=0;
	}
}

