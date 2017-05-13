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
void i2c_init(void);			//i2c初始化
void i2c_start(void);			//开始
void i2c_stop(void);			//停止
void i2c_write(uchar byte);	//传输字节
uchar i2c_read(uchar ack);			//接收字节


uchar i2c_readbyte(uchar reg);//读一字节
uchar i2c_writebyte(uchar reg,uchar byte);//写一字节
uchar i2c_read_buf(uchar reg,uchar *date,uchar bytes);		//接收一组数据	返回操作结果
uchar i2c_write_buf(uchar reg,uchar *date,uchar bytes);	//发送一组数据	返回操作结果
#endif