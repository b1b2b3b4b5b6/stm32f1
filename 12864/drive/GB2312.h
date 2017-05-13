#ifndef GB2312_H
#define GB2312_H

#include "init.h"
#include "spi.h"

#ifdef GB2312_HERE
	#define CS		GPIOA,GPIO_Pin_4

	#define OUT(arg)	gpio_init_pin(arg,GPIO_Mode_Out_PP)
	#define IN(arg)		gpio_init_pin(arg,GPIO_Mode_IPU)
	#define SET(arg)	GPIO_SetBits(arg)
	#define RESET(arg)	GPIO_ResetBits(arg)
	#define READ(arg)	GPIO_ReadInputDataBit(arg)
#endif
void GB2312_init(void);
void get_n_bytes_data_from_ROM(uchar addrHigh,uchar addrMid,uchar addrLow,uchar *pBuff,uchar DataLen );

#endif
