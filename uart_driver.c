#include<lpc21xx.h>
#include"header.h"
void uart_init(u32 baud)
{
	 s32 a[]={15,60,30,15,15};
	 u32 pclk,result=0;
	 pclk=a[VPBDIV]*1000000;
	 result=pclk/(16*baud);
	 PINSEL0|=0x05;
	 U0LCR=0x83;
	 U0DLL=(result&0xff);
	 U0DLM=((result>>8)&0xFF);

	 U0LCR=0x03	;
}
#define THRE ((U0LSR>>5)&1)
void uart_tx(u8 data)
{
	U0THR=data;
	while(THRE==0);
}
 #define RDR (U0LSR &1)
u8 uart_rx(void)
{
	while(RDR==0);
	return U0RBR;
}

void uart_tx_string(s8 *p)
{
 	while(*p)
	{
		U0THR=*p;
		while(THRE==0);
		p++;
	}
}


void uart_rx_string(s8 *p,s32 max_bytes)
{
 	s32 i;
	for(i=0; i<max_bytes; i++)
	{
		while(RDR==0);
	 p[i]=U0RBR;
	 if(p[i]=='\r')
	 break;
	}
	p[i]='\0';
}

void uart_tx_integer(s16 num)
{
char arr[10];
   int i=0;
   if(num==0)
   {
	uart_tx('0');
	return;
   }
	 
   if(num<0)
   {
	uart_tx('-');
	num=-num;
   }
   while(num>0)
   {
	arr[i]=(num%10)+48;
	num/=10;
	i++;
   }
  for(i--; i>=0; i--)
   uart_tx(arr[i]);
 }

 void uart_hex(s32 num)
{
char a[8];
sprintf(a,"%x",num);
uart_tx_string(a);
}
