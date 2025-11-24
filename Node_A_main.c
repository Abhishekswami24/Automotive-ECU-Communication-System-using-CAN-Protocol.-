#include"header.h"
CAN2 data;
int flagLI=0,flagRI=0,flagHL=0,flag=0;
int main()
{
        can_init();
        data.id=0XDF;
        data.rtr=0;
        data.dlc=8;
        data.byteA=0;
        data.byteB=0;

        config_vic();
        config_eint();

        while(1){
        if(flag)
        flag=0;
        }
}