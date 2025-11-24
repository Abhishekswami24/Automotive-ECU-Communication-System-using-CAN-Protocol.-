#include <LPC21xx.H>
#include<stdio.h>

typedef unsigned int u32;
typedef signed int s32;
typedef unsigned char u8;
typedef signed char s8;
typedef float f32;
typedef	unsigned short int u16;
typedef	signed short int s16;

#define sw1 ((IOPIN0>>14)&1)   //P0.14
#define sw2 ((IOPIN0>>15)&1)   //P0.15
#define sw3 ((IOPIN0>>16)&1)   //P0.16

extern void delay_ms(u32 ms);

typedef struct can2
{
	u32 id;
	u32 rtr;
	u32 dlc;
	u32 byteA;
	u32 byteB;
}CAN1;

extern void can_init(void);
extern void can_tx(CAN1 v);
extern void can_rx(CAN1 *ptr);
extern void uart0_tx_hex(s32 num);
extern void config_vic(void);
extern void can2_rx_intr_en(void);

extern void lcd_data(u8 data);
extern void lcd_cmd(u8 cmd);
extern void lcd_init(void);
extern void lcd_string(s8 *ptr);
void lcd_cgram(void);

extern void config_eint(void);
extern void config_vic(void);
void en_can2_intrpt(void);
