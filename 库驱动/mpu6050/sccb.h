#ifndef __SCCB_H
#define __SCCB_H
#include "init.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ο�������guanfu_wang���롣
//ALIENTEKս��STM32������V3
//SCCB ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/18
//�汾��V1.0		    							    							  
//////////////////////////////////////////////////////////////////////////////////
#define PIN_SCL		GPIO_Pin_0
#define PIN_SDA		GPIO_Pin_1

#define SCCB_SCL_OUT 			gpio_init_pin(GPIOA,PIN_SCL,GPIO_Mode_Out_PP)
#define SCCB_SCL_SET			GPIO_SetBits(GPIOA,PIN_SCL)
#define SCCB_SCL_RESET		GPIO_ResetBits(GPIOA,PIN_SCL)

#define SCCB_SDA_OUT			gpio_init_pin(GPIOA,PIN_SDA,GPIO_Mode_Out_PP)
#define SCCB_SDA_IN				gpio_init_pin(GPIOA,PIN_SDA,GPIO_Mode_IPU)
#define SCCB_SDA_SET			GPIO_SetBits(GPIOA,PIN_SDA)
#define SCCB_SDA_RESET		GPIO_ResetBits(GPIOA,PIN_SDA)
#define SCCB_SDA_R				GPIO_ReadInputDataBit(GPIOA,PIN_SDA)

#define DELAY50US		delay_us(50)
#define DELAY100US		delay_us(100)
 	
#define SCCB_ID   		0X42  			//OV7670��ID

///////////////////////////////////////////
void sccb_init(void);
void sccb_start(void);
void sccb_stop(void);
void sccb_no_ack(void);
u8 sccb_write_byte(u8 dat);
u8 sccb_read_byte(void);
u8 sccb_write_reg(u8 reg,u8 data);
u8 sccb_read_reg(u8 reg);
#endif













