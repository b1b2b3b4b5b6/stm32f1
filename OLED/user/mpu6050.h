#ifndef __MPU6050_H_
#define __MPU6050_H_

#include"init.h"
#include"i2c.h"

#define SMPLRT_DIV  0x19    //采样率分频，典型值：0x07(125Hz) */
#define MPU_CONFIG   0x1A       // 低通滤波频率，典型值：0x06(5Hz) */
#define GYRO_CONFIG  0x1B   // 陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s) */
#define ACCEL_CONFIG 0x1C  // 加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz) */
 
#define ACCEL_XOUT_H 0x3B  // 存储最近的X轴、Y轴、Z轴加速度感应器的测量值 */
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
 
#define TEMP_OUT_H  0x41   // 存储的最近温度传感器的测量值 */
#define TEMP_OUT_L  0x42
 
#define GYRO_XOUT_H  0x43 // 存储最近的X轴、Y轴、Z轴陀螺仪感应器的测量值 */
#define GYRO_XOUT_L  0x44 
#define GYRO_YOUT_H  0x45
#define GYRO_YOUT_L  0x46
#define GYRO_ZOUT_H  0x47
#define GYRO_ZOUT_L  0x48
 
#define PWR_MGMT_1  0x6b // 电源管理，典型值：0x00(正常启用) */
#define WHO_AM_I  0x75 //IIC地址寄存器(默认数值0x68，只读) */

void mpu6050_init(void);
uchar accel_read(int *accel);	//读取3加速度，返回操作结果
uchar gyro_read(int *gyro);		//读取3角速度，返回操作结果


#endif
