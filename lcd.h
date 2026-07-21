#include<lpc21xx.h>
#include<string.h>
#include "delay.h"


#define  lcd (0xff << 10)
#define  rs 1<<18
#define  e 1<<19

void lcd_init(void);
void lcd_command(unsigned char);
void lcd_data(unsigned char);
void lcd_str(unsigned char *p);
void scroll(unsigned char *);




void lcd_init(void){
IODIR0= lcd|rs|e;
lcd_command(0x01);// clear the display
lcd_command(0x02);// return cursor to home position
lcd_command(0x0c);// display on, cursor off
lcd_command(0x38);// 8-bit interfacing(D0-D7)
}


void lcd_command(unsigned char cmd)
{
IOCLR0= lcd;
IOSET0=(cmd<<10);
IOCLR0=rs;
IOSET0=e;
ms_delay(2);
IOCLR0=	e;
}


void lcd_data(unsigned char data)
{
IOCLR0= lcd;
IOSET0=(data<<10);
IOSET0=rs;
IOSET0=e;
ms_delay(2);
IOCLR0=	e;
}


void lcd_str(unsigned char *p)					 
{
while(*p){
lcd_data(*p++);
}
}

void scroll(unsigned char *name)
{
int i=0,n,k=1;
n=strlen((char*)name);
while(1)
{
lcd_command(0x01);
if(i>(16-n))
{
lcd_command(0x80);
lcd_str(&name[n-k++]);
}


lcd_command(0x80+i);
lcd_str(name);
ms_delay(500);

if(i==16)
{
i=0;
k=1;
}
i++;
}
}

