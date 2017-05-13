#ifndef __MPU6050_H_
#define __MPU6050_H_

#include"init.h"
#include"i2c.h"

#define SMPLRT_DIV  0x19    //�����ʷ�Ƶ������ֵ��0x07(125Hz) */
#define MPU_CONFIG   0x1A       // ��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz) */
#define GYRO_CONFIG  0x1B   // �������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s) */
#define ACCEL_CONFIG 0x1C  // ���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz) */
 
#define ACCEL_XOUT_H 0x3B  // �洢�����X�ᡢY�ᡢZ����ٶȸ�Ӧ���Ĳ���ֵ */
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
 
#define TEMP_OUT_H  0x41   // �洢������¶ȴ������Ĳ���ֵ */
#define TEMP_OUT_L  0x42
 
#define GYRO_XOUT_H  0x43 // �洢�����X�ᡢY�ᡢZ�������Ǹ�Ӧ���Ĳ���ֵ */
#define GYRO_XOUT_L  0x44 
#define GYRO_YOUT_H  0x45
#define GYRO_YOUT_L  0x46
#define GYRO_ZOUT_H  0x47
#define GYRO_ZOUT_L  0x48
 
#define PWR_MGMT_1  0x6b // ��Դ��������ֵ��0x00(��������) */
#define WHO_AM_I  0x75 //IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��) */

void mpu6050_init(void);
uchar accel_read(int *accel);	//��ȡ3���ٶȣ����ز������
uchar gyro_read(int *gyro);		//��ȡ3���ٶȣ����ز������


#endif
