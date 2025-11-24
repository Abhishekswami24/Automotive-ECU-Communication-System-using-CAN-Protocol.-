#include "header.h"
#define LED1 (1<<17)
#define LED2 (1<<18)
#define LED3 (1<<19)

CAN1 data;
int flag=0, f_LI=0, f_RI=0, f_HL=0;

int main()
{
        IODIR0 |= LED1 | LED2 | LED3;
        IOSET0 |= LED1 | LED2 | LED3;

        can_init();
        config_vic();
        en_can2_intrpt();

        while(1)
        {
                if(flag == 1)
                {
                        flag = 0;

                        /**************************Left Indicator**************/
                        if(data.byteA == 0xCC)
                        {
                                if(f_RI)
                                        f_RI = 0;
                                f_LI = 1;
                        }
                        else if(data.byteA == 0xDD)
                                f_LI = 0;

                        /***********************Right Indicator*****************/
                        if(data.byteA == 0xEE)
                        {
                                if(f_LI)
                                        f_LI = 0;
                                f_RI = 1;
                        }
                        else if(data.byteA == 0xFF)
                                f_RI = 0;

                        /**************************Head Light***************/
                        if(data.byteA == 0xAA)
                        {
                                f_HL = 1;
                        }
                        else if(data.byteA == 0xBB)
                        {
                                f_HL = 0;
                        }

                        /***********HL-sw2-LED2*************/
                        if(f_HL)
                        {
                                IOCLR0 = LED2;
                        }
                        else
                        {
                                IOSET0 = LED2;
                        }

                        /***********LI-sw1-LED3*************/
                        if(f_LI)
                        {
                                while(flag == 0)
                                {
                                        IOCLR0 = LED3;
                                        delay_ms(100);
                                        IOSET0 = LED3;
                                        delay_ms(100);
                                }
                        }
                        else
                        {
                                IOSET0 = LED3;
                        }

                        /***********RI-sw3-LED1*************/
                        if(f_RI)
                        {
                                while(flag == 0)
                                {
                                        IOCLR0 = LED1;
                                        delay_ms(100);
                                        IOSET0 = LED1;
                                        delay_ms(100);
                                }
                        }
                        else
                        {
                                IOSET0 = LED1;
                        }
                }
        }
}
