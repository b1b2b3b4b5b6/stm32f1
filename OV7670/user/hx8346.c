/*
 * hx8346.c
 *
 * Created: 2015/10/14 21:02:06
 *  Author: God
 */ 

#include "hx8346.h"

void hx8346_gpio_init(void)
{
	BYTE_OUT;
	 
	CS_OUT;
	CS_SET;
	
	RD_OUT;
	RD_SET;
	
	RW_OUT;
	RW_SET;
	
	RS_OUT;
	RS_SET;
		
	RST_OUT;
	RST_RESET;
	delay_us(5000);//5ms复位
	RST_SET;
}
void hx8346_init(void)
{
	hx8346_gpio_init();
	CS_RESET;  //打开片选使能
	delay_us(50000);                     //根据不同晶振速度可以调整延时，保障稳定显示
	hx8346_write_com(0x11);

	hx8346_write_com(0xc5);
	hx8346_write_date(0xc5);

	hx8346_write_com(0xf0);
	hx8346_write_date(0x5a);

	hx8346_write_com(0xf2);
	hx8346_write_date(0x01);

	hx8346_write_com(0xe0);
	hx8346_write_date(0x00);
	hx8346_write_date(0x01);
	hx8346_write_date(0x06);
	hx8346_write_date(0x2e);
	hx8346_write_date(0x2b);
	hx8346_write_date(0x0b);
	hx8346_write_date(0x1a);
	hx8346_write_date(0x02);
	hx8346_write_date(0x06);
	hx8346_write_date(0x05);
	hx8346_write_date(0x0c);
	hx8346_write_date(0x0d);
	hx8346_write_date(0x00);
	hx8346_write_date(0x05);
	hx8346_write_date(0x02);
	hx8346_write_date(0x05);

	hx8346_write_com(0xe1);
	hx8346_write_date(0x06);
	hx8346_write_date(0x23);
	hx8346_write_date(0x25);
	hx8346_write_date(0x0f);
	hx8346_write_date(0x0a);
	hx8346_write_date(0x04);
	hx8346_write_date(0x02);
	hx8346_write_date(0x1a);
	hx8346_write_date(0x05);
	hx8346_write_date(0x03);
	hx8346_write_date(0x06);
	hx8346_write_date(0x01);
	hx8346_write_date(0x0c);
	hx8346_write_date(0x0b);
	hx8346_write_date(0x05);
	hx8346_write_date(0x05);

	hx8346_write_com(0x3a);
	hx8346_write_date(0x05);

	hx8346_write_com(0x36);
	hx8346_write_date(0xC8);

	hx8346_write_com(0x29);
}
void hx8346_write_com(u16 com)	 //发送命令
{
	RS_RESET;
	hx8346_write_bus(com);
}
void hx8346_write_date(u16 date)	//发送数据
{
	RS_SET;
	hx8346_write_bus(date);
}
#ifdef HX8346_16BIT 
void hx8346_write_bus(u16 bus) //并行数据写入函数
{
	SEND_BYTE(bus);
	RW_RESET;
	RW_SET;
}
#endif
#ifdef HX8346_8BIT
void hx8346_write_bus(u16 bus) //并行数据写入字节
{
	SEND_BYTE(bus>>8);
	RW_RESET;
	RW_SET;
	SEND_BYTE(bus);
	RW_RESET;
	RW_SET;	
}
#endif
void hx8346_write_reg(u16 com,u16 date)//向寄存器写入指令
{
	hx8346_write_com(com);
	hx8346_write_date(date);
}
void hx8346_add_set(u16 x1,u16 y1,u16 x2,u16 y2)////设定窗口
{
   hx8346_write_com(0x2A);
   hx8346_write_date(0x00);
   hx8346_write_date(x1);
   hx8346_write_date(0x00);
   hx8346_write_date(x2);

   hx8346_write_com(0x2b);
   hx8346_write_date(0x00);
   hx8346_write_date(y1);
   hx8346_write_date(0x00);
   hx8346_write_date(y2);
   
   hx8346_write_com(0x2c);
}
void hx8346_send_color(u8 red,u8 green,u8 blue)
{

/*	SEND_BYTE(red);
	RW_RESET;
	RW_SET;		
	SEND_BYTE(green);
	RW_RESET;
	RW_SET;
	SEND_BYTE(blue);
	RW_RESET;
	RW_SET;	*/
/*
	SEND_BYTE(red>>6);
	RW_RESET;
	RW_SET;
	SEND_BYTE((red<<4)|(green>>4));
	RW_RESET;
	RW_SET;
	SEND_BYTE((green<<6)|(blue>>2));
	RW_RESET;
	RW_SET;*/
	u16 color;
	color=(((red&0xf8)|(green>>5))<<8)|((green<<0x1c)|(blue>>3));
	hx8346_write_date(color);
}

void hx8346_paint(u8 red,u8 green,u8 blue)//设定屏幕颜色
{
	int i,j;
	hx8346_add_set(0,0,175,219);
	for(i=0;i<320;i++)
	{
		for (j=0;j<240;j++)
		{
			hx8346_send_color(red,green,blue);
		}
	}
}

