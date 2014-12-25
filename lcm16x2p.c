#include <reg51.h>
#include <intrins.h>
#include "LCM16X2P.H"
#define LCM_DB P2
sbit LCM_RS=P1^0;
sbit LCM_RW=P1^1;
sbit LCM_E=P1^2;
sbit LCM_BLC=P1^3;
unsigned int data DelayConst=140;
void LCMDelay(int ms)
{
unsigned int i,cnt;
cnt=DelayConst*ms;
for(i=0;i<cnt;i++);
}
unsigned char LCMReadState(void)
{
unsigned char state;
LCM_E=0;
LCM_RS=0;
LCM_RW=1;
LCM_E=1;
_nop_();
_nop_();
state=LCM_DB;
LCM_E=0;
return state;
}
void LCMClear(void)
{
LCMDelay(1);
LCM_E=0;
LCM_RS=0;
LCM_RW=1;
LCM_DB=0x01;
LCM_E=1;
_nop_();
_nop_();
LCM_E=0;
LCMDelay(1);
}
void LCMWriteCmd(unsigned char cmd)
{
LCMDelay(1);
LCM_E=0;
LCM_RS=0;
LCM_RW=0;

LCM_DB=cmd;

LCM_E=1;
_nop_();
_nop_();
LCM_E=0;
}
void LCMWriteData(unsigned char dc)
{
while(LCMReadState()&BUSYFLAG);
LCM_RS=1;
LCM_RW=0;
LCM_DB=dc;
LCM_E=1;
_nop_();
_nop_();
LCM_E=0;
}
void LCMInit(void)
{
LCMDelay(60);
LCMWriteCmd(0x38);
LCMDelay(5);
LCMWriteCmd(0x38);
LCMDelay(1);
LCMWriteCmd(0x38);
while(LCMReadState()&BUSYFLAG);
LCMWriteCmd(0x08);
while(LCMReadState()&BUSYFLAG);
LCMWriteCmd(0x01);
while(LCMReadState()&BUSYFLAG);
LCMWriteCmd(0x06);
while(LCMReadState()&BUSYFLAG);
LCMWriteCmd(0x0e);
while(LCMReadState()&BUSYFLAG);
}
void LCMGotoXY(unsigned char x,unsigned char y)
{
unsigned char cmd;
if(x==0)
{
cmd=0x80|y;

}
else
{
 cmd=0x80|0x40|y;
 
}
LCMWriteCmd(cmd);
while(LCMReadState()&BUSYFLAG);
 }
void LCMDisplayChar(unsigned char x,unsigned char y,unsigned char ch)
{
LCMGotoXY(x,y);
LCMWriteData(ch);
}
void LCMDisplayString(unsigned char x,unsigned char y,unsigned char* str)
{
unsigned char ptr;
ptr=0;

while(*(str+ptr)!=0)
{

LCMDisplayChar(x,(y+ptr),*(str+ptr));
ptr++;
 
 
}
}
void LCMBlink(unsigned char x,unsigned char y,unsigned char cmd)
{
LCMGotoXY(x,y);
if(cmd==BLINK)
{
LCMWriteCmd(0x0d);
}
else
{
LCMWriteCmd(0x0c);
}

}
