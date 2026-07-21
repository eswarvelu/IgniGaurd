#include<lpc21xx.h>

void uart1_init(void);
void uart1_tx(unsigned char);
unsigned char uart1_rx(void);
void uart1_str(unsigned char *);

void uart1_init(void)
{
PINSEL0=0x050005;
U1LCR=0x83;
U1DLL=97;
U1DLM=0;
U1LCR=0x03;
}


void uart1_tx(unsigned char txbyte)
{
while(((U1LSR>>5)&1)==0);
U1THR=txbyte;
}


unsigned char uart1_rx(void)
{
while((U1LSR&1)==0);
return U1RBR;
}


void uart1_str(unsigned char *p)
{
while(*p)
{
uart1_tx(*p++);
}
}
