#include "init.h"
#include "xpt2046.h"
void exit_xpt2046(void);
u16 date[2];
int main(void)
{	
		clock_init();
		xpt2046_init();
		exit_xpt2046();
		while (1)
		{
			delay_us(100);
		}
}
 
void exit_xpt2046(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;// 抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =15 ;// 子优先级位15
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据上面指定的参数初始化NVIC寄存器
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

EXTI0_IRQHandler(void)
{	
	xpt2046_read(date,10);
	EXTI_ClearITPendingBit(EXTI_Line0);
}

