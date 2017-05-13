/*
 * init.c
 *
 * Created: 2015/10/6 17:07:32
 *  Author: God
 */ 

#include "init.h"

void clock_init(void)
{
	 RCC_DeInit();		//ʱ�ӳ�ʼ��
	 RCC_HSEConfig(RCC_HSE_ON);		//��HSE��8MHZ
	 while(!RCC_WaitForHSEStartUp());		//�ȴ�HSE�ȶ�
	 RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);		//PLL9��Ƶ��72MHZ
	 RCC_PLLCmd(ENABLE);		//��PLL
	 while(RCC_GetITStatus(RCC_FLAG_PLLRDY)!=RESET);		//�ȴ�PLL����
	 RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);		//ѡ��PLLΪϵͳʱ��
	 RCC_HCLKConfig(RCC_SYSCLK_Div1);				//AHB����Ƶ
	 RCC_PCLK1Config(RCC_HCLK_Div2);		//APB1����Ƶ 36MHZ
	 RCC_PCLK2Config(RCC_HCLK_Div1);		//APB2����Ƶ 72MHz
	 RCC_ADCCLKConfig(RCC_PCLK2_Div6);		//ADC 6��Ƶ 12MHZ
	 SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//�δ�ѡ���ⲿʱ��  HCLK/8
	 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//�����˿���ӳ��
	 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);		//ֻ����SW����io�ڣ�A13��A14	 

	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	 //����GPIOAʱ��
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	 //����GPIOBʱ��
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	 EXTI_DeInit();
}

void delay_us(u32 nus)
{
	u32 temp;
	SysTick->LOAD=nus*9; 					//ʱ�����
	SysTick->VAL=0x00;        					//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;      					 //��ռ�����
}

void gpio_init_pin(GPIO_TypeDef* GPIOx, u16 GPIO_Pin,GPIOMode_TypeDef MODE)
{
	GPIO_InitTypeDef io;
	io.GPIO_Mode = MODE;
	io.GPIO_Pin=GPIO_Pin;
	io.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOx,&io);
}
