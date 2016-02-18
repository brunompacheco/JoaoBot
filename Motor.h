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


#define M1_PWM PD5
#define M1_DIR PB0
#define M2_PWM PD6
#define M2_DIR PD7

/*FUNCOES
 * dir(A/B): 1 ou 0
 * pwm(A/B): valor PWM (0-255)
 */

void motorInit();

void motor2(int pwm2);
void motor1(int pwm1);
