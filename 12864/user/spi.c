/*
 * spi.c
 *
 * Created: 2015/10/25 0:03:38
 *  Author: God
 */ 
#include "spi.h"



void spi_init(void)
{
	SPI_InitTypeDef SPI_InitStruct;
	SPI_StructInit(&SPI_InitStruct);
	SPI_InitStruct.SPI_Mode=SPI_Mode_Master;
	SPI_InitStruct.SPI_BaudRatePrescaler =SPI_SPEED;		//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;		//管理:内部NSS信号由SSI位控制
	SPI_Init(SPIX, &SPI_InitStruct);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
	SPI_Cmd(SPIX, ENABLE); //使能SPI外设
	spi_gpio_init();
}

void spi_gpio_init()
{

		gpio_init_pin(GPIOA,GPIO_Pin_5,GPIO_Mode_AF_PP);
		gpio_init_pin(GPIOA,GPIO_Pin_6,GPIO_Mode_IPU);		
		gpio_init_pin(GPIOA,GPIO_Pin_7,GPIO_Mode_AF_PP);


/*
	gpio_init_pin(GPIOB,GPIO_Pin_13,GPIO_Mode_AF_PP);
	gpio_init_pin(GPIOB,GPIO_Pin_14,GPIO_Mode_IPU);
	gpio_init_pin(GPIOB,GPIO_Pin_15,GPIO_Mode_AF_PP);*/

}

u16 spi_rw(u16 byte)
{
	SPI_I2S_SendData(SPIX, byte);
	while(!SPI_I2S_GetFlagStatus(SPIX,SPI_I2S_FLAG_RXNE));
	byte=SPI_I2S_ReceiveData(SPIX);
	return byte;
}

uchar spi_write_reg(uchar reg, uchar value)
{
	uchar status;
	status = spi_rw(reg);
	spi_rw(value);
	return	status;
}



uchar spi_read_reg(uchar reg)
{
	uchar value;
	spi_rw(reg);
	value=spi_rw(0);
	return value;
}

uchar spi_write_buf(uchar reg,uchar *Buf,uchar n)
{
	uchar i,status;
	status=spi_rw(reg);
	for(i=0;i<n;i++)
	{
		spi_rw(*Buf);
		Buf++;
	}
	return status;
}
uchar spi_read_buf(uchar reg,uchar *Buf,uchar n)
{
	uchar i,status;
	spi_rw(reg);
	for(i=0;i<n;i++)
	{
		*Buf=spi_rw(0);
		Buf++;
	}
	return status;
}

void spi_speed(u32 SPI_BaudRatePrescaler)
{
	 assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	 SPI_Cmd(SPIX, DISABLE); //禁止SPI外设
	 SPIX->CR1=(SPIX->CR1&~0x0038)|SPI_BaudRatePrescaler;
	 SPI_Cmd(SPIX, ENABLE); //使能SPI外设
}
