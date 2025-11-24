#include <LPC21xx.H>
#include"header.h"
#define select_tx_buf1 (1<<5)
#define start_tx (1<<0)
#define RBS (C2GSR&1)
#define RRB (1<<2)

void can_init()
{
	PINSEL1|=0X14000;
	VPBDIV=1;
	C2MOD=0X1;
	C2BTR=0x001C001D;
	AFMR=0X2;
	C2MOD=0;
}

void can_tx(CAN1 v)
{
	C2TID1=v.id;
	C2TFI1=(v.dlc<<16);
	if(v.rtr==0)
	{
		C2TFI1&=~(1<<30);
		C2TDA1=v.byteA;
		C2TDB1=v.byteB;
	}
	else
		C2TFI1|=(1<<30);
	C2CMR=(start_tx|select_tx_buf1);
	while((C2GSR>>3)&1==0);
}
