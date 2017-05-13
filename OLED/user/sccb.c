
#include "sccb.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ο�������guanfu_wang���롣
//ALIENTEKս��STM32������V3
//SCCB ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/18
//�汾��V1.0		    							    							  
//////////////////////////////////////////////////////////////////////////////////
 
//��ʼ��SCCB�ӿ�
//CHECK OK
void sccb_init(void)
{		
	SCCB_SCL_OUT;
	SCCB_SCL_RESET;	
	SCCB_SDA_OUT;
	SCCB_SDA_SET;
	sccb_stop();
}			 

//SCCB��ʼ�ź�
//��ʱ��Ϊ�ߵ�ʱ��,�����ߵĸߵ���,ΪSCCB��ʼ�ź�
//�ڼ���״̬��,SDA��SCL��Ϊ�͵�ƽ
void sccb_start(void)
{
   SCCB_SDA_SET;     //�����߸ߵ�ƽ	   
   SCCB_SCL_SET;	    //��ʱ���߸ߵ�ʱ���������ɸ�����
    DELAY50US;  
   SCCB_SDA_RESET;
    DELAY50US;	 
   SCCB_SCL_RESET;	    //�����߻ָ��͵�ƽ��������������Ҫ	  
}

//SCCBֹͣ�ź�
//��ʱ��Ϊ�ߵ�ʱ��,�����ߵĵ͵���,ΪSCCBֹͣ�ź�
//����״����,SDA,SCL��Ϊ�ߵ�ƽ
void sccb_stop(void)
{
   SCCB_SDA_RESET;
    DELAY50US;	 
   SCCB_SCL_SET;	
    DELAY50US; 
   SCCB_SDA_SET;	
    DELAY50US;
}  
//����NA�ź�
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
//SCCB,д��һ���ֽ�
//����ֵ:0,�ɹ�;1,ʧ��. 
u8 sccb_write_byte(u8 dat)
{
	u8 j,res;	 
	for(j=0;j<8;j++) //ѭ��8�η�������
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
	SCCB_SDA_IN;		//����SDAΪ���� 
	DELAY50US;
	SCCB_SCL_SET;			//���յھ�λ,���ж��Ƿ��ͳɹ�
	DELAY50US;
	if(SCCB_SDA_R) res=0;  //SDA=1������1
	else res=1;         //SDA=0���ͳɹ�������0
	SCCB_SCL_RESET;		 
	SCCB_SDA_OUT;		//����SDAΪ���    
	return res;  
}	 
//SCCB ��ȡһ���ֽ�
//��SCL��������,��������
//����ֵ:����������
u8 sccb_read_byte(void)
{
	u8 temp=0,j;    
	SCCB_SDA_IN;		//����SDAΪ����  
	for(j=8;j>0;j--) 	//ѭ��8�ν�������
	{		     	  
		DELAY50US;
		SCCB_SCL_SET;
		temp=temp<<1;
		if(SCCB_SDA_R)temp++;   
		DELAY50US;
		SCCB_SCL_RESET;
	}	
	SCCB_SDA_OUT;		//����SDAΪ���    
	return temp;
} 							    
//д�Ĵ���
//����ֵ:0,�ɹ�;1,ʧ��.
u8 sccb_write_reg(u8 reg,u8 data)
{
	sccb_start(); 					//����SCCB����
	if(!sccb_write_byte(SCCB_ID))return 0;	//д����ID	  
	DELAY100US;
  	if(!sccb_write_byte(reg))return 0;		//д�Ĵ�����ַ	  
	DELAY100US;
  	if(!sccb_write_byte(data))return 0; 	//д����	 
  	sccb_stop();	  
  	return	1;
}		  					    
//���Ĵ���
//����ֵ:�����ļĴ���ֵ
u8 sccb_read_reg(u8 reg)
{
	u8 val=0;
	sccb_start(); 				//����SCCB����
	sccb_write_byte(SCCB_ID);		//д����ID	  
	DELAY100US;	 
  	sccb_write_byte(reg);			//д�Ĵ�����ַ	  
	DELAY100US;	  
	sccb_stop();   
	DELAY100US;	   
	//���üĴ�����ַ�󣬲��Ƕ�
	sccb_start();
	sccb_write_byte(SCCB_ID|0X01);	//���Ͷ�����	  
	DELAY100US;
  	val=sccb_read_byte();		 	//��ȡ����
  	sccb_no_ack();
  	sccb_stop();
  	return val;
}















