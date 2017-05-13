/*
 * xpt2046.h
 *
 * Created: 2015/10/7 18:57:00
 *  Author: God
 */ 


#ifndef XPT2046_H_
#define XPT2046_H_

#include "init.h"

#define MAX 10

#define CS_OUT			gpio_init_pin(GPIOB,GPIO_Pin_4,GPIO_Mode_Out_PP)
#define CS_SET			GPIO_SetBits(GPIOB,GPIO_Pin_4)
#define CS_RESET		GPIO_ResetBits(GPIOB,GPIO_Pin_4)

#define MOSI_OUT		gpio_init_pin(GPIOB,GPIO_Pin_3,GPIO_Mode_Out_PP)
#define MOSI_SET		GPIO_SetBits(GPIOB,GPIO_Pin_3)
#define MOSI_RESET	GPIO_ResetBits(GPIOB,GPIO_Pin_3)

#define	SCK_OUT		gpio_init_pin(GPIOB,GPIO_Pin_5,GPIO_Mode_Out_PP)
#define	SCK_SET		GPIO_SetBits(GPIOB,GPIO_Pin_5)
#define	SCK_RESET	GPIO_ResetBits(GPIOB,GPIO_Pin_5)

#define MISO_IN		gpio_init_pin(GPIOB,GPIO_Pin_1,GPIO_Mode_IPU)		
#define MISO_R			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)	

#define BUSY_IN			gpio_init_pin(GPIOB,GPIO_Pin_2,GPIO_Mode_IPU)	
#define BUSY_R			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)	

#define PENIRQ_IN		gpio_init_pin(GPIOB,GPIO_Pin_0,GPIO_Mode_IPU)
#define PENIRQ_R		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)	

void xpt2046_init(void);
u8 xpt2046_xy(u16 *p);
u8 xpt2046_read(u16 *p,u8 times);
u8 spi_rw(u8 byte);
void spi_gpio_init(void);

#endif /* XPT2046_H_ */
