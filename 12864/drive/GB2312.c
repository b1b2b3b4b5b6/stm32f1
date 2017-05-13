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

/*从相关地址（addrHigh：地址高字节,addrMid：地址中字节,addrLow：地址低字节）中连续读出DataLen个字节的数据到 pBuff的地址*/
/*连续读取*/
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
			/*1ú±ê?òì?￡¨GB2312￡?oo×??ú?§áa??×??aIC?Dμ?μ??·óéò???1?ê?à′????￡o*/
			/*Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+ 846)*32+ BaseAdd;BaseAdd=0*/
			/*óéóúμ￡D?8??μ￥???úóD3?·¨ò?3??êìa￡??ùò?·?èy2?è?μ??·*/
			fontaddr = (text[i]- 0xb0)*94; 
			fontaddr += (text[i+1]-0xa1)+846;
			fontaddr = fontaddr*32;
			
			addrHigh = (fontaddr&0xff0000)>>16;  /*μ??·μ???8??,1224??*/
			addrMid = (fontaddr&0xff00)>>8;      /*μ??·μ??D8??,1224??*/
			addrLow = fontaddr&0xff;	     /*μ??·μ?μí8??,1224??*/
			get_n_bytes_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,32 );/*è?32??×??úμ?êy?Y￡?′?μ?"fontbuf[32]"*/
			st7565r_show_16x16(page,column,fontbuf);/*??ê?oo×?μ?LCDé?￡?y?aò3μ??·￡?x?aáDμ??·￡?fontbuf[]?aêy?Y*/
			i+=2;
			column+=16;
		}
		else if(((text[i]>=0xa1) &&(text[i]<=0xa3))&&(text[i+1]>=0xa1))
		{						
			/*1ú±ê?òì?￡¨GB2312￡?15x16μ?μ?×?·??ú?§áa??×??aIC?Dμ?μ??·óéò???1?ê?à′????￡o*/
			/*Address = ((MSB - 0xa1) * 94 + (LSB - 0xA1))*32+ BaseAdd;BaseAdd=0*/
			/*óéóúμ￡D?8??μ￥???úóD3?·¨ò?3??êìa￡??ùò?·?èy2?è?μ??·*/
			fontaddr = (text[i]- 0xa1)*94; 
			fontaddr += (text[i+1]-0xa1);
			fontaddr = (u16)(fontaddr*32);
			
			addrHigh = (fontaddr&0xff0000)>>16;  /*μ??·μ???8??,1224??*/
			addrMid = (fontaddr&0xff00)>>8;      /*μ??·μ??D8??,1224??*/
			addrLow = fontaddr&0xff;	     /*μ??·μ?μí8??,1224??*/
			get_n_bytes_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,32 );/*è?32??×??úμ?êy?Y￡?′?μ?"fontbuf[32]"*/
			st7565r_show_16x16(page,column,fontbuf);/*??ê?oo×?μ?LCDé?￡?y?aò3μ??·￡?x?aáDμ??·￡?fontbuf[]?aêy?Y*/
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

			get_n_bytes_data_from_ROM(addrHigh,addrMid,addrLow,fontbuf,16 );/*è?16??×??úμ?êy?Y￡?′?μ?"fontbuf[32]"*/
			
			st7565r_show_8x16(page,column,fontbuf);/*??ê?8x16μ?ASCII×?μ?LCDé?￡?y?aò3μ??·￡?x?aáDμ??·￡?fontbuf[]?aêy?Y*/
			i+=1;
			column+=8;
		}
		else
			i++;	
	}
	
}

