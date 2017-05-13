/*
 * hx8346.h
 *
 * Created: 2015/10/14 21:02:16
 *  Author: God
 */ 


#ifndef HX8346_H_
#define HX8346_H_

#include "init.h"
#define  HX8346_16BIT

#ifdef HX8346_8BIT
#define RST_OUT	gpio_init_pin(GPIOB,GPIO_Pin_11,GPIO_Mode_Out_PP)
#define RST_SET		GPIO_SetBits(GPIOB,GPIO_Pin_11)
#define RST_RESET	GPIO_ResetBits(GPIOB,GPIO_Pin_11)

#define CS_OUT		gpio_init_pin(GPIOB,GPIO_Pin_12,GPIO_Mode_Out_PP)
#define CS_SET		GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define CS_RESET	GPIO_ResetBits(GPIOB,GPIO_Pin_12)

#define RD_OUT		gpio_init_pin(GPIOB,GPIO_Pin_13,GPIO_Mode_Out_PP)
#define RD_SET		GPIO_SetBits(GPIOB,GPIO_Pin_13)
#define RD_RESET	GPIO_ResetBits(GPIOB,GPIO_Pin_13)


#define RW_OUT	gpio_init_pin(GPIOB,GPIO_Pin_14,GPIO_Mode_Out_PP)
#define RW_SET		GPIO_SetBits(GPIOB,GPIO_Pin_14)
#define RW_RESET	GPIO_ResetBits(GPIOB,GPIO_Pin_14)

#define RS_OUT		gpio_init_pin(GPIOB,GPIO_Pin_15,GPIO_Mode_Out_PP)
#define RS_SET		GPIO_SetBits(GPIOB,GPIO_Pin_15)
#define RS_RESET	GPIO_ResetBits(GPIOB,GPIO_Pin_15)

/*
#define RST_OUT	gpio_init_pin(GPIOA,GPIO_Pin_12,GPIO_Mode_Out_PP)
#define RST_SET		GPIO_SetBits(GPIOA,GPIO_Pin_12)
#define RST_RESET	GPIO_ResetBits(GPIOA,GPIO_Pin_12)

#define CS_OUT		gpio_init_pin(GPIOA,GPIO_Pin_11,GPIO_Mode_Out_PP)
#define CS_SET		GPIO_SetBits(GPIOA,GPIO_Pin_11)
#define CS_RESET	GPIO_ResetBits(GPIOA,GPIO_Pin_11)


#define RD_OUT		gpio_init_pin(GPIOA,GPIO_Pin_10,GPIO_Mode_Out_PP)
#define RD_SET		GPIO_SetBits(GPIOA,GPIO_Pin_10)
#define RD_RESET	GPIO_ResetBits(GPIOA,GPIO_Pin_10)

#define RW_OUT	gpio_init_pin(GPIOA,GPIO_Pin_9,GPIO_Mode_Out_PP)
#define RW_SET		GPIO_SetBits(GPIOA,GPIO_Pin_9)
#define RW_RESET	GPIO_ResetBits(GPIOA,GPIO_Pin_9)

#define RS_OUT		gpio_init_pin(GPIOA,GPIO_Pin_8,GPIO_Mode_Out_PP)
#define RS_SET		GPIO_SetBits(GPIOA,GPIO_Pin_8)
#define RS_RESET	GPIO_ResetBits(GPIOA,GPIO_Pin_8)*/

#define BYTE_OUT		gpio_init_pin(GPIOA,0x00ff,GPIO_Mode_Out_PP)
#define SEND_BYTE(BYTE)		GPIOA->ODR=(GPIOA->ODR&0xffffffff00)|(u8)(BYTE)
#endif

#ifdef HX8346_16BIT
#define RST_OUT	gpio_init_pin(GPIOA,GPIO_Pin_12,GPIO_Mode_Out_PP)
#define RST_SET		GPIO_SetBits(GPIOA,GPIO_Pin_12)
#define RST_RESET	GPIO_ResetBits(GPIOA,GPIO_Pin_12)

#define CS_OUT		gpio_init_pin(GPIOA,GPIO_Pin_11,GPIO_Mode_Out_PP)
#define CS_SET		GPIO_SetBits(GPIOA,GPIO_Pin_11)
#define CS_RESET	GPIO_ResetBits(GPIOA,GPIO_Pin_11)

#define RD_OUT		gpio_init_pin(GPIOA,GPIO_Pin_10,GPIO_Mode_Out_PP)
#define RD_SET		GPIO_SetBits(GPIOA,GPIO_Pin_10)
#define RD_RESET	GPIO_ResetBits(GPIOA,GPIO_Pin_10)

#define RW_OUT	gpio_init_pin(GPIOA,GPIO_Pin_9,GPIO_Mode_Out_PP)
#define RW_SET		GPIO_SetBits(GPIOA,GPIO_Pin_9)
#define RW_RESET	GPIO_ResetBits(GPIOA,GPIO_Pin_9)

#define RS_OUT		gpio_init_pin(GPIOA,GPIO_Pin_8,GPIO_Mode_Out_PP)
#define RS_SET		GPIO_SetBits(GPIOA,GPIO_Pin_8)
#define RS_RESET	GPIO_ResetBits(GPIOA,GPIO_Pin_8)

#define BYTE_OUT		gpio_init_pin(GPIOB,0xffff,GPIO_Mode_Out_PP)
#define SEND_BYTE(BYTE)		GPIOB->ODR=BYTE
#endif

void hx8346_gpio_init(void);
void hx8346_init(void);
void hx8346_write_com(u16   com);		 //发送命令
void hx8346_write_date(u16 date);		//发送数据
void hx8346_write_bus(u16 bus);				//并行数据写入函数
void hx8346_write_reg(u16 com,u16 date);	//向寄存器写入指令
void hx8346_add_set(u16 x1,u16 y1,u16 x2,u16 y2);//设定窗口
void hx8346_paint(u8 red,u8 green,u8 blue);//设定屏幕颜色
void hx8346_send_color(u8 red,u8 green,u8 blue);	//写入GRAM

#endif /* HX8346_H_ */

