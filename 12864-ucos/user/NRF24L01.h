#ifndef __NRF24L01_H_
#define __NRF24L01_H_

#include"spi.h"

//#define READ_REG        0x00   // 读寄存器指令
//#define WRITE_REG       0x20  // 写寄存器指令
#define RD_RX_PLOAD     0x61   // 读取接收数据指令
#define WR_TX_PLOAD     0xA0   // 写待发数据指令
#define FLUSH_TX        0xE1  // 冲洗发送 FIFO指令
#define FLUSH_RX        0xE2   // 冲洗接收 FIFO指令
#define REUSE_TX_PL     0xE3   // 定义重复装载数据指令
#define NOP             0xFF   // 保留
//SPI(nRF24L01)寄存器地址
#define NRF_CONFIG          0x00  // 配置收发状态，CRC校验模式以及收发状态响应方式
#define EN_AA           0x01  // 自动应答功能设置
#define EN_RX_ADDR       0x02  // 可用信道设置
#define SETUP_AW        0x03  // 收发地址宽度设置
#define SETUP_RETR      0x04  // 自动重发功能设置
#define RF_CH           0x05  // 工作频率设置
#define RF_SETUP        0x06  // 发射速率、功耗功能设置
#define STATUS          0x07  // 状态寄存器
#define OBSERVE_TX      0x08  // 发送监测功能
#define CD              0x09  // 地址检测           
#define RX_ADDR_P0      0x0A  // 频道0接收数据地址
#define RX_ADDR_P1      0x0B  // 频道1接收数据地址
#define RX_ADDR_P2      0x0C  // 频道2接收数据地址
#define RX_ADDR_P3      0x0D  // 频道3接收数据地址
#define RX_ADDR_P4      0x0E  // 频道4接收数据地址
#define RX_ADDR_P5      0x0F  // 频道5接收数据地址
#define TX_ADDR         0x10  // 发送地址寄存器
#define RX_PW_P0        0x11  // 接收频道0接收数据长度
#define RX_PW_P1        0x12  // 接收频道0接收数据长度
#define RX_PW_P2        0x13  // 接收频道0接收数据长度
#define RX_PW_P3        0x14  // 接收频道0接收数据长度
#define RX_PW_P4        0x15  // 接收频道0接收数据长度
#define RX_PW_P5        0x16  // 接收频道0接收数据长度
#define FIFO_STATUS     0x17  // FIFO栈入栈出状态寄存器设置

#define SEND_MODE			1
#define RECEIVE_MODE		0

#define EXIT_ON			1
#define EXIT_OFF		0

#define DELAY2MS 	delay_ms(2)



//CE PC1
//IRQ PC2
#define NRF_CE_OUT			gpio_init_pin(GPIOA,GPIO_Pin_3,GPIO_Mode_Out_PP)
#define NRF_CE_SET			GPIO_SetBits(GPIOA,GPIO_Pin_3)
#define NRF_CE_CLR			GPIO_ResetBits(GPIOA,GPIO_Pin_3)

#define NRF_CSN_OUT			gpio_init_pin(GPIOA,GPIO_Pin_2,GPIO_Mode_Out_PP)
#define NRF_CSN_SET			GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define NRF_CSN_CLR			GPIO_ResetBits(GPIOA,GPIO_Pin_2)


#define NRF_IRQ_IN		gpio_init_pin(GPIOA,GPIO_Pin_4,GPIO_Mode_IPU)
#define NRF_IRQ_SET		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)	

#define NRF_BYTES 16				//发送及接收字节数
#define NRF_SPEED 1					//0-1Mbps;1-2Mbps

#define NRF_tx_address	{2,2,2,2,2};	//发送地址
#define NRF_rx_address	{2,2,2,2,2};	//接收地址

void NRF_init(uchar mode,uchar exit_receive);	//(模式，接收中断)
uchar NRF_send_mode(uchar exit_receive);		//发送模式，返回中断状态
uchar NRF_receive_mode(uchar exit_receive);		//接收模式，返回中断状态
uchar NRF_send_date(uchar *date);				//发送数据，返回0or1
uchar NRF_receive_date(uchar *date);			//接收数据，返回0or1

#endif
