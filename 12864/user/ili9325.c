/*
 * ili9325.c
 *
 * Created: 2015/10/10 0:20:50
 *  Author: God
 */ 

#include "ili9325.h"
void ili9325_gpio_init(void)
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
void ili9325_init(void)	//初始化
{
	ili9325_gpio_init();
	CS_RESET;  //打开片选使能
	delay_us(50000);                     //根据不同晶振速度可以调整延时，保障稳定显示
	ili9325_write_reg(0x0001,0x0100);
	ili9325_write_reg(0x0002,0x0700);
	ili9325_write_reg(0x0003,0x0030);
	ili9325_write_reg(0x0004,0x0000);
	ili9325_write_reg(0x0008,0x0207);
	ili9325_write_reg(0x0009,0x0000);
	ili9325_write_reg(0x000A,0x0000);
	ili9325_write_reg(0x000C,0x0000);
	ili9325_write_reg(0x000D,0x0000);
	ili9325_write_reg(0x000F,0x0000);
	//power on sequence VGHVGL
	ili9325_write_reg(0x0010,0x0000);
	ili9325_write_reg(0x0011,0x0007);
	ili9325_write_reg(0x0012,0x0000);
	ili9325_write_reg(0x0013,0x0000);
	//vgh
	ili9325_write_reg(0x0010,0x1290);
	ili9325_write_reg(0x0011,0x0227);
	//delayms(100);
	//vregiout
	ili9325_write_reg(0x0012,0x001d); //0x001b
	//delayms(100);
	//vom amplitude
	ili9325_write_reg(0x0013,0x1500);
	//delayms(100);
	//vom H
	ili9325_write_reg(0x0029,0x0018);
	ili9325_write_reg(0x002B,0x000D);

	//gamma
	ili9325_write_reg(0x0030,0x0004);
	ili9325_write_reg(0x0031,0x0307);
	ili9325_write_reg(0x0032,0x0002);// 0006
	ili9325_write_reg(0x0035,0x0206);
	ili9325_write_reg(0x0036,0x0408);
	ili9325_write_reg(0x0037,0x0507);
	ili9325_write_reg(0x0038,0x0204);//0200
	ili9325_write_reg(0x0039,0x0707);
	ili9325_write_reg(0x003C,0x0405);// 0504
	ili9325_write_reg(0x003D,0x0F02);
	//ram
	ili9325_write_reg(0x0050,0x0000);
	ili9325_write_reg(0x0051,0x00EF);
	ili9325_write_reg(0x0052,0x0000);
	ili9325_write_reg(0x0053,0x013F);
	ili9325_write_reg(0x0060,0xA700);
	ili9325_write_reg(0x0061,0x0001);
	ili9325_write_reg(0x006A,0x0000);
	//
	ili9325_write_reg(0x0080,0x0000);
	ili9325_write_reg(0x0081,0x0000);
	ili9325_write_reg(0x0082,0x0000);
	ili9325_write_reg(0x0083,0x0000);
	ili9325_write_reg(0x0084,0x0000);
	ili9325_write_reg(0x0085,0x0000);
	//
	ili9325_write_reg(0x0090,0x0010);
	ili9325_write_reg(0x0092,0x0600);
	ili9325_write_reg(0x0093,0x0003);
	ili9325_write_reg(0x0095,0x0110);
	ili9325_write_reg(0x0097,0x0000);
	ili9325_write_reg(0x0098,0x0000);
	ili9325_write_reg(0x0007,0x0133);
}
void ili9325_write_bus(u16 bus) //并行数据写入函数
{
	#ifdef ILI9325_16BIT
	SEND_BYTE(bus);
	RW_RESET;
	RW_SET;
	#endif
	
	#ifdef ILI9325_8BIT
	SEND_BYTE(bus>>8);
	RW_RESET;
	RW_SET;
	SEND_BYTE(bus);
	RW_RESET;
	RW_SET;
	#endif
}
u16 ili9325_read_bus(void)//并行数据读入函数
{
	#ifdef ILI9325_16BIT
	u16 date;
	BYTE_IN;  //设置数据口为输入
	RD_RESET;
	READ_BYTE(date);
	RD_SET;
	BYTE_OUT;
	return date;
	#endif
	
	#ifdef ILI9325_8BIT
	u16 date;
	u8 temp;
	BYTE_IN;  //设置数据口为输入
	
	RD_RESET;
	READ_BYTE(temp);
	date=temp;
	RD_SET;
	
	RD_RESET;
	date<<=8;
	READ_BYTE(temp);
	date |=temp;
	RD_SET;
	
	BYTE_OUT;
	return date;
	#endif
}
void ili9325_write_com(u16 com)	 //发送命令
{
	RS_RESET;
		#ifdef ILI9325_16BIT
		SEND_BYTE(com);
		RW_RESET;
		RW_SET;
		#endif
		
		#ifdef ILI9325_8BIT
		SEND_BYTE(com>>8);
		RW_RESET;
		RW_SET;
		SEND_BYTE(com);
		RW_RESET;
		RW_SET;
		#endif
	RS_SET;
}
void ili9325_write_date(u16 date)	//发送数据
{
	RS_SET;
	
	#ifdef ILI9325_16BIT
	SEND_BYTE(date);
	RW_RESET;
	RW_SET;
	#endif
	
	#ifdef ILI9325_8BIT
	SEND_BYTE(date>>8);
	RW_RESET;
	RW_SET;
	SEND_BYTE(date);
	RW_RESET;
	RW_SET;
	#endif
}
u16 ili9325_read_reg(u16 reg)//读寄存器
{
	u16 date;
	ili9325_write_com(reg); //写地址
	date=ili9325_read_bus();//读数据
	return date;
}
void ili9325_write_reg(u16 com,u16 date)//向寄存器写入指令
{
	ili9325_write_com(com);
	ili9325_write_date(date);
}
u8 ili9325_set_window(u16 x1,u16 y1,u16 x2,u16 y2)////设定窗口
{
	if ((x2>X_MAX)||(y2>Y_MAX))
	{
		return 0;
	}
	if ((x1>x2)||(y1>y2))
	{
		return 0;
	}
	ili9325_write_reg(0x20,x1-1);	 //设置X坐标位置
	ili9325_write_reg(0x21,y1-1);//设置Y坐标位置
	ili9325_write_reg(0x50,x1-1);	 //开始X
	ili9325_write_reg(0x52,y1-1);	  //开始Y
	ili9325_write_reg(0x51,x2-1);	//结束X
	ili9325_write_reg(0x53,y2-1);	//结束Y
	ili9325_write_com(0x22);
	return 1;
}
u8 ili9325_set_point(u16 x,u16 y)
{
	if ((x>X_MAX)||(y>Y_MAX))	
	{
		return 0;
	}
	ili9325_write_reg(0x0020,x-1);
	ili9325_write_reg(0x0021,y-1);
	ili9325_write_com(0x22);
	return 1;
}


	u8 ili9325_draw_point(u16 x,u16 y,const u8 *color)
	{
		if(!ili9325_set_point(x,y)) return 0;
		ili9325_write_gram(color);
		return 1;
	}
	void ili9325_write_gram(const u8 *color)//写GRAM
	{

	#ifdef  ILI9325_8BIT
		SEND_BYTE((*color&0xf8)|(*(color+1)>>5));
		RW_RESET;
		RW_SET;
		SEND_BYTE(((*(color+1)<<3)&0xe0)|(*(color+2)>>3));
		RW_RESET;
		RW_SET;
	#endif

	#ifdef  ILI9325_16BIT
		u16 color565,temp;
	
		temp=*color&0xf8;
		color565=temp<<8;
	
		temp=*(color+1)&0xfc;
		color565|=temp<<3;
	
		color565|=(*(color+2)&0xf8)>>3;
		SEND_BYTE(color565);
		RW_RESET;
		RW_SET;
	#endif
	}
	u8 ili9325_read_point(u16 x,u16 y,u8 *color)
	{
		u16 temp;
		if (!ili9325_set_point(x,y))	return 0;
		ili9325_read_reg(0x22);
		temp=ili9325_read_reg(0x22);
		*color=(temp&0xf800)>>8;
		*(color+1)=(temp&0x07e0)>>3;
		*(color+2)=(temp&0x001f)<<3;
		return 1;
	}
	void ili9325_refresh(const u8 *color)//设定屏幕颜色
	{
		ili9325_draw_window(1,1,240,320,color);
	}
	u8 ili9325_draw_window(u16 x1,u16 y1,u16 x2,u16 y2,const u8 *color)//填充矩形
	{	
		u32 num;
		if(!ili9325_set_window(x1,y1,x2,y2))
		{
			return 0;
		}
		for (num=(x2-x1+1)*(y2-y1+1);num>0;num--)
		{
			ili9325_write_gram(color);
		}
		ili9325_set_window(1,1,240,320);
		return 1;
	}
	u8 ili9325_draw_line(u16 x1,u16 y1,u16 x2,u16 y2,const u8 *color)//画线
	{
		s16 dx,dy;
		s16 f;
		if ((x1>X_MAX)||(y1>Y_MAX)||(x2>X_MAX)||(y2>Y_MAX))
		{
			return 0;
		}
		dx=x2-x1;
		dy=y2-y1;
		if (dx==0)
		{	
			if (dy>=0)
			{
				for(;y1<=y2;y1++)
				{
					ili9325_draw_point(x1,y1,color);
				}
			} 
			else
			{
				for(;y2<=y1;y2++)
				{
					ili9325_draw_point(x1,y2,color);
				}
			}
			return 1;
		}
	
		if (dy==0)
		{
			if (dx>=0)
			{
				for(;x1<=x2;x1++)
				{
					ili9325_draw_point(x1,y1,color);
				}
			}
			else
			{
				for(;x2<=x1;x2++)
				{
					ili9325_draw_point(x2,y1,color);
				}
			}
			return 1;
		}
		ili9325_draw_point(x1,y1,color);
		f=0;
		if ((dx>0)&&(dy>0))
		{
			while(!((x1==x2)&&(y1==y2)))
			{
				if (f>=0)
				{
					x1++;
					f-=dy;
				}
				else 
				{
					if (f<0)
					{
						y1++;
						f+=dx;
					}
				}
				ili9325_draw_point(x1,y1,color);
			}
		}
		if ((dx>0)&&(dy<0))
		{
			while(!((x1==x2)&&(y1==y2)))
			{
				if (f>=0)
				{
					x1++;
					f+=dy;
				}
				else
				{
					if (f<0)
					{
						y1--;
						f+=dx;
					}
				}
				ili9325_draw_point(x1,y1,color);
			}
		}	
		if ((dx<0)&&(dy>0))
		{
			while(!((x1==x2)&&(y1==y2)))
			{
				if (f>=0)
				{
					x1--;
					f-=dy;
				}
				else
				{
					if (f<0)
					{
						y1++;
						f-=dx;
					}
				}
				ili9325_draw_point(x1,y1,color);
			}
		}	
		if ((dx<0)&&(dy<0))
		{
			while(!((x1==x2)&&(y1==y2)))
			{
				if (f>=0)
				{
					x1--;
					f+=dy;
				}
				else
				{
					if (f<0)
					{
						y1--;
						f-=dx;
					}
				}
				ili9325_draw_point(x1,y1,color);
			}
		}	
		return 1;
	}
	u16 ili9325_fill_line(u16 x,u16 y,u16 num,const u8 *color)
	{
		u16 n;
		const u8 *temp;
		temp=color;
		if(!ili9325_set_point(x,y)) return 0;
		n=X_MAX+1-x;
		if (num>n) num=n;
		for (n=0;n<num;n++)
		{
			ili9325_write_gram(temp);
			temp+=3;
		}
		return num;
	}
	u16 ili9325_fill_window(u16 x,u16 y,u16 width,u16 num,const u8 *color )
	{
		u16 n;
		const u8 *temp;
		temp=color;
		if(!ili9325_set_window(x,y,x+width-1,Y_MAX)) return 0;
		n=width*(Y_MAX-y+1);
		if(num>n) num=n;
		for (n=0;n<num;n++)
		{
			ili9325_write_gram(temp);
			temp+=3;
		}
		ili9325_set_window(1,1,240,320);
		return num;
	}



	u8 ili9325_draw_point565(u16 x,u16 y,const u16 color)
	{
		if (!(ili9325_set_point(x,y)))
		{
			return 0;
		}
		ili9325_write_gram565(color);
		return 1;
	}
	void ili9325_write_gram565(const u16 color)
	{
		#ifdef ILI9325_8BIT
			SEND_BYTE(color>>8);
			RW_RESET;
			RW_SET;
			SEND_BYTE(color);
			RW_RESET;
			RW_SET;
		#endif

		#ifdef ILI9325_16BIT
			SEND_BYTE(color);
			RW_RESET;
			RW_SET;
		#endif
	}
	u8 ili9325_read_point565(u16 x,u16 y,u16 *color)
	{
		if (!ili9325_set_point(x,y))	return 0;
		ili9325_read_reg(0x22);
		*color=ili9325_read_reg(0x22);
		return 1;
	}
	void ili9325_refresh565(const u16 color)//设定屏幕颜色
	{
		ili9325_draw_window565(1,1,240,320,color);
	}
	u8 ili9325_draw_window565(u16 x1,u16 y1,u16 x2,u16 y2,const u16 color)//填充矩形
	{
		u32 num;
		if(!ili9325_set_window(x1,y1,x2,y2))
		{
			return 0;
		}
		for (num=(x2-x1+1)*(y2-y1+1);num>0;num--)
		{
			ili9325_write_gram565(color);
		}
		ili9325_set_window(1,1,240,320);
		return 1;
	}
	u8 ili9325_draw_line565(u16 x1,u16 y1,u16 x2,u16 y2,const u16 color)//画线
	{
		s16 dx,dy;
		s16 f;
		if ((x1>X_MAX)||(y1>Y_MAX)||(x2>X_MAX)||(y2>Y_MAX))
		{
			return 0;
		}
		dx=x2-x1;
		dy=y2-y1;
		if (dx==0)
		{
			if (dy>=0)
			{
				for(;y1<=y2;y1++)
				{
					ili9325_draw_point565(x1,y1,color);
				}
			}
			else
			{
				for(;y2<=y1;y2++)
				{
					ili9325_draw_point565(x1,y2,color);
				}
			}
			return 1;
		}
	
		if (dy==0)
		{
			if (dx>=0)
			{
				for(;x1<=x2;x1++)
				{
					ili9325_draw_point565(x1,y1,color);
				}
			}
			else
			{
				for(;x2<=x1;x2++)
				{
					ili9325_draw_point565(x2,y1,color);
				}
			}
			return 1;
		}
		ili9325_draw_point565(x1,y1,color);
		f=0;
		if ((dx>0)&&(dy>0))
		{
			while(!((x1==x2)&&(y1==y2)))
			{
				if (f>=0)
				{
					x1++;
					f-=dy;
				}
				else
				{
					if (f<0)
					{
						y1++;
						f+=dx;
					}
				}
				ili9325_draw_point565(x1,y1,color);
			}
		}
		if ((dx>0)&&(dy<0))
		{
			while(!((x1==x2)&&(y1==y2)))
			{
				if (f>=0)
				{
					x1++;
					f+=dy;
				}
				else
				{
					if (f<0)
					{
						y1--;
						f+=dx;
					}
				}
				ili9325_draw_point565(x1,y1,color);
			}
		}
		if ((dx<0)&&(dy>0))
		{
			while(!((x1==x2)&&(y1==y2)))
			{
				if (f>=0)
				{
					x1--;
					f-=dy;
				}
				else
				{
					if (f<0)
					{
						y1++;
						f-=dx;
					}
				}
				ili9325_draw_point565(x1,y1,color);
			}
		}
		if ((dx<0)&&(dy<0))
		{
			while(!((x1==x2)&&(y1==y2)))
			{
				if (f>=0)
				{
					x1--;
					f+=dy;
				}
				else
				{
					if (f<0)
					{
						y1--;
						f-=dx;
					}
				}
				ili9325_draw_point565(x1,y1,color);
			}
		}
		return 1;
	}
	u16 ili9325_fill_line565(u16 x,u16 y,u16 num,const u16 *color)
	{
		u16 n;
		const u16 *temp;
		temp=color;
		if(!ili9325_set_point(x,y)) return 0;
		n=X_MAX+1-x;
		if (num>n) num=n;
		
		for (n=0;n<num;n++)
		{
			ili9325_write_gram565(*temp);
			temp++;
		}
		return num;
	}
	u16 ili9325_fill_window565(u16 x,u16 y,u16 width,u16 num,const u16 *color )
	{
		u16 n;
		const u16 *temp;
		temp=color;
		if(!ili9325_set_window(x,y,x+width-1,Y_MAX)) return 0;
		n=width*(Y_MAX-y+1);
		if(num>n) num=n;
		for (n=0;n<num;n++)
		{
			ili9325_write_gram565(*temp);
			temp++;
		}
		ili9325_set_window(1,1,240,320);
		return num;
	}


#ifdef ASCII_FONT
	#include "ASCII_FONT.H"
	u8	ili9325_show_char(u16 x,u16 y,u8 num,u8 size,const u8 *color,u8 mode)
	{
	    u8 temp,t1,t;
		const u8 black[3]={0,0,0};
	    u16 y0=y;
	    u8 csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数
	    num=num-' ';//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	    for(t=0;t<csize;t++)
	    {
		    if(size==12)temp=asc2_1206[num][t]; 	 	//调用1206字体
		    else if(size==16)temp=asc2_1608[num][t];	//调用1608字体
		    //else if(size==24)temp=asc2_2412[num][t];	//调用2412字体
		    else return 0;								//没有的字库
		    for(t1=0;t1<8;t1++)
		    {

			    if(temp&0x80)	
					{
						if(!ili9325_draw_point(x,y,color)) return 0;
					}
			    else 
					if(mode==0)	
					{
						if(!ili9325_draw_point(x,y,black)) return 0;
					}
			    temp<<=1;
			    y++;
					if((y-y0)==size)
					{
						y=y0;
						x++;
						break;
					}
		    }
	    }
		return 1;	
	}
	u8 ili9325_show_string(u16 x,u16 y,const u8 *string,u8 size,const u8 *color,u8 mode)
	{	
		while (*string!=0)
		{
			if(!ili9325_show_char(x,y,*string,size,color,mode)) return 0;
			string++;
			x+=size/2;
		}
		return 1;
	}
#endif

