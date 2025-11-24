#include"header.h"
#define sw1 ((IOPIN0>>14)&1)
#define sw2     ((IOPIN0>>15)&1)
#define sw3 ((IOPIN0>>16)&1)            //r ind
extern CAN2 data;
extern int flagLI,flagRI,flagHL,flag;

void eint0_sw3()__irq          //Right Indicator
{
        flag=1;
        if(flagLI)
        flagLI=0;                               //if left indicator is on turn it off
        flagRI=(1^flagRI);
        if(flagRI)
        {
                data.byteA=0XEE;  //on
                can_tx(data);
        }
        else
        {
                data.byteA=0XFF;          //off
                can_tx(data);
        }

        EXTINT=(1<<0);
        VICVectAddr=0;
}

void eint1_sw1()__irq              //Left Indicator
{
        flag=1;
        if(flagRI)
                flagRI=0;                          //if right     indicator is on turn it off
        flagLI=(1^flagLI);
        if(flagLI)
        {
                data.byteA=0XCC;
                can_tx(data);
        }
        else
        {
                 data.byteA=0XDD;
                 can_tx(data);
        }

        EXTINT=(1<<1);
        VICVectAddr=0;
}

void eint2_sw2()__irq                     // Head Light
{
        flag=1;
        flagHL=(1^flagHL);
        if(flagHL)
        {
                data.byteA=0XAA;
                can_tx(data);
        }
        else
        {
                data.byteA=0XBB;
                can_tx(data);
        }

        EXTINT=(1<<2);
        VICVectAddr=0;
}

void config_vic(void)
{
        VICIntSelect=0;
        VICVectCntl0=(1<<5)|14;
        VICVectAddr0=(int)eint0_sw3;
        VICVectCntl1=(1<<5)|15;
        VICVectAddr1=(int)eint1_sw1;
        VICVectCntl2=(1<<5)|16;
        VICVectAddr2=(int)eint2_sw2;
        VICIntEnable=(7<<14);
}

void config_eint(void)
{
        PINSEL0|=0xa0000000;
        PINSEL1|=0X1;
        EXTMODE=0X7;
        EXTPOLAR=0X0;
}