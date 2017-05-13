/*
 * init.c
 *
 * Created: 2015/10/6 17:07:32
 *  Author: God
 */ 

#include "init.h"
#define SYSTICK_CLOCK 4
void clock_init(void)
{
	RCC_DeInit();		//时钟初始化

	//RCC_HSEConfig(RCC_HSE_ON);		//开HSE，8MHZ
	//while(!RCC_WaitForHSEStartUp());		//等待HSE稳定
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_8);		//PLL9倍频，72MHZ
	RCC_PLLCmd(ENABLE);		//开PLL
	while(RCC_GetITStatus(RCC_FLAG_PLLRDY)!=RESET);		//等待PLL就绪
	
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);		//选择PLL为系统时钟
	/*
	RCC_HCLKConfig(RCC_SYSCLK_Div1);				//AHB不分频
	RCC_PCLK1Config(RCC_HCLK_Div2);		//APB1二分频 36MHZ
	RCC_PCLK2Config(RCC_HCLK_Div1);		//APB2不分频 72MHz
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//滴答选择外部时钟  HCLK/8=9
	*/
	RCC_HCLKConfig(RCC_SYSCLK_Div8);	
	RCC_PCLK1Config(RCC_HCLK_Div1);		//APB1
	RCC_PCLK2Config(RCC_HCLK_Div1);		//APB2
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);	//滴答选择外部时钟  HCLK
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//开启端口重映射
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);		//只开启SW调试io口，A13，A14	
	//GPIO_PinRemapConfig(GPIO_Remap_PD01,ENABLE);	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	 //开启GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	 //开启GPIOB时钟
	gpio_init_pin(GPIOA,GPIO_Pin_All,GPIO_Mode_AIN);
	gpio_init_pin(GPIOB,GPIO_Pin_All,GPIO_Mode_AIN);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//开启USART1
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);	//开启SPI
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		//设置中断优先组
	EXTI_DeInit();//中断初始化
	 
}

void delay_us(u32 nus)
{
	u32 temp;
	SysTick->LOAD=nus*SYSTICK_CLOCK; 					//时间加载
	SysTick->VAL=0x00;        					//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;      					 //清空计数器
}
void delay_ms(u32 nms)
{
	for(;nms>0;nms--)
	{
		delay_us(1000);
	}
}
void gpio_init_pin(GPIO_TypeDef* GPIOx, u16 GPIO_Pin,GPIOMode_TypeDef MODE)
{
	GPIO_InitTypeDef io;
	io.GPIO_Mode = MODE;
	io.GPIO_Pin=GPIO_Pin;
	io.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOx,&io);
}

void int_to_uchar(int *in,uchar *out,uchar n)
{
	uchar i;
	for (i=0;i<n;i++)
	{
		*out=*in>>8;
		out++;
		*out=*in;
		in++;
		out++;
	}
}

void uchar_to_int(uchar *in,int *out,uchar n)
{
	uchar i;
	for (i=0;i<n;i++)
	{
		*out=*in;
		*out<<=8;
		in++;
		*out|=*in;
		out++;
		in++;
	}
}
