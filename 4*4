#include <reg51.h>
#include <intrins.h>

#define uchar unsigned char
#define uint  unsigned int

uchar ledbit=0 ;
uchar data leddata[8] ;
uchar idata regment[8]={0,0,0,0,0,0,0,0};   

uchar code keytable[16]={0xEE,0xED,0xEB,0xE7,	//0,1,2,3
                         0xDE,0xDD,0xDB,0xD7,   //4,5,6,7
						 0xBE,0xBD,0xBB,0xB7,   
						 0x7E,0x7D,0x7B,0x77};  	  	  

uchar code keytable[16]={0x7D,0xD7,0xBE,0xBD,	//C,7,8,9
                         0x7B,0xDE,0xDD,0xDB,   //A,4,5,6
						 0x77,0xED,0xEB,0xE7,   
						 0x7E,0xEE,0xBB,0xB7};  


uchar code ledtable[16]={0xed,0x81,0xf4,0xb5,	
                         0x99,0x3d,0x7d,0x85,   
                         0xfd,0xbd,0x02,0xd9,	
						 0x10,0x6c,0xdd,0x7c};    

uchar code ledtable[16]={0xbd,0x7d,0xb5,0xd9,	
                         0xfd,0x3d,0xf4,0x02,  
                         0x85,0x99,0x81,0xed,	
						 0x6c,0xdd,0x7c,0x10};  

void delay()
{
	uchar i;
	for(i=0;i<=220;i++){;}
}

void main()
{
	uchar input1,input2,dis_buf,i,j,k;
	while(1)
	{
		P1=0x0f ;
		if(P1!=0x0f)
		{
			input1=P1;
			P1=0xf0 ;
			input2=P1;
			dis_buf=input1+input2;
			for(i=0;i<16;i++)
			{
				if(dis_buf==keytable[i])
				{
					if(ledbit==8) ledbit=0;
					leddata[ledbit]=ledtable[i];
					ledbit++ ;
					
					if(dis_buf==0x7E)
					{sum();
						for(j=0;j<8;j++)
						{
							regment[i]=ledtable[i];
						}
						for(j=0;k<8;j++)
						{
							ledtable[i]=0x00;
						}
						P2=0x00;
					}
					break ;
				}
			}
			P1=0xf0 ;
			while(P1!=0xf0) ;
		}
		
		for(i=0;i<ledbit;i++)
		{
			P2=_cror_(0x7f,i);
			P0=leddata[ledbit-i-1];
			delay();
		}
		P0=0x00;
	}
}
