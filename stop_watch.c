/*
 * stop_watch.c
 *
 * Created: 11/7/2021 7:47:55 PM
 * Author : ahmed ashraf 
 */ 
#include "stdio.h"
#define F_CPU 8000000
#include <util/delay.h>
#include "MemMap.h"
#include "Utils.h"
#include "StdTypes.h"

#define  BUTTON1 0
#define  BUTTON2 1
#define  BUTTON3 2


int main(void)
{
    /* ------------- session 6 ---------------  */
	DDRA = 0xff; // output port
	PORTA=0X00;
	DDRD = 0XFF;  // output port
	
	PORTB =0X00;
	DDRC = 0x00; // input port
	PORTC=0xff; // pull up for input
	
	// 
	u8 control=0 ;
	u8 state=0 ,reset , mode =0  , x=0 ;
	u8 _7seg[] = {0b00111111 , 
		                     0b00000110 , 
							 0b01011011 , 
							 0b01001111 , 
							 0b01100110 , 
							 0b01101101 ,
							 0b01111101 ,
							 0b00000111 ,
							 0b01111111 ,
							 0b01101111 }  ,i ; // Mockup table for comman cathod 7 segment

// 7 segment cathod 
void SEVEN_SegmentDisplay(unsigned char num )
{
	PORTA = ~_7seg[num%10];
	PORTD = _7seg[num/10];
}

// 7 segment using DECODER
void SEVEN_SegmentDisplay_Decoder(unsigned char num )
{
	PORTD = num%10;
	PORTD |= (num/10)<<4;
}
 
 
 while (1) 
{

/********* stop watch project in session 5 *********/
#if 1


	// ---------control button stop & pause -------------
	if (GET_BIT(PINC , BUTTON1)==0)
	{
		control = control ^1;
		reset=0;
		while(GET_BIT(PINC , BUTTON1)==0);
	}
	// --------- reset button -------------
	if (GET_BIT(PINC , BUTTON2)==0)
	{
		reset = reset ^1;
		control=0;
		while(GET_BIT(PINC , BUTTON2)==0);
	}
	// --------- mode button -------------
	if (GET_BIT(PINC , BUTTON3)==0)
	{
		mode = mode ^1;
		control=0;
		reset=0;
		while(GET_BIT(PINC , BUTTON3)==0);
	}
	


if (mode==1)
{
	SET_BIT(PORTB,2);
	if (GET_BIT(PINC , BUTTON1)==0)
	{
		x++;
		SEVEN_SegmentDisplay_Decoder(x);
		while(GET_BIT(PINC , BUTTON1)==0);
	}
	if (GET_BIT(PINC , BUTTON2)==0)
	{
		x--;
		SEVEN_SegmentDisplay_Decoder(x);
		while(GET_BIT(PINC , BUTTON2)==0);
	}
}
else
{
	CLR_BIT(PORTB,2);
	if (control==1 && x>0)
	{
		SEVEN_SegmentDisplay_Decoder(x);
		x--;
		if (x==0)
		{
			control = 0;
			SET_BIT(PORTB,0);
		}
		_delay_ms(400);
	}
	
	else
	{
		SEVEN_SegmentDisplay_Decoder(x);
	}
	if (reset==1)
	{
		x=0;
		control=0;
		reset=0;
		mode=0;
	}
}

#endif



}
}