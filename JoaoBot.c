#include "LS_defines.h"
#include "LS_ATmega328.h"

//#include <avr/io.h>
//#include "LS_i2c_master.h"
//#include "twi_master.h"
#include "i2cmaster.h"
#include "l3g4200d.h"
#include "adxl345.h"
#include "Motor.h"
#include "PID_v1.h"
#include <math.h>

#define SAD 0x69<<1

double ax = 0;
double ay = 0;
double az = 0;
double gx = 0;
double gy = 0;
double gz = 0;

volatile FloatType angle = 0;

volatile FloatType outmot = 0;

volatile FloatType setpoint = 0;

ISR(TIMER2_OVF_vect);

PidType PID;

volatile int init_calib = 0;
volatile double angle_off = 0;

int main() {

	usartInit(57600);
	usartEnableReceiver();
	usartEnableTransmitter();
	usartStdio();

	setBit(DDRB, M1_DIR);
	setBit(DDRD, M1_PWM);
	setBit(DDRD, M2_DIR);
	setBit(DDRD, M2_PWM);

	clrBit(PORTB, M1_DIR);
	clrBit(PORTD, M1_PWM);
	clrBit(PORTD, M2_PWM);
	clrBit(PORTD, M2_DIR);

	timer0FastPWMMaxMode();
	timer0ClockPrescaller64();
	timer0OC0ANonInvertedMode();
	timer0OC0BNonInvertedMode();
	timer0SetCompareAValue(0);
	timer0SetCompareBValue(0);
	timer0DeactivateCompareAInterrupt();
	timer0DeactivateCompareBInterrupt();

	timer2ClockPrescaller256();
	timer2NormalMode();
	timer2OC2AOff();
	timer2OC2BOff();
	timer2ActivateOverflowInterrupt();


	i2c_init();

	adxl345_init();

	l3g4200d_init();
	l3g4200d_setoffset(0.11, -1.71, -0.46);
	//l3g4200d_settemperatureref();

	PID_init(&PID, 15,0.2,1, 0);
	PID_SetMode(&PID, 1);
	PID_SetOutputLimits(&PID, -255, 255);

	PID.mySetpoint = 0;

	motor1(0);
	motor2(0);


//	printf("\e[1;1H\e[2J");
//	printf("STARTED!\r\n");
//	_delay_ms(200);

//	motor1(120);
//	printf("Motor1 = 120\r\n");
//	_delay_ms(500);
//	motor1(-120);
//	printf("Motor1 = -120\r\n");
//	_delay_ms(500);
//	motor1(120);
//	printf("Motor1 = 120\r\n");
//	_delay_ms(500);
//	motor1(0);
//	printf("Motor1 = 0\r\n");

	sei();

	while(1);

	return 0;
}

ISR(TIMER2_OVF_vect) {
	if (init_calib == 100) {
		angle_off = angle;
		init_calib++;
	} else {
		init_calib++;
	}


	l3g4200d_getdata(&gx,&gy,&gz);
	adxl345_getdata(&ax, &ay, &az);

	angle = (0.25)*(angle + gy*0.004096) + (0.75)*((asin(az)*180)/3.14159);

	PID.myInput = angle;// - angle_off;
	PID_Compute(&PID);

	if (angle > 45 || angle < -45) {
		motor1(0);
		motor2(0);
	} else {
//		if (angle > 10) {
//			motor1(-175);
//			motor2(-175);
//		} else if (angle < -10) {
//			motor1(175);
//			motor2(175);
//		} else if (angle > 5) {
//			motor1(-80);
//			motor2(-80);
//		} else if (angle < -5) {
//			motor1(80);
//			motor2(80);
//		} else if (angle > -5 && angle < 5) {
//			motor1(0);
//			motor2(0);
//		}

		motor1(PID.myOutput);
		motor2(PID.myOutput);
	}

	printf("\e[1;1H\e[2J");
	printf("FUCKING ANGLE: %f\r\n", angle);
//	printf("ANGLE w/ offset: %f\r\n", angle-angle_off);
	printf("PID output: %f\r\n", PID.myOutput);
}
