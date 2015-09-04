#include <REGX51.H>
sbit dula=P2^6;
sbit wela=P2^7;
sbit LED=P1^7;
char count;
void main()
{
    TMOD=0x01;
    TH0=(65536-45872)/256;
    TL0=(65536-45872)%256;
    EA=1;
    ET0=1;
    TR0=1;
    while(1);
}

void LED_shine () interrupt 1
{
    TH0=(65536-45872)/256;
    TL0=(65536-45872)%256;
    count++;
    if(count==10)
    {
        LED=~LED;
        count=0;
    }
}