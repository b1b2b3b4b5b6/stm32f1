#include"MPU6050.h"


uchar  accel_read(int *accel)
{
	uchar n,value;
	uchar x[6];
	value=i2c_read_buf(ACCEL_XOUT_H,x,6)	;
	for(n=0;n<=2;n++)
	{ 
		*accel=0;
		*accel=x[2*n];
		*accel<<=8;
		*accel|=x[2*n+1];
		accel++;
	}
	return value;
}
uchar  gyro_read(int *gyro)
{
	uchar n,value;
	uchar x[6];
	value=i2c_read_buf(GYRO_XOUT_H,x,6)	;
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
void mpu6050_init(void)                       //mpu6050³õÊ¼»¯
{
	i2c_init();
	i2c_write_byte(PWR_MGMT_1, 0x00);	      //½â³ýÐÝÃß×´Ì¬
	i2c_write_byte(SMPLRT_DIV, 0x07);
	i2c_write_byte(MPU_CONFIG, 0x06);
	i2c_write_byte(GYRO_CONFIG, 0x18);
	i2c_write_byte(ACCEL_CONFIG, 0x01);
}
