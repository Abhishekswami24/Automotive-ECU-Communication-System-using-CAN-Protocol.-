#include "header.h"
extern int flag;
extern CAN1 data;

void can2_rx_handler()__irq
{
        flag=1;
        data.id=C2RID;
        data.dlc=(C2RFS>>16)&0XF;
        data.rtr=(C2RFS>>30)&1;
        if(data.rtr==0)
        {
                data.byteA=C2RDA;
                data.byteB=C2RDB;
        }
        C2CMR=(1<<2);
        VICVectAddr=0;
}

void config_vic(void)
{
        VICIntSelect=0;
        VICVectCntl0=(1<<5)|27;
        VICVectAddr0=(int)can2_rx_handler;
        VICIntEnable=(1<<27);
}

void en_can2_intrpt(void)
{
         C2IER=0x1;
}
