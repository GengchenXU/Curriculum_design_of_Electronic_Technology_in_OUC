#include <reg52.h>
#include <intrins.h>



sbit p34=P3^4;
sbit p35=P3^5;
sbit p20=P2^0;

//void moto_go();
//void moto_back();
//void moto_stp();
void delay(unsigned int xms);

void run(){
	p34=0;
	p35=0;
}

void back(){
	p34=1;
	p35=1;

}


void stop(){
	p35=0;
	p34=1;


}

void delay(unsigned int xms){
	unsigned int x,y;
	for(x=xms;x>0;x--){
	 	for(y=110;y>0;y--);		
	}
}

void pwmR(void){
	p35=0;
	p34=0;
	delay(100);
	p34=1;
	delay(100);
}
void pwmB(void){
	p35=1;
	p34=1;
	delay(100);
	p35=0;
	delay(100);
}

unsigned int time=0;
unsigned int blackline=0;

void Timer0Init()
{
	TMOD|=0x01;
	TH0=0xFC;
	TL0=0x18;
	TF0=0;
	TR0=1;
	ET0=1;
	EA=1;
	TR0=0;		

}


void   Init_INT0(){
	EX0=1;
	IT0=1;
	PX0=0;
	EA=1;

}

void int0(void) interrupt 0{

	blackline++;
	p20=0;
	delay(2000);
	p20=1;

}

void main(){
	Timer0Init();
	Init_INT0();
	run();
	while(1){
		while(blackline==3)
			pwmR();
		while(blackline==4)
			run();
		//while(blackline==5)
		//	pwm();	 
		if(blackline==6){
			stop();
			delay(5000);
			back();
			blackline++;
		
		}
		while(blackline==10)
			pwmB();
		while(blackline==11)
			back();
		//while(blackline==12)
		//	pwm();
		if(blackline==13)
			stop();
	
	}
}




