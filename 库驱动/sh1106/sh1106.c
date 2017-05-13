
#include "sh1106.h"
#include "OLEDfont.h"

void  sh1106_set_addr(u8 x, u8 y) 
{ 
	sh1106_write_cmd(0xb0 + y - 1);
	sh1106_write_cmd(((x&0xf0)>>4)|0x10);
	sh1106_write_cmd((x&0x0f) + 1); 
}   	

void sh1106_draw_byte(u8 x, u8 y, u8 value)
{
	sh1106_set_addr(x, y);
	sh1106_write_data(value);
}

void sh1106_draw_bytes(u8 x, u8 y, u8 *buf, u8 len)
{
	sh1106_set_addr(x, y);
	i2c_write_buf(SLAVE, 0x40, (u8 *)buf, len);
}

//开启OLED显示    
void sh1106_display_on(void)
{
	sh1106_write_cmd(0X8D);  //SET DCDC命令
	sh1106_write_cmd(0X14);  //DCDC ON
	sh1106_write_cmd(0XAF);  //DISPLAY ON
}
//关闭OLED显示     
void Osh1106_display_off(void)
{
	sh1106_write_cmd(0X8D);  //SET DCDC命令
	sh1106_write_cmd(0X10);  //DCDC OFF
	sh1106_write_cmd(0XAE);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void sh1106_clear(void)  
{  
	u8 buf[128] = {0};
	for(int y = 1; y <= 8; y++)
		sh1106_draw_bytes(1, y, buf, 128);
}

void sh1106_draw_frame(u8 *buf)
{
	for(int y = 1; y <= 8; y++)
	{
		sh1106_draw_bytes(1, y, buf, 128);
		buf += 128;
	}	
}

void sh1106_show_char(u8 x, u8 y, u8 c, u8 size)
{
	switch(size)
	{
		case 8:
		{
			c = c - 32;
			sh1106_draw_bytes(x, y, (u8 *)&F8X16[c][0], 8);
			sh1106_draw_bytes(x, y + 1, (u8 *)&F8X16[c][1*8], 8);
		}
		break;
		
		case 16:
		{
		
		}
		break;
		
		case 24:
		{
			c = c - 32;
			sh1106_draw_bytes(x, y, (u8 *)&F24X48[c][0], 24);
			sh1106_draw_bytes(x, y+1, (u8 *)&F24X48[c][1*24], 24);
			sh1106_draw_bytes(x, y+2, (u8 *)&F24X48[c][2*24], 24);
			sh1106_draw_bytes(x, y+3, (u8 *)&F24X48[c][3*24], 24);
			sh1106_draw_bytes(x, y+4, (u8 *)&F24X48[c][4*24], 24);
			sh1106_draw_bytes(x, y+5, (u8 *)&F24X48[c][5*24], 24);
		}
		
		default :
		break;
		
	}
}

void sh1106_show_string(u8 x, u8 y, char *str, u8 size)
{
	while(*str != 0)
	{
		sh1106_show_char(x, y, *str, size);
		str++;
		x += size;
	}
}
				    
void sh1106_init(void)
{
	i2c_init();
	
	sh1106_write_cmd(0xAE);//--display off
	sh1106_write_cmd(0x02);//---set low column address
	sh1106_write_cmd(0x10);//---set high column address
	sh1106_write_cmd(0x40);//--set start line address  
	sh1106_write_cmd(0xB0);//--set page address
	sh1106_write_cmd(0x81); // contract control
	sh1106_write_cmd(0xFF);//--128   
	sh1106_write_cmd(0xA1);//set segment remap 
	sh1106_write_cmd(0xA6);//--normal / reverse
	sh1106_write_cmd(0xA8);//--set multiplex ratio(1 to 64)
	sh1106_write_cmd(0x3F);//--1/64 duty
	sh1106_write_cmd(0xAD);//set charge pump enable
	sh1106_write_cmd(0x8B);//-0x8B 内供 VCC
	sh1106_write_cmd(0x33);//-0X30---0X33 set VPP 9V
	sh1106_write_cmd(0xC8);//Com scan direction
	sh1106_write_cmd(0xD3);//-set display offset
	sh1106_write_cmd(0x00);//
	
	sh1106_write_cmd(0xD5);//set osc division
	sh1106_write_cmd(0x80);//
	
	sh1106_write_cmd(0xD8);//set area color mode off
	sh1106_write_cmd(0x05);//
	
	sh1106_write_cmd(0xD9);//Set Pre-Charge Period
	sh1106_write_cmd(0x1F);//
	
	sh1106_write_cmd(0xDA);//set com pin configuartion
	sh1106_write_cmd(0x12);//
	
	sh1106_write_cmd(0xDB);//set Vcomh
	sh1106_write_cmd(0x40);//
	
	
	sh1106_write_cmd(0xAF);//--turn on oled panel
}  

#undef SLAVE


