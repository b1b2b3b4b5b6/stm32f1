
#ifndef SH1106_H
#define SH1106_H			  	 

#include "i2c.h"

#define  SLAVE 0x78		

#define sh1106_write_data(data) i2c_write_reg(SLAVE, 0x40, data)
#define sh1106_write_cmd(cmd) i2c_write_reg(SLAVE, 0x00, cmd)


//OLED¿ØÖÆÓÃº¯Êý
void sh1106_display_on(void);
void sh1106_display_off(void);	   							   		    
void sh1106_init(void);
void sh1106_clear(void);
void sh1106_set_addr(u8 x, u8 y);
void sh1106_draw_byte(u8 x, u8 y, u8 value);
void sh1106_draw_bytes(u8 x, u8 y, u8 *buf, u8 len);
void sh1106_draw_frame(u8 *buf);
void sh1106_show_char(u8 x, u8 y, u8 c, u8 size);
void sh1106_show_string(u8 x, u8 y, char *str, u8 size);

#endif  	

