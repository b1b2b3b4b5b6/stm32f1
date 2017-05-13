#include "xpt2046.h"

void xpt_spi_gpio_init(void)
{
	XPT_SCK_OUT;
	XPT_SCK_RESET;
	XPT_MOSI_OUT;
	XPT_MOSI_SET;
	XPT_MISO_IN;
}
void xpt2046_init(void) 
{
	xpt_spi_gpio_init();
	XPT_CS_SET;
	XPT_CS_OUT;
	XPT_PENIRQ_IN;
	
	XPT_CS_RESET;
	xpt_spi_rw(0xd0);
	xpt_spi_rw(0);
	xpt_spi_rw(0);
	XPT_CS_SET;
}
u8 xpt_spi_rw(u8 byte)
{
	u8 n;

	for(n=0;n<8;n++)
	{
		if((byte&0x80)==0)
		{
			XPT_MOSI_RESET;
		}
		else
		{
			XPT_MOSI_SET;
		}
		byte<<=1;
		XPT_SCK_SET;
		byte|=XPT_MISO_R;
		XPT_SCK_RESET;
	}



	return byte;
}
u8 xpt2046_xy(u16 *p)
{
	xpt_spi_rw(0xd0);
	*p=0;
	XPT_SCK_SET;
	XPT_SCK_RESET;
	delay_us(10);	
	*p=xpt_spi_rw(0);
	*p<<=4;
	*p|=(xpt_spi_rw(0x90)>>4);
	if (*p<100) return 0;
	
	XPT_SCK_SET;
	XPT_SCK_RESET;
	delay_us(10);
	p++;
	*p=0;	
	*p=xpt_spi_rw(0);
	*p<<=4;
	*p|=(xpt_spi_rw(0)>>4);
	if(*p>4000) return 0;
	
	return 1;
}

u8 xpt2046_read(u16 *p,u8 times)
{
	u16 group[2][20];
	u16 temp[2];
	u16 x;
	char i,j;
	XPT_CS_RESET;	
	for (j=0,i=0;j<times;j++)
	{
		if (xpt2046_xy(temp))
		{
			group[0][j]=temp[0];
			group[1][j]=temp[1];	
			i++;		
		}
	}
	XPT_CS_SET;	
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
