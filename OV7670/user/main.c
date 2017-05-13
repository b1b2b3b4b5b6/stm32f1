
#include "xpt2046.h"
#include "ili9325.h"
#include "NRF24L01.h"
#include "mmc_sd.h"
#include "malloc.h"
#include "stmflash.h"
#include "exfuns.h"
#include "bmp.h"
#include "ov7670.h"

#define OV_READ(BYTE)		BYTE=(GPIOA->IDR)&0x00000ff

void exit_xpt2046(void);
void exit_NRF24L01(void);
void usart1_init(void);

u16 date[2];
u8 nrf_date[16];
const u8 black[3]={0,0,0};
const u8 white[3]={255,255,255};
const u8 red[3]={0,0,255};
const u8 green[3]={0,255,0};
const u8 blue[3]={255,0,0};
u8 bytes1[512]={1,2,3,4,5,6,7,8,9};
u8 bytes2[512];
int main(void)
 {
	 
	 vu16 temp[0x3d];
	 u16 n;
	 //signed int num[4];
	clock_init();
	delay_ms(20);
	mem_init();			//初始化内存池
	exfuns_init();		//为fatfs相关变量申请内存
	piclib_init();
	SD_Initialize();
	f_mount(fs[0],"0:",1); 					//挂载SD卡 
	//f_open(file,"0:3.txt",FA_WRITE |FA_CREATE_NEW|FA_OPEN_ALWAYS);
	//f_write(file,"24689",5,&bw);
	//f_close(file);
	//NRF_init(0,0);
	//exit_NRF24L01();
	//xpt2046_init();
	//exit_xpt2046();
	
	
//	ili9325_init();
	ili9325_gpio_init();
	CS_RESET;  //??????
	delay_us(50000);       
	ili9325_refresh565(0xff00);
	for(n=0;n<0x3d;n++)	temp[n]=ili9325_read_reg(n);


	//delay_ms(1000);

	//OV7670_Init();
	gpio_init_pin(GPIOA,GPIO_Pin_8,GPIO_Mode_IPU);
	gpio_init_pin(GPIOA,GPIO_Pin_15,GPIO_Mode_IPU);
	gpio_init_pin(GPIOA,0x00ff,GPIO_Mode_IPU);
	while(1)
	{	
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
void exit_NRF24L01(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;// 抢占优先级为1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =15 ;// 子优先级位15
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据上面指定的参数初始化NVIC寄存器
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);
	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}
void EXTI0_IRQHandler(void)
{	
	xpt2046_read(date,10);
	EXTI_ClearITPendingBit(EXTI_Line0);
}
void EXTI4_IRQHandler(void)
{
	NRF_receive_date(nrf_date);
	EXTI_ClearITPendingBit(EXTI_Line4);
}
void usart1_init(void)
{
	USART_InitTypeDef USART_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	NVIC_InitStrue.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStrue);
	
	gpio_init_pin(GPIOA,GPIO_Pin_9,GPIO_Mode_AF_PP);
	gpio_init_pin(GPIOA,GPIO_Pin_10,GPIO_Mode_IN_FLOATING);
	
	USART_InitStrue.USART_BaudRate=115200;
	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStrue.USART_Parity=USART_Parity_No;
	USART_InitStrue.USART_StopBits=USART_StopBits_1;
	USART_InitStrue.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStrue);//③
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//开启接收中断	
	USART_Cmd(USART1,ENABLE);//使能串口1
	
}

void USART1_IRQHandler(void)
{
	u8 res;
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		res= USART_ReceiveData(USART1);
		USART_SendData(USART1,res);
	}
}

