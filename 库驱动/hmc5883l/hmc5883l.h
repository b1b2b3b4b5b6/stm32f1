/*
 * hmc5883l.h
 *
 * Created: 2015/11/27 20:40:17
 *  Author: God
 */ 


#ifndef HMC5883L_H_
#define HMC5883L_H_

#include "i2c.h"

u8 hmc5883l_init(void);
uchar hmc5883l_read(int *gyro);	//读取磁场x,y,z，返回操作结果
#endif /* HMC5883L_H_ */
