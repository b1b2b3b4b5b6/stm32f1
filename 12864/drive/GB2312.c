#define GB2312_HERE
#include "GB2312.h"

#define get_data_from_ROM()	(unsigned char)spi_rw(0xff)
#define send_command_to_ROM(dat) spi_rw(dat)

static void gpio_init(void)
{
	OUT(CS);
	spi_init();
}

void GB2312_init()
{
	gpio_init();
	SET(CS);
}

/*����ص�ַ��addrHigh����ַ���ֽ�,addrMid����ַ���ֽ�,addrLow����ַ���ֽڣ�����������DataLen���ֽڵ����ݵ� pBuff�ĵ�ַ*/
/*������ȡ*/
void get_n_bytes_data_from_ROM(uchar addrHigh,uchar addrMid,uchar addrLow,uchar *pBuff,uchar DataLen )
{
	uchar i;
	RESET(CS);
	send_command_to_ROM(0x03);
	send_command_to_ROM(addrHigh);
	send_command_to_ROM(addrMid);
	send_command_to_ROM(addrLow);
	for(i = 0; i < DataLen; i++ )
	     *(pBuff+i) = get_data_from_ROM();
	SET(CS);
}
void show_GB2312_string(uchar page,uchar column,uchar *text)
{
	u32  fontaddr=0;
	uchar i= 0;
	uchar addrHigh,addrMid,addrLow ;
	uchar fontbuf[32];			
	while((text[i]>0x00))
	{
		if(((text[i]>=0xb0) &&(text[i]<=0xf7))&&(text[i+1]>=0xa1))
		{						
			/*1������?����?�ꡧGB2312��?oo��??��?�쨢a??��??aIC?D��?��??��������???1?��?����????��o*/
			/*Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*32+ BaseAdd;BaseAdd=0*/
			/*���������̡�D?8??�̣�???����D3?������?3??����a��??����?��?��y2?��?��??��*/
			fontaddr = (text[i]- 0xb0)*94; 
			fontaddr += (text[i+1]-0xa1)+846;
			fontaddr = fontaddr*32;
			
			addrHigh = (fontaddr&0xff0000)>>16;  /*��??����???8??,1224??*/
			addrMid = (fontaddr&0xff00)>>8;      /*��??����??D8??,1224??*/
			addrLow = fontaddr&0xff;	     /*��??����?�̨�8??,1224??*/
			get_n_bytes_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,32 );/*��?32??��??����?��y?Y��?��?��?"fontbuf[32]"*/
			st7565r_show_16x16(page,column,fontbuf);/*??��?oo��?��?LCD��?��?y?a��3��??����?x?a��D��??����?fontbuf[]?a��y?Y*/
			i+=2;
			column+=16;
		}
		else if(((text[i]>=0xa1) &&(text[i]<=0xa3))&&(text[i+1]>=0xa1))
		{						
			/*1������?����?�ꡧGB2312��?15x16��?��?��?��??��?�쨢a??��??aIC?D��?��??��������???1?��?����????��o*/
			/*Address = ((MSB - 0xa1) * 94 + (LSB - 0xA1))*32+ BaseAdd;BaseAdd=0*/
			/*���������̡�D?8??�̣�???����D3?������?3??����a��??����?��?��y2?��?��??��*/
			fontaddr = (text[i]- 0xa1)*94; 
			fontaddr += (text[i+1]-0xa1);
			fontaddr = (u16)(fontaddr*32);
			
			addrHigh = (fontaddr&0xff0000)>>16;  /*��??����???8??,1224??*/
			addrMid = (fontaddr&0xff00)>>8;      /*��??����??D8??,1224??*/
			addrLow = fontaddr&0xff;	     /*��??����?�̨�8??,1224??*/
			get_n_bytes_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,32 );/*��?32??��??����?��y?Y��?��?��?"fontbuf[32]"*/
			st7565r_show_16x16(page,column,fontbuf);/*??��?oo��?��?LCD��?��?y?a��3��??����?x?a��D��??����?fontbuf[]?a��y?Y*/
			i+=2;
			column+=16;
		}

		else if((text[i]>=0x20) &&(text[i]<=0x7e))	
		{						
			unsigned char fontbuf[16];			
			fontaddr = (text[i]- 0x20);
			fontaddr = (unsigned long)(fontaddr*16);
			fontaddr = (unsigned long)(fontaddr+0x3cf80);			
			addrHigh = (fontaddr&0xff0000)>>16;
			addrMid = (fontaddr&0xff00)>>8;
			addrLow = fontaddr&0xff;

			get_n_bytes_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,16 );/*��?16??��??����?��y?Y��?��?��?"fontbuf[32]"*/
			
			st7565r_show_8x16(page,column,fontbuf);/*??��?8x16��?ASCII��?��?LCD��?��?y?a��3��??����?x?a��D��??����?fontbuf[]?a��y?Y*/
			i+=1;
			column+=8;
		}
		else
			i++;	
	}
	
}

