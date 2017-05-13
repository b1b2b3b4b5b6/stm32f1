#include "display.h"
#include "numfont.h"
#include "stdio.h"
#include <string.h>

void show_num_char(u8 page, u8 column, char c, u8 size)
{
	c = c - '0';
	switch(size)
	{
		case 8:
			//st7565r_show_8x16(page, column, (u8 *)&F8X16[c][0]);
		break;
		
		case 12:
			st7565r_show_12x24(page, column, (u8 *)&F12X24[c][0]);
		break;
		
		case 16:
			st7565r_show_16x32(page, column, (u8 *)&F16X32[c][0]);
		break;
		
		case 20:
			//st7565r_show_20x40(page, column, (u8 *)&F20X40[c][0]);
		break;
		
		case 24:
			//st7565r_show_24x48(page, column, (u8 *)&F24X48[c][0]);
		break;
	
		default :
		break;
	}
}

void show_num_string(u8 page, u8 column, char *s, u8 size)
{
	while(*s != 0)
	{
		show_num_char(page, column, *s, size);
		column += size;
		s++;
	}
	
}
void show_array(u8 page, u8 column, u8 *buf, u8 len, u8 size)
{
	while(len != 0)
	{
		switch(size)
		{
			case 8:
				st7565r_show_8x16(page, column, buf);
			break;
			
			case 12:
				st7565r_show_12x24(page, column, buf);
			break;
			
			case 16:
				st7565r_show_16x32(page, column, buf);
			break;
			
			case 20:
				//st7565r_show_20x40(page, column, buf);
			break;
			
			case 24:
				//st7565r_show_24x48(page, column, buf);
			break;
		
			default :
			break;
		}
		buf += size*size/4;
		len--;
		column += size;
	}
	
}



void show_temperature(u16 temperature)
{
	const char temp[][3*12] = 
	{
		0x80,0x60,0x20,0x20,0x20,0xE0,0xE0,0x20,0x20,0x20,0x60,0x80,
		0x01,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x01,
		0x00,0x00,0x00,0x00,0x10,0x1F,0x1F,0x10,0x00,0x00,0x00,0x00,//T0
		0x20,0xE0,0xE0,0x20,0x20,0x20,0x20,0x20,0x20,0x60,0x80,0x00,
		0x00,0xFF,0xFF,0x10,0x10,0x10,0x10,0x7C,0x00,0x00,0x00,0x00,
		0x10,0x1F,0x1F,0x10,0x10,0x10,0x10,0x10,0x10,0x18,0x06,0x00,//E1
		0x20,0xE0,0xE0,0xE0,0x00,0x00,0x00,0x00,0xE0,0xE0,0xE0,0x20,
		0x00,0xFF,0x01,0x3F,0xFE,0xC0,0xE0,0x1E,0x01,0xFF,0xFF,0x00,
		0x10,0x1F,0x10,0x00,0x03,0x1F,0x03,0x00,0x10,0x1F,0x1F,0x10,//M2
		0x20,0xE0,0xE0,0x20,0x20,0x20,0x20,0x20,0x60,0xC0,0x80,0x00,
		0x00,0xFF,0xFF,0x20,0x20,0x20,0x20,0x20,0x30,0x1F,0x0F,0x00,
		0x10,0x1F,0x1F,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//P3
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x0E,0x0E,0x0E,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x1C,0x1C,0x1C,0x00,0x00,0x00,0x00,//:4
	};
	st7565r_clear_area(6,8,1,128);
	show_array(6, 1, (u8 *)temp, 5, 12);
	char str[10];
	sprintf(str, "%d", temperature);
	show_num_string(6, 6*12,str, 12);

}
void show_tpm(u16 tpm)
{
	const char buf[][3*12] = 
	{
		0x80,0x60,0x20,0x20,0x20,0xE0,0xE0,0x20,0x20,0x20,0x60,0x80,
		0x01,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x01,
		0x00,0x00,0x00,0x00,0x10,0x1F,0x1F,0x10,0x00,0x00,0x00,0x00,//T0
		0x20,0xE0,0xE0,0x20,0x20,0x20,0x20,0x20,0x60,0xC0,0x80,0x00,
		0x00,0xFF,0xFF,0x20,0x20,0x20,0x20,0x20,0x30,0x1F,0x0F,0x00,
		0x10,0x1F,0x1F,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//P1
		0x20,0xE0,0xE0,0xE0,0x00,0x00,0x00,0x00,0xE0,0xE0,0xE0,0x20,
		0x00,0xFF,0x01,0x3F,0xFE,0xC0,0xE0,0x1E,0x01,0xFF,0xFF,0x00,
		0x10,0x1F,0x10,0x00,0x03,0x1F,0x03,0x00,0x10,0x1F,0x1F,0x10,//M2
		0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0x30,0x08,0x04,0x00,
		0x00,0x00,0x00,0x00,0x00,0xFE,0xFF,0x01,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0F,0x18,0x20,0x40,0x00,//(3
		0x80,0x60,0x20,0x60,0x80,0x00,0x00,0x00,0xE0,0x20,0x00,0x00,
		0x0F,0x30,0x20,0x30,0x9F,0x70,0xDC,0x37,0x10,0x30,0xC0,0x00,
		0x00,0x00,0x10,0x0E,0x03,0x00,0x07,0x18,0x10,0x18,0x07,0x00,//%4
		0x00,0x04,0x08,0x30,0xE0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x01,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,
		0x00,0x40,0x20,0x18,0x0F,0x03,0x00,0x00,0x00,0x00,0x00,0x00,//)5
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x0E,0x0E,0x0E,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x1C,0x1C,0x1C,0x00,0x00,0x00,0x00,//:6
	};
	st7565r_clear_area(3, 5, 1, 128);
	show_array(3, 1, (u8 *)buf, 7, 12);
	char str[10];
	sprintf(str, "%d", tpm);
	show_num_string(3, 8*12,str, 12);
}

void show_status(u8 battery, u8 flag_temp, u8 flag_tpm)
{
	st7565r_clear_area(1, 2, 1, 128);
	const char buf[][32*2] = 
	{
		0x00,0x00,0xF0,0xFC,0xFC,0x0C,0x0C,0x0C,0xFC,0xFC,0xFC,0xFC,
		0x0C,0x0C,0x0C,0xFC,0xFC,0xFC,0xFC,0x0C,0x0C,0x0C,0xFC,0xFC,
		0xFC,0xFC,0x0C,0x0C,0xFC,0xFC,0x00,0x00,0x00,0x00,0x0F,0x3F,
		0x3F,0x30,0x30,0x30,0x3F,0x3F,0x3F,0x3F,0x30,0x30,0x30,0x3F,
		0x3F,0x3F,0x3F,0x30,0x30,0x30,0x3F,0x3F,0x3F,0x3F,0x30,0x30,
		0x3F,0x3F,0x00,0x00,

		0x00,0x00,0xF0,0xFC,0xFC,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,
		0x0C,0x0C,0x0C,0xFC,0xFC,0xFC,0xFC,0x0C,0x0C,0x0C,0xFC,0xFC,
		0xFC,0xFC,0x0C,0x0C,0xFC,0xFC,0x00,0x00,0x00,0x00,0x0F,0x3F,
		0x3F,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x3F,
		0x3F,0x3F,0x3F,0x30,0x30,0x30,0x3F,0x3F,0x3F,0x3F,0x30,0x30,
		0x3F,0x3F,0x00,0x00,

		0x00,0x00,0xF0,0xFC,0xFC,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,
		0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0xFC,0xFC,
		0xFC,0xFC,0x0C,0x0C,0xFC,0xFC,0x00,0x00,0x00,0x00,0x0F,0x3F,
		0x3F,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
		0x30,0x30,0x30,0x30,0x30,0x30,0x3F,0x3F,0x3F,0x3F,0x30,0x30,
		0x3F,0x3F,0x00,0x00,
				
		0x00,0x00,0xF0,0xFC,0xFC,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,
		0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,
		0x0C,0x0C,0x0C,0x0C,0xFC,0xFC,0x00,0x00,0x00,0x00,0x0F,0x3F,
		0x3F,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
		0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
		0x3F,0x3F,0x00,0x00,
	};
	int value = battery/20;
	if(value > 4) value = 4;
	value = 4 - value;	
	st7565r_show_32x12(1,90,(u8 *)buf[value]);
	const char temp[] = 
	{
		0x00,0x00,0x00,0xF8,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x11,
		0x1B,0x00,0x00,0x00,//!9
		0x00,0xF8,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0x1F,0x00,0x00,
		0x00,0x00,0x1F,0x00,//h0
		0x00,0x40,0x40,0x58,0xD8,0x00,0x00,0x00,0x00,0x10,0x10,0x10,
		0x1F,0x10,0x10,0x00,//i1
		0x00,0x80,0xC0,0x40,0x40,0xC0,0xC0,0x40,0x00,0x6F,0x92,0x94,
		0x94,0x92,0x73,0x20,//g2
		0x00,0xF8,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0x1F,0x00,0x00,
		0x00,0x00,0x1F,0x00,//h3
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,// 4
		0x40,0x40,0x40,0xF0,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0x1F,
		0x10,0x10,0x10,0x00,//t5
		0x00,0x80,0xC0,0x40,0x40,0x40,0x80,0x00,0x00,0x0F,0x1A,0x12,
		0x12,0x12,0x13,0x00,//e6
		0x00,0xC0,0x40,0x40,0x80,0x40,0xC0,0x80,0x00,0x1F,0x00,0x00,
		0x1F,0x00,0x1F,0x1F,//m7
		0x00,0xC0,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0xFF,0x10,0x10,
		0x10,0x10,0x0F,0x00,//p8
		0x00,0x00,0x00,0xF8,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x11,
		0x1B,0x00,0x00,0x00,//!9
	};
	if(flag_temp != 0 ) show_array(1,1,(u8 *)temp, 11, 8);


	const char tpm[] = 
	{
		0x00,0x00,0x00,0xF8,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x11,
		0x1B,0x00,0x00,0x00,//!0
		0x00,0xF8,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0x1F,0x00,0x00,
		0x00,0x00,0x1F,0x00,//h1
		0x00,0x40,0x40,0x58,0xD8,0x00,0x00,0x00,0x00,0x10,0x10,0x10,
		0x1F,0x10,0x10,0x00,//i2
		0x00,0x80,0xC0,0x40,0x40,0xC0,0xC0,0x40,0x00,0x6F,0x92,0x94,
		0x94,0x92,0x73,0x20,//g3
		0x00,0xF8,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0x1F,0x00,0x00,
		0x00,0x00,0x1F,0x00,//h4
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,// 5
		0x40,0x40,0x40,0xF0,0x40,0x40,0x40,0x00,0x00,0x00,0x00,0x1F,
		0x10,0x10,0x10,0x00,//t6
		0x00,0xC0,0x80,0x40,0x40,0x40,0x80,0x00,0x00,0xFF,0x10,0x10,
		0x10,0x10,0x0F,0x00,//p7
		0x00,0xC0,0x40,0x40,0x80,0x40,0xC0,0x80,0x00,0x1F,0x00,0x00,
		0x1F,0x00,0x1F,0x1F,//m8
		0x00,0x00,0x00,0xF8,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x11,
		0x1B,0x00,0x00,0x00,//!9
	};
	if(flag_tpm != 0 ) show_array(1,1,(u8 *)tpm, 10, 8);


}

	