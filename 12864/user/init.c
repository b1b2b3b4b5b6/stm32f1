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
	RCC_DeInit();		//ʱ�ӳ�ʼ��

	//RCC_HSEConfig(RCC_HSE_ON);		//��HSE��8MHZ
	//while(!RCC_WaitForHSEStartUp());		//�ȴ�HSE�ȶ�
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_8);		//PLL9��Ƶ��72MHZ
	RCC_PLLCmd(ENABLE);		//��PLL
	while(RCC_GetITStatus(RCC_FLAG_PLLRDY)!=RESET);		//�ȴ�PLL����
	
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);		//ѡ��PLLΪϵͳʱ��
	/*
	RCC_HCLKConfig(RCC_SYSCLK_Div1);				//AHB����Ƶ
	RCC_PCLK1Config(RCC_HCLK_Div2);		//APB1����Ƶ 36MHZ
	RCC_PCLK2Config(RCC_HCLK_Div1);		//APB2����Ƶ 72MHz
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//�δ�ѡ���ⲿʱ��  HCLK/8=9
	*/
	RCC_HCLKConfig(RCC_SYSCLK_Div8);	
	RCC_PCLK1Config(RCC_HCLK_Div1);		//APB1
	RCC_PCLK2Config(RCC_HCLK_Div1);		//APB2
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);	//�δ�ѡ���ⲿʱ��  HCLK
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//�����˿���ӳ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);		//ֻ����SW����io�ڣ�A13��A14	
	//GPIO_PinRemapConfig(GPIO_Remap_PD01,ENABLE);	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	 //����GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	 //����GPIOBʱ��
	gpio_init_pin(GPIOA,GPIO_Pin_All,GPIO_Mode_AIN);
	gpio_init_pin(GPIOB,GPIO_Pin_All,GPIO_Mode_AIN);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//����USART1
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);	//����SPI
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		//�����ж�������
	EXTI_DeInit();//�жϳ�ʼ��
	 
}

void delay_us(u32 nus)
{
	u32 temp;
	SysTick->LOAD=nus*SYSTICK_CLOCK; 					//ʱ�����
	SysTick->VAL=0x00;        					//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;      					 //��ռ�����
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
