#include<lpc21xx.h>

void uart0_init(void);
void uart0_tx(unsigned char);
unsigned char uart0_rx(void);
void uart0_str(unsigned char *);


void uart0_init(void)
{
PINSEL0=0x050005;
U0LCR=0x83;
U0DLL=97;
U0DLM=0;
U0LCR=0x03;
}

void uart0_tx(unsigned char txbyte)
{
while(((U0LSR>>5)&1)==0);
U0THR=txbyte;
}

unsigned char uart0_rx(void)
{
while((U0LSR&1)==0);
return U0RBR;
}

void uart0_str(unsigned char *p)
{
while(*p)
{
uart0_tx(*p++);
}
}
