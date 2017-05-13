#include "xpt2046.h"

void spi_gpio_init(void)
{
	SCK_OUT;
	SCK_RESET;
	MOSI_OUT;
	MOSI_SET;
	MISO_IN;
}
void xpt2046_init(void) 
{
	spi_gpio_init();
	CS_SET;
	CS_OUT;
	BUSY_IN;
	PENIRQ_IN;
	
	CS_RESET;
	spi_rw(0xd0);
	spi_rw(0);
	spi_rw(0);
	CS_SET;
	
}
u8 spi_rw(u8 byte)
{
	u8 n;
	for(n=0;n<8;n++)
	{
		if((byte&0x80)==0)
		{
			MOSI_RESET;
		}
		else
		{
			MOSI_SET;
		}
		byte<<=1;
		SCK_SET;
		byte|=MISO_R;
		SCK_RESET;
	}
	return byte;
}
u8 xpt2046_xy(u16 *p)
{
	spi_rw(0xd0);
	*p=0;
	SCK_SET;
	SCK_RESET;
	delay_us(10);	
	*p=spi_rw(0);
	*p<<=4;
	*p|=(spi_rw(0x90)>>4);
	if (*p<100) return 0;
	
	SCK_SET;
	SCK_RESET;
	delay_us(10);
	p++;
	*p=0;	
	*p=spi_rw(0);
	*p<<=4;
	*p|=(spi_rw(0)>>4);
	if(*p>4000) return 0;
	
	return 1;
}

u8 xpt2046_read(u16 *p,u8 times)
{
	u16 group[2][20];
	u16 temp[2];
	u16 x;
	char i,j;
	CS_RESET;	
	for (j=0,i=0;j<times;j++)
	{
		if (xpt2046_xy(temp))
		{
			group[0][j]=temp[0];
			group[1][j]=temp[1];	
			i++;		
		}
	}
	CS_SET;	
	if (i<(times-2))
	{
		return 0;
	}
for (j=times-1;j>0;j--)
{
	for (i=0;i<j;i++)
	{
		if (group[0][i]>group[0][i+1])
		{
			x=group[0][i+1];
			group[0][i+1]=group[0][i];
			group[0][i]=x;
		}
		if (group[1][i]>group[1][i+1])
		{
			x=group[1][i+1];
			group[1][i+1]=group[1][i];
			group[1][i]=x;
		}
	}
}
if ((group[0][5]-group[0][4])>MAX)
{
	return 0;
}
if ((group[1][5]-group[1][4])>MAX)
{
	return 0;
}
*p=(group[0][4]+group[0][5])/2;
*p=(*p-240)/14.7;

p++;
*p=(group[1][4]+group[1][5])/2;
*p=(*p-390)/11.16;

return 1;
}
