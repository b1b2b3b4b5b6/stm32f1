#ifndef __NRF24L01_H_
#define __NRF24L01_H_

#include"spi.h"

//#define READ_REG        0x00   // ���Ĵ���ָ��
//#define WRITE_REG       0x20  // д�Ĵ���ָ��
#define RD_RX_PLOAD     0x61   // ��ȡ��������ָ��
#define WR_TX_PLOAD     0xA0   // д��������ָ��
#define FLUSH_TX        0xE1  // ��ϴ���� FIFOָ��
#define FLUSH_RX        0xE2   // ��ϴ���� FIFOָ��
#define REUSE_TX_PL     0xE3   // �����ظ�װ������ָ��
#define NOP             0xFF   // ����
//SPI(nRF24L01)�Ĵ�����ַ
#define NRF_CONFIG          0x00  // �����շ�״̬��CRCУ��ģʽ�Լ��շ�״̬��Ӧ��ʽ
#define EN_AA           0x01  // �Զ�Ӧ��������
#define EN_RX_ADDR       0x02  // �����ŵ�����
#define SETUP_AW        0x03  // �շ���ַ�������
#define SETUP_RETR      0x04  // �Զ��ط���������
#define RF_CH           0x05  // ����Ƶ������
#define RF_SETUP        0x06  // �������ʡ����Ĺ�������
#define STATUS          0x07  // ״̬�Ĵ���
#define OBSERVE_TX      0x08  // ���ͼ�⹦��
#define CD              0x09  // ��ַ���           
#define RX_ADDR_P0      0x0A  // Ƶ��0�������ݵ�ַ
#define RX_ADDR_P1      0x0B  // Ƶ��1�������ݵ�ַ
#define RX_ADDR_P2      0x0C  // Ƶ��2�������ݵ�ַ
#define RX_ADDR_P3      0x0D  // Ƶ��3�������ݵ�ַ
#define RX_ADDR_P4      0x0E  // Ƶ��4�������ݵ�ַ
#define RX_ADDR_P5      0x0F  // Ƶ��5�������ݵ�ַ
#define TX_ADDR         0x10  // ���͵�ַ�Ĵ���
#define RX_PW_P0        0x11  // ����Ƶ��0�������ݳ���
#define RX_PW_P1        0x12  // ����Ƶ��0�������ݳ���
#define RX_PW_P2        0x13  // ����Ƶ��0�������ݳ���
#define RX_PW_P3        0x14  // ����Ƶ��0�������ݳ���
#define RX_PW_P4        0x15  // ����Ƶ��0�������ݳ���
#define RX_PW_P5        0x16  // ����Ƶ��0�������ݳ���
#define FIFO_STATUS     0x17  // FIFOջ��ջ��״̬�Ĵ�������

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

#define NRF_BYTES 16				//���ͼ������ֽ���
#define NRF_SPEED 1					//0-1Mbps;1-2Mbps

#define NRF_tx_address	{2,2,2,2,2};	//���͵�ַ
#define NRF_rx_address	{2,2,2,2,2};	//���յ�ַ

void NRF_init(uchar mode,uchar exit_receive);	//(ģʽ�������ж�)
uchar NRF_send_mode(uchar exit_receive);		//����ģʽ�������ж�״̬
uchar NRF_receive_mode(uchar exit_receive);		//����ģʽ�������ж�״̬
uchar NRF_send_date(uchar *date);				//�������ݣ�����0or1
uchar NRF_receive_date(uchar *date);			//�������ݣ�����0or1

#endif
