/*Biblioteca para acionamento do motor
 * pinos:
 * motor A: PD6 e PD4
 * motor B: PD5 e PD3
 */

/*//INCLUDES
#include <avr/io.h>
#include "LS_ATmega328.h"
#include "LS_defines.h"
*/
#include"Motor.c"

//CONFIGURAÇÃO DO TIMER
timer0FastPWMMaxMode();
timer0ClockPrescaller64();
timer0OC0ANonInvertedMode();
timer0OC0BNonInvertedMode();
timer0SetCompareAValue(0);
timer0SetCompareBValue(0);
timer0DeactivateCompareAInterrupt();
timer0DeactivateCompareBInterrupt();

//CONFIGURACAO DOS PORTS
DDRD = 0b01111000;
PORTD = 0x00;

/*FUNCOES
 * dir(A/B): 1 ou 0
 * pwm(A/B): valor PWM (0-255)
 */

//Acionamento apenas motor A
void motorA(int pwmA, int dirA);
//Acionamento apenas motor B
void motorB(int pwmB, int dirB);
//Acionamento motores AB (iguais)
void motorAIB(int pwm, int dir);
//Acionamento motores AB (diferentes)
void motorADB(int pwmA, int dirA, int pwmB, int dirB);
