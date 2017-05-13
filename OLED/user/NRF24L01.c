#include"NRF24L01.h"

uchar TX_ADDRESS[]=NRF_tx_address;
uchar RX_ADDRESS[]=NRF_rx_address;

void NRF_init(uchar mode,uchar exit_receive)
{	
	NRF_CSN_SET;
	NRF_CSN_OUT;
	NRF_CE_OUT;
	NRF_CE_CLR;
	NRF_IRQ_SET;
	NRF_IRQ_IN;
	(mode>0)?(mode=0):(mode=1);
	(exit_receive>0)?(exit_receive=0):(exit_receive=1);
	spi_init();
	NRF_CSN_CLR;
	spi_write_reg(0x20+NRF_CONFIG,0x3e|exit_receive<<6|mode<<0);
	//����ģʽ������MAX_RT������16λCRC
	NRF_CSN_SET;
	DELAY2MS;	//����->�ϵ� ��ʱ	
	
	NRF_CSN_CLR;
	spi_write_reg(0x20+EN_RX_ADDR,0x01);				//P0����ͨ������
	NRF_CSN_SET;
	
	NRF_CSN_CLR;
	spi_write_buf(0x20+RX_ADDR_P0,RX_ADDRESS,5);		//P0���յ�ַ
	NRF_CSN_SET;
	
	NRF_CSN_CLR;
	spi_write_buf(0x20+TX_ADDR,TX_ADDRESS,5);		//���͵�ַ
	NRF_CSN_SET;
	
	NRF_CSN_CLR;
	spi_write_reg(0x20+EN_AA,1);						//poƵ���Զ�Ӧ����
	NRF_CSN_SET;
	
	NRF_CSN_CLR;
	spi_write_reg(0x20+SETUP_RETR,0x0f);			//�ط�15
	NRF_CSN_SET;
	
	NRF_CSN_CLR;
	spi_write_reg(0x20+RF_CH,0);						//Ƶ��2.4g
	NRF_CSN_SET;
	
	NRF_CSN_CLR;
	spi_write_reg(0x20+RX_PW_P0,NRF_BYTES);					//16�ֽ�����P0
	NRF_CSN_SET;
	NRF_CSN_CLR;
	spi_write_reg(0x20+RF_SETUP,0x03|NRF_SPEED<<3);				//1Mbps��0dBm���������Ŵ�����
	NRF_CSN_SET;
	
	NRF_CSN_CLR;
	spi_write_reg(0x20+STATUS,0xff);		//��������жϱ�־
	NRF_CSN_SET;
	
	NRF_CE_SET;
}

uchar NRF_send_mode(uchar exit_receive)
{	
	uchar status;
	(exit_receive>0)?(exit_receive=0):(exit_receive=1);
	
	NRF_CSN_CLR;
	status=spi_write_reg(0x20+NRF_CONFIG,0x3e|exit_receive<<6);
	NRF_CSN_SET;
	
	return status;
}

uchar NRF_receive_mode(uchar exit_receive)
{
	uchar status;
	(exit_receive>0)?(exit_receive=0):(exit_receive=1);
	
	NRF_CSN_CLR;
	status=spi_write_reg(0x20+NRF_CONFIG,0x3f|exit_receive<<6);
	NRF_CSN_SET;
	
	return status;

}

uchar NRF_send_date(uchar *date)
{	
		NRF_CSN_CLR;
		spi_write_buf(WR_TX_PLOAD,date,NRF_BYTES);
		NRF_CSN_SET;
		
		NRF_CSN_CLR;
		while((spi_read_reg(STATUS)&((1<<4)|(1<<5)))==0)
		{
			NRF_CSN_SET;
			NRF_CSN_CLR;	
		}
		NRF_CSN_SET;
		NRF_CSN_CLR;
		if ((spi_read_reg(STATUS))&(1<<4))		//����Ƿ�����ط���־
		{	
			NRF_CSN_SET;
			NRF_CSN_CLR;
			spi_write_reg(FLUSH_TX,0);
			NRF_CSN_SET;
			NRF_CSN_CLR;
			spi_write_reg(0x20+STATUS,1<<4);	//ȥ���ط���־
			NRF_CSN_SET;
			return 0;
		}
		
		NRF_CSN_CLR;
		spi_write_reg(FLUSH_TX,0);
		NRF_CSN_SET;
		
		NRF_CSN_CLR;
		spi_write_reg(0x20+STATUS,1<<5);
		NRF_CSN_SET;
		return 1;	
}

uchar NRF_receive_date(uchar *date)
{	
	NRF_CSN_CLR;
	if (~(spi_read_reg(FIFO_STATUS)&1))
	{	
		NRF_CSN_SET;
		
		NRF_CSN_CLR;
		spi_read_buf(RD_RX_PLOAD,date,NRF_BYTES);		//��ȡ����
		NRF_CSN_SET;
		
		NRF_CSN_CLR;
		if (spi_read_reg(FIFO_STATUS)&1)		//��ѯRX�Ƿ�Ϊ��
		{	
			NRF_CSN_SET;
			
			NRF_CSN_CLR;
			spi_write_reg(0x20+STATUS,1<<6);		//��������ж�
			NRF_CSN_SET;
			return 1;
		}
		return 2;
	}
	else
	{
		NRF_CSN_SET;
		return 0;
	}
}
