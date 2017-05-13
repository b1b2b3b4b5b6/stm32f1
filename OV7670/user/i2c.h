#ifndef __I2C_H_
#define __I2C_H_
#include"init.h"

#define SLAVE 0xD0
#define PIN_SCL		GPIO_Pin_0
#define PIN_SDA	GPIO_Pin_1

#define SCL_OUT 	gpio_init_pin(GPIOA,PIN_SCL,GPIO_Mode_Out_PP)	
#define SCL_SET		GPIO_SetBits(GPIOA,PIN_SCL)
#define SCL_RESET		GPIO_ResetBits(GPIOA,PIN_SCL)

#define SDA_OUT	gpio_init_pin(GPIOA,PIN_SDA,GPIO_Mode_Out_OD)
#define SDA_SET	GPIO_SetBits(GPIOA,PIN_SDA)
#define SDA_RESET	GPIO_ResetBits(GPIOA,PIN_SDA)
#define SDA_R		GPIO_ReadInputDataBit(GPIOA,PIN_SDA)

void delay2us(void);
void i2c_init(void);			//i2c��ʼ��
void i2c_start(void);			//��ʼ
void i2c_stop(void);			//ֹͣ
void i2c_write(uchar byte);	//�����ֽ�
uchar i2c_read(uchar ack);			//�����ֽ�


uchar i2c_readbyte(uchar reg);//��һ�ֽ�
uchar i2c_writebyte(uchar reg,uchar byte);//дһ�ֽ�
uchar i2c_read_buf(uchar reg,uchar *date,uchar bytes);		//����һ������	���ز������
uchar i2c_write_buf(uchar reg,uchar *date,uchar bytes);	//����һ������	���ز������
#endif