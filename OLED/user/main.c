#include "malloc.h"
#include "stmflash.h"
#include "sh1106.h"
#include "string.h"
#include "stdio.h"

int main(void)
 {
	char buf[10];
	int n = 0;
	clock_init();
	delay_ms(20);
	sh1106_init();
	sh1106_clear();
	while(1)
	{
		
		sprintf(buf, "%d", n);
		//delay_ms(5);
		sh1106_show_string(1,2,buf, 24);
		n++;
		
	}
}
