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
	//设置模式，屏蔽MAX_RT，开启16位CRC
	NRF_CSN_SET;
	DELAY2MS;	//待机->上电 延时	
	
	NRF_CSN_CLR;
	spi_write_reg(0x20+EN_RX_ADDR,0x01);				//P0接受通道允许
	NRF_CSN_SET;
	
	NRF_CSN_CLR;
	spi_write_buf(0x20+RX_ADDR_P0,RX_ADDRESS,5);		//P0接收地址
	NRF_CSN_SET;
	
	NRF_CSN_CLR;
	spi_write_buf(0x20+TX_ADDR,TX_ADDRESS,5);		//发送地址
	NRF_CSN_SET;
	
	NRF_CSN_CLR;
	spi_write_reg(0x20+EN_AA,1);						//po频道自动应答开启
	NRF_CSN_SET;
	
	NRF_CSN_CLR;
	spi_write_reg(0x20+SETUP_RETR,0x0f);			//重发15
	NRF_CSN_SET;
	
	NRF_CSN_CLR;
	spi_write_reg(0x20+RF_CH,0);						//频率2.4g
	NRF_CSN_SET;
	
	NRF_CSN_CLR;
	spi_write_reg(0x20+RX_PW_P0,NRF_BYTES);					//16字节数据P0
	NRF_CSN_SET;
	NRF_CSN_CLR;
	spi_write_reg(0x20+RF_SETUP,0x03|NRF_SPEED<<3);				//1Mbps，0dBm，低噪声放大增益
	NRF_CSN_SET;
	
	NRF_CSN_CLR;
	spi_write_reg(0x20+STATUS,0xff);		//清除所有中断标志
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
		if ((spi_read_reg(STATUS))&(1<<4))		//检查是否产生重发标志
		{	
			NRF_CSN_SET;
			NRF_CSN_CLR;
			spi_write_reg(FLUSH_TX,0);
			NRF_CSN_SET;
			NRF_CSN_CLR;
			spi_write_reg(0x20+STATUS,1<<4);	//去除重发标志
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
		spi_read_buf(RD_RX_PLOAD,date,NRF_BYTES);		//读取数据
		NRF_CSN_SET;
		
		NRF_CSN_CLR;
		if (spi_read_reg(FIFO_STATUS)&1)		//查询RX是否为空
		{	
			NRF_CSN_SET;
			
			NRF_CSN_CLR;
			spi_write_reg(0x20+STATUS,1<<6);		//清除接收中断
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
