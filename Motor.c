#include "LS_defines.h"
#include "LS_ATmega328.h"

//Acionamento apenas motor A
void motorA(int pwmA, int dirA)
{
	if(dirA)
		clrBit(PORTD, PD4);
	else
		setBit(PORTD, PD4);
	timer0SetCompareAValue(pwmA);
}

//Acionamento apenas motor B
void motorB(int pwmB, int dirB)
{
	if(dirB){
		clrBit(PORTD, PD3);
	}
	else{
		setBit(PORTD, PD3);
	}
	timer0SetCompareBValue(pwmB);
}

//Acionamento motores AB (iguais)
void motorAIB(int pwm, int dir)
{
	if(dir){
		clrBit(PORTD, PD4);
		clrBit(PORTD, PD3);
	}
	else{
		setBit(PORTD, PD4);
		setBit(PORTD, PD3);
	}
	timer0SetCompareAValue(pwm);
	timer0SetCompareBValue(pwm);
}

//Acionamento motores AB (diferentes)
void motorADB(int pwmA, int dirA, int pwmB, int dirB)
{
	if(dirA)
		clrBit(PORTD, PD4);
	else
		setBit(PORTD, PD4);
	timer0SetCompareAValue(pwmA);

	if(dirB)
		clrBit(PORTD, PD3);
	else
		setBit(PORTD, PD3);
	timer0SetCompareBValue(pwmB);
}
