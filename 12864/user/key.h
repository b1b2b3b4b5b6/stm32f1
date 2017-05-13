#ifndef KEY_H
#define KEY_H

#include "init.h"



#define SHAKE_DELAY	delay_ms(3)	//us

#define ERR 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define OK 5

#define KEY_OK		GPIOB,GPIO_Pin_11
#define KEY_UP		GPIOB,GPIO_Pin_12
#define KEY_RIGHT	GPIOB,GPIO_Pin_13
#define KEY_DOWN	GPIOB,GPIO_Pin_14
#define KEY_LEFT	GPIOB,GPIO_Pin_15

#define R_OK	GPIO_ReadInputDataBit(KEY_OK)
#define R_UP	GPIO_ReadInputDataBit(KEY_UP)
#define R_DOWN	GPIO_ReadInputDataBit(KEY_DOWN)
#define R_LEFT	GPIO_ReadInputDataBit(KEY_LEFT)
#define R_RIGHT	GPIO_ReadInputDataBit(KEY_RIGHT)
void key_init(void);
u8 get_key(void);

#endif
