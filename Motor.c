#include "Motor.h"
#include "LS_defines.h"
#include "LS_ATmega328.h"


void motorInit() {
	setBit(DDRB, M1_DIR);
	setBit(DDRD, M1_PWM);
	setBit(DDRD, M2_DIR);
	setBit(DDRD, M2_PWM);

	clrBit(PORTB, M1_DIR);
	clrBit(PORTD, M1_PWM);
	clrBit(PORTD, M2_PWM);
	clrBit(PORTD, M2_DIR);

//	DDRD = 0b01111000;
//	PORTD = 0x00;

	timer0FastPWMMaxMode();
	timer0ClockPrescaller64();
	timer0OC0ANonInvertedMode();
	timer0OC0BNonInvertedMode();
	timer0SetCompareAValue(0);
	timer0SetCompareBValue(0);
	timer0DeactivateCompareAInterrupt();
	timer0DeactivateCompareBInterrupt();
}

////Acionamento apenas motor A
//void motor2(int pwmA, int dirA)
//{
//	if(dirA) {
//		clrBit(PORTD, M2_DIR);
//		timer0SetCompareAValue(pwmA);
//	} else {
//		setBit(PORTD, M2_DIR);
//		timer0SetCompareAValue(255-pwmA);
//	}
//}
//
////Acionamento apenas motor B
//void motor1(int pwmB, int dirB)
//{
//	if(dirB){
//		clrBit(PORTD, M1_DIR);
//		timer0SetCompareBValue(pwmB);
//	}
//	else{
//		setBit(PORTD, M1_DIR);
//		timer0SetCompareBValue(255-pwmB);
//	}
//}

//Acionamento apenas motor A
void motor2(int pwm2)
{
	if(pwm2>=0) {
		clrBit(PORTD, M2_DIR);
		timer0SetCompareAValue(pwm2);
	} else {
		setBit(PORTD, M2_DIR);
		timer0SetCompareAValue(255+pwm2);
	}
}

//Acionamento apenas motor B
void motor1(int pwm1)
{
	if(pwm1>=0){
		clrBit(PORTD, M1_DIR);
		timer0SetCompareBValue(pwm1);
	}
	else{
		setBit(PORTD, M1_DIR);
		timer0SetCompareBValue(255+pwm1);
	}
}

////Acionamento motores AB (iguais)
//void motorAIB(int pwm, int dir)
//{
//	if(dir){
//		clrBit(PORTD, PD4);
//		clrBit(PORTD, PD3);
//		timer0SetCompareAValue(pwm);
//		timer0SetCompareBValue(pwm);
//	}
//	else{
//		setBit(PORTD, PD4);
//		setBit(PORTD, PD3);
//		timer0SetCompareAValue(255-pwm);
//		timer0SetCompareBValue(255-pwm);
//	}
//}
//
////Acionamento motores AB (diferentes)
//void motorADB(int pwmA, int dirA, int pwmB, int dirB)
//{
//	if(dirA) {
//		clrBit(PORTD, PD4);
//		timer0SetCompareAValue(pwmA);
//	} else {
//		setBit(PORTD, PD4);
//		timer0SetCompareAValue(255-pwmA);
//	}
//
//	if(dirB) {
//		clrBit(PORTD, PD3);
//		timer0SetCompareBValue(pwmB);
//	} else {
//		setBit(PORTD, PD3);
//		timer0SetCompareBValue(255-pwmB);
//	}
//}
