#include<lpc21xx.h>
#include<string.h>
#include "lc.h"
#include "uart0.h"
#include "uart1.h"


#define m1 1<<21
#define m2 1<<22


unsigned char* scan(void);


int main()
{

IODIR1=m1|m2;
//stop condition
IOSET1=m1;
IOSET1=m2;

lcd_init();
uart0_init();
uart1_init();
lcd_command(0x01);
lcd_command(0x80);
lcd_str("theft detection");
ms_delay(1000);
while(1)
{
unsigned char key[]="26001EC83ECE";
unsigned char *id;
lcd_command(0x01);
lcd_command(0x80);
lcd_str("scan the key");
id=scan();
 if(strcmp((char*)key,(char*)id)==0)
 {
 lcd_command(0x01);
 lcd_command(0x80);
 lcd_str("Acess Granted");
 lcd_command(0xc0);
 lcd_str("Engine Started");
 ms_delay(300);
 //motor code
   IOSET1=m1;
   IOCLR1=m2; // led light for motor
 }
 else
 {
 // stop the motor 
  IOSET1=m1;
  IOSET1=m2;
  lcd_command(0x01);
  lcd_command(0x80);
  lcd_str("Invalid card");
  lcd_command(0xc0);
  lcd_str("Acess Deneid");
  ms_delay(3000);

  uart1_str("at\r\n");
  ms_delay(10);
  uart1_str("at+cmgf=1\r\n");
  ms_delay(10);
  uart1_str("at+cmgs=\"+919486821832\"\r\n");
  ms_delay(10);
  //while(uart1_rx() != '>');
  uart1_str("someone take your bike ALEART");
  uart1_tx(0x1a); 
  lcd_command(0x01);
  lcd_command(0x80);
  lcd_str("message sent");
 }
 }
 
}


unsigned char* scan(void)

{
static unsigned char card[13],i;
 for(i=0;i<12;i++)
{
 card[i]=uart0_rx();
 }
 card[i]='\0';
 //uart0_rx();
 //uart0_rx();
return card;
 }
