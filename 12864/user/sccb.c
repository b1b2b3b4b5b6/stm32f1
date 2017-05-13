
#include "sccb.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序参考自网友guanfu_wang代码。
//ALIENTEK战舰STM32开发板V3
//SCCB 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/1/18
//版本：V1.0		    							    							  
//////////////////////////////////////////////////////////////////////////////////
 
//初始化SCCB接口
//CHECK OK
void sccb_init(void)
{		
	SCCB_SCL_OUT;
	SCCB_SCL_RESET;	
	SCCB_SDA_OUT;
	SCCB_SDA_SET;
	sccb_stop();
}			 

//SCCB起始信号
//当时钟为高的时候,数据线的高到低,为SCCB起始信号
//在激活状态下,SDA和SCL均为低电平
void sccb_start(void)
{
   SCCB_SDA_SET;     //数据线高电平	   
   SCCB_SCL_SET;	    //在时钟线高的时候数据线由高至低
    DELAY50US;  
   SCCB_SDA_RESET;
    DELAY50US;	 
   SCCB_SCL_RESET;	    //数据线恢复低电平，单操作函数必要	  
}

//SCCB停止信号
//当时钟为高的时候,数据线的低到高,为SCCB停止信号
//空闲状况下,SDA,SCL均为高电平
void sccb_stop(void)
{
   SCCB_SDA_RESET;
    DELAY50US;	 
   SCCB_SCL_SET;	
    DELAY50US; 
   SCCB_SDA_SET;	
    DELAY50US;
}  
//产生NA信号
void sccb_no_ack(void)
{
	DELAY50US;
	SCCB_SDA_SET;	
	SCCB_SCL_SET;	
	DELAY50US;
	SCCB_SCL_RESET;	
	DELAY50US;
	SCCB_SDA_RESET;	
	DELAY50US;
}
//SCCB,写入一个字节
//返回值:0,成功;1,失败. 
u8 sccb_write_byte(u8 dat)
{
	u8 j,res;	 
	for(j=0;j<8;j++) //循环8次发送数据
	{
		if(dat&0x80)SCCB_SDA_SET;	
		else
		SCCB_SDA_RESET;
		dat<<=1;
		DELAY50US;
		SCCB_SCL_SET;	
		DELAY50US;
		SCCB_SCL_RESET;		   
	}			 
	SCCB_SDA_IN;		//设置SDA为输入 
	DELAY50US;
	SCCB_SCL_SET;			//接收第九位,以判断是否发送成功
	DELAY50US;
	if(SCCB_SDA_R) res=0;  //SDA=1，返回1
	else res=1;         //SDA=0发送成功，返回0
	SCCB_SCL_RESET;		 
	SCCB_SDA_OUT;		//设置SDA为输出    
	return res;  
}	 
//SCCB 读取一个字节
//在SCL的上升沿,数据锁存
//返回值:读到的数据
u8 sccb_read_byte(void)
{
	u8 temp=0,j;    
	SCCB_SDA_IN;		//设置SDA为输入  
	for(j=8;j>0;j--) 	//循环8次接收数据
	{		     	  
		DELAY50US;
		SCCB_SCL_SET;
		temp=temp<<1;
		if(SCCB_SDA_R)temp++;   
		DELAY50US;
		SCCB_SCL_RESET;
	}	
	SCCB_SDA_OUT;		//设置SDA为输出    
	return temp;
} 							    
//写寄存器
//返回值:0,成功;1,失败.
u8 sccb_write_reg(u8 reg,u8 data)
{
	sccb_start(); 					//启动SCCB传输
	if(!sccb_write_byte(SCCB_ID))return 0;	//写器件ID	  
	DELAY100US;
  	if(!sccb_write_byte(reg))return 0;		//写寄存器地址	  
	DELAY100US;
  	if(!sccb_write_byte(data))return 0; 	//写数据	 
  	sccb_stop();	  
  	return	1;
}		  					    
//读寄存器
//返回值:读到的寄存器值
u8 sccb_read_reg(u8 reg)
{
	u8 val=0;
	sccb_start(); 				//启动SCCB传输
	sccb_write_byte(SCCB_ID);		//写器件ID	  
	DELAY100US;	 
  	sccb_write_byte(reg);			//写寄存器地址	  
	DELAY100US;	  
	sccb_stop();   
	DELAY100US;	   
	//设置寄存器地址后，才是读
	sccb_start();
	sccb_write_byte(SCCB_ID|0X01);	//发送读命令	  
	DELAY100US;
  	val=sccb_read_byte();		 	//读取数据
  	sccb_no_ack();
  	sccb_stop();
  	return val;
}















