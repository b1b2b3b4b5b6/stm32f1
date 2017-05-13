/*
 * hmc5883l.c
 *
 * Created: 2015/11/27 20:40:29
 *  Author: God
 */ 
#include "hmc5883l.h"

u8 hmc5883l_init(void)
{
	u8 res=1;
	i2c_init();
	if(!i2c_write_reg(0, 0x6e))	res=0;	      
	if(!i2c_write_reg(1, 0x20))	res=0;
	if(!i2c_write_reg(2, 0x00))	res=0;
	return res;
}
uchar hmc5883l_read(int *gyro)	//读取磁场x,y,z，返回操作结果
{
	uchar x[6];
	u8 n,value;
	value=i2c_read_buf(3,x,6)	;
	for(n=0;n<=2;n++)
	{
		*gyro=0;
		*gyro=x[2*n];
		*gyro<<=8;
		*gyro|=x[2*n+1];
		gyro++;
	}
	return value;
}
