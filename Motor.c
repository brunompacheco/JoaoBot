#include "Motor.h"
#include "LS_defines.h"
#include "LS_ATmega328.h"


void motorInit() {

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
		clrBit(PORTB, M1_DIR);
		timer0SetCompareBValue(pwm1);
	}
	else{
		setBit(PORTB, M1_DIR);
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
