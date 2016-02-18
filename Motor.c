#include "Motor.h"
#include "LS_defines.h"
#include "LS_ATmega328.h"


void motorInit() {
	DDRD = 0b01111000;
	PORTD = 0x00;

	timer0FastPWMMaxMode();
	timer0ClockPrescaller64();
	timer0OC0ANonInvertedMode();
	timer0OC0BNonInvertedMode();
	timer0SetCompareAValue(0);
	timer0SetCompareBValue(0);
	timer0DeactivateCompareAInterrupt();
	timer0DeactivateCompareBInterrupt();
}

//Acionamento apenas motor A
void motorA(int pwmA, int dirA)
{
	if(dirA) {
		clrBit(PORTD, PD4);
		timer0SetCompareAValue(pwmA);
	} else {
		setBit(PORTD, PD4);
		timer0SetCompareAValue(255-pwmA);
	}
}

//Acionamento apenas motor B
void motorB(int pwmB, int dirB)
{
	if(dirB){
		clrBit(PORTD, PD3);
		timer0SetCompareBValue(pwmB);
	}
	else{
		setBit(PORTD, PD3);
		timer0SetCompareBValue(255-pwmB);
	}
}

//Acionamento motores AB (iguais)
void motorAIB(int pwm, int dir)
{
	if(dir){
		clrBit(PORTD, PD4);
		clrBit(PORTD, PD3);
		timer0SetCompareAValue(pwm);
		timer0SetCompareBValue(pwm);
	}
	else{
		setBit(PORTD, PD4);
		setBit(PORTD, PD3);
		timer0SetCompareAValue(255-pwm);
		timer0SetCompareBValue(255-pwm);
	}
}

//Acionamento motores AB (diferentes)
void motorADB(int pwmA, int dirA, int pwmB, int dirB)
{
	if(dirA) {
		clrBit(PORTD, PD4);
		timer0SetCompareAValue(pwmA);
	} else {
		setBit(PORTD, PD4);
		timer0SetCompareAValue(255-pwmA);
	}

	if(dirB) {
		clrBit(PORTD, PD3);
		timer0SetCompareBValue(pwmB);
	} else {
		setBit(PORTD, PD3);
		timer0SetCompareBValue(255-pwmB);
	}
}
