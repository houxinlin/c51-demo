#include "reg52.h"

#include "stdio.h"


#define LINK_LED_NUMBER 8
sbit pin =P2^0;
sbit keyPin1 =P0^4;
sbit keyPin2 =P0^5;
sbit keyPin3 =P0^6;
sbit changeFunctionKey = P3^2; 
sbit changeSpeedKey = P3^3; 

sbit p00=P0^0;
sbit p01=P0^1;
sbit p02=P0^2;
sbit p03=P0^3;

unsigned int T0Count=0;

int speed=500;
int state=0;
int LED_FF=0xff;
int loopLedState =1;
int ledState =0xff;
unsigned int  NUMBER[]={0xF9,0xA4,0xB0,0x99,0x92,0x82,0xf8,0x80,0x98}; 
int numberState =1;
void delay_ms(int  z)
{
   int  x,y;
   for(x=z;x>0;x--)
   for(y=110;y>0;y--);
}

void display(){
	p00=1;
	P1 =NUMBER[1];
	delay_ms(10);
	p00=0;
	
	p01=1;
	P1 =NUMBER[2];
	delay_ms(10);
	p01=0;

}
void ledFunction1(){
	P2=ledState=~ledState;

}
void ledFunction2(){
			P2= LED_FF & ~(1<<(state++));
			state=state>=LINK_LED_NUMBER?0:state;

}
void ledFunction3(){
	    int   i;

			for(i =0;i<LINK_LED_NUMBER;i++){
				P2= LED_FF & ~(1<<i);
				delay_ms(100);
			}
			P2=0xff;

}
void ledFunction4(){
	if(P2==0x00 || P2==0xff){
				P2=0x00;
	}else{
				P2=~P2;
	}

}
void ledFunction5(){
	int left =3;
	int right=4;
	while(left!=-1 && right !=8){
	  P2=(LED_FF & ~(1<<(left)))  &  ~(1<<(right));
	  delay_ms(100);
	  right++;left--;
	}
	P2=0xff;
}
void ledFunction6(){
	int left =0;
	int right=7;
	while(left!=4 && right !=3){
	  P2=(LED_FF & ~(1<<(left)))  &  ~(1<<(right));
	  delay_ms(100);
	  right--;left++;
	}
	P2=0xff;
}
void ledFunction7(){
		int i =rand()%8;
		int j =rand()%8;
		int k =rand()%8;
	
	  P2=LED_FF & ~(1<<(i)) & ~(1<<j)& ~(1<<k);
}



void main()
{		
	EX0 = 1;
	EX1=1;
	IT0 = 1;
	EA  = 1;
	p00 =1;p01 =0;p02 =0;p03 =0;
	P1=NUMBER[loopLedState-1];
	while(1)

	{		

					while(loopLedState==1){
								ledFunction1();
							  delay_ms(500);
					}
					while(loopLedState==2){
								ledFunction3();
							  delay_ms(speed);
					}
					while(loopLedState==3){
								ledFunction5();
							  delay_ms(speed);
					}
					while(loopLedState==4){
								ledFunction6();
							  delay_ms(speed);
					}
					while(loopLedState==5){
								ledFunction7();
							  delay_ms(50);
					}					
					
}
	}
void interruptHandler() interrupt 0
{
	if(changeFunctionKey == 0)
	{
		
		while(changeFunctionKey==0); 
		delay_ms(100);
		
	
 		if(changeFunctionKey==1){
			loopLedState=loopLedState>4?1:loopLedState+1;
			 P1=NUMBER[loopLedState-1];
		}
//		if(loopLedState==1){
//			P1=0x3F;
//		}
		
	}
}
void interruptHandler2() interrupt 2
{
	if(changeSpeedKey == 0)
	{
		
		while(changeSpeedKey==0); 
		delay_ms(100);
		
	
// 		if(changeSpeedKey==1){
//				speed-=100;
//				if(speed<=0) speed=500;
//		}
//		if(loopLedState==1){
//			P1=0x3F;
//		}
		
	}
}

