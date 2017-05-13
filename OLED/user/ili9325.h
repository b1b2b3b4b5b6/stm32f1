/*
 * ili9325.h
 *
 * Created: 2015/10/10 0:21:04
 *  Author: God
 */ 


#ifndef ILI9325_H_
#define ILI9325_H_

#define ASCII_FONT

#define X_MAX 240
#define Y_MAX 320

#include "init.h"
//#define  ILI9325_8BIT
#define  ILI9325_16BIT


#define		ILI9325_PIN_DATE	GPIOB

#define		ILI9325_PIN_CTR		GPIOA

#define		ILI9325_PIN_RST		GPIO_Pin_12
#define		ILI9325_PIN_CS		
#define		ILI9325_PIN_RD		GPIO_Pin_10
#define		ILI9325_PIN_RW		GPIO_Pin_9
#define		ILI9325_PIN_RS		GPIO_Pin_11


/*
#if	_ILI9325_PIN_DATE == _ILI9325_PIN_CTR
#ifdef ILI9325_16BIT
#error gpio conflict!
#endif
#endif*/

#define RST_OUT	gpio_init_pin(ILI9325_PIN_CTR,ILI9325_PIN_RST,GPIO_Mode_Out_PP)
#define RST_SET		GPIO_SetBits(ILI9325_PIN_CTR,ILI9325_PIN_RST)
#define RST_RESET	GPIO_ResetBits(ILI9325_PIN_CTR,ILI9325_PIN_RST)

#define CS_OUT		//gpio_init_pin(ILI9325_PIN_CTR,ILI9325_PIN_CS,GPIO_Mode_Out_PP)
#define CS_SET		//GPIO_SetBits(ILI9325_PIN_CTR,ILI9325_PIN_CS)
#define CS_RESET	//GPIO_ResetBits(ILI9325_PIN_CTR,ILI9325_PIN_CS)


#define RD_OUT		gpio_init_pin(ILI9325_PIN_CTR,ILI9325_PIN_RD,GPIO_Mode_Out_PP)
#define RD_SET		GPIO_SetBits(ILI9325_PIN_CTR,ILI9325_PIN_RD)
#define RD_RESET	GPIO_ResetBits(ILI9325_PIN_CTR,ILI9325_PIN_RD)

#define RW_OUT	gpio_init_pin(ILI9325_PIN_CTR,ILI9325_PIN_RW,GPIO_Mode_Out_PP)
#define RW_SET		GPIO_SetBits(ILI9325_PIN_CTR,ILI9325_PIN_RW)
#define RW_RESET	GPIO_ResetBits(ILI9325_PIN_CTR,ILI9325_PIN_RW)

#define RS_OUT		gpio_init_pin(ILI9325_PIN_CTR,ILI9325_PIN_RS,GPIO_Mode_Out_PP)
#define RS_SET		GPIO_SetBits(ILI9325_PIN_CTR,ILI9325_PIN_RS)
#define RS_RESET	GPIO_ResetBits(ILI9325_PIN_CTR,ILI9325_PIN_RS)


#ifdef ILI9325_8BIT
	#define BYTE_OUT		gpio_init_pin(ILI9325_PIN_DATE,0x00ff,GPIO_Mode_Out_PP)
	#define BYTE_IN			gpio_init_pin(ILI9325_PIN_DATE,0x00ff,GPIO_Mode_IPU)
	#define READ_BYTE(BYTE)		BYTE=(ILI9325_PIN_DATE->IDR)&0x00000ff
	#define SEND_BYTE(BYTE)		ILI9325_PIN_DATE->ODR=(ILI9325_PIN_DATE->ODR&0xffffff00)|(u8)(BYTE)
#endif

#ifdef ILI9325_16BIT
	#define BYTE_OUT		gpio_init_pin(ILI9325_PIN_DATE,0xffff,GPIO_Mode_Out_PP)
	#define BYTE_IN			gpio_init_pin(ILI9325_PIN_DATE,0xffff,GPIO_Mode_IPU)
	#define SEND_BYTE(BYTE)		ILI9325_PIN_DATE->ODR=(u16)BYTE
	#define READ_BYTE(BYTE)		BYTE=ILI9325_PIN_DATE->IDR
#endif

void ili9325_gpio_init(void);
void ili9325_init(void);
void ili9325_write_bus(u16 bus);		//并行数据写入函数
u16 ili9325_read_bus(void);		//并行读数据
void ili9325_write_com(u16 com);		 //发送命令
void ili9325_write_date(u16 date);		//发送数据
void ili9325_write_reg(u16 com,u16 date);	//向寄存器写入指令
u16 ili9325_read_reg(u16 reg);	//读寄存器
void ili9325_write_gram(const u8 *color);	//写入GRAM
u8 ili9325_read_point(u16 x,u16 y,u8 *color);
u8 ili9325_set_point(u16 x,u16 y);	//设置一个点
u8 ili9325_draw_point(u16 x,u16 y,const u8 *color);	//画一个点
u8 ili9325_set_window(u16 x1,u16 y1,u16 x2,u16 y2);//设定窗口
void ili9325_refresh(const u8 *color);//刷屏
u8 ili9325_draw_window(u16 x1,u16 y1,u16 x2,u16 y2,const u8 *color);//填充矩形
u8 ili9325_draw_line(u16 x1,u16 y1,u16 x2,u16 y2,const u8 *color);//画线
u16 ili9325_fill_line(u16 x,u16 y,u16 num,const u8 *color  );
u16 ili9325_fill_window(u16 x,u16 y,u16 width,u16 num,const u8 *color  );


	void ili9325_write_gram565(const u16 color);
	u8 ili9325_draw_point565(u16 x,u16 y,u16 color);
	u8 ili9325_read_point565(u16 x,u16 y,u16 *color);
	void ili9325_refresh565(const u16 color);
	u8 ili9325_draw_window565(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);//填充矩形
	u8 ili9325_draw_line565(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);
	u16 ili9325_fill_line565(u16 x,u16 y,u16 num,const u16 *color);	
	u16 ili9325_fill_window565(u16 x,u16 y,u16 width,u16 num,const u16 *color );

	
#ifdef ASCII_FONT

	u8 ili9325_show_char(u16 x,u16 y,u8 num,u8 size,const u8 *color,u8 mode);
	u8 ili9325_show_string(u16 x,u16 y,const u8 *string,u8 size,const u8 *color,u8 mode);
#endif
#endif /* ILI9325_H_ */
