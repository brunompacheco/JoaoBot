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

int i = 0;

int main() {


	motorInit();

	usartInit(57600);
	usartEnableReceiver();
	usartEnableTransmitter();
	usartStdio();

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

	PID_init(&PID, 5,0,0, 0);
	PID_SetMode(&PID, 1);
	PID_SetOutputLimits(&PID, -255, 255);

	PID.mySetpoint = 0;

	printf("\e[1;1H\e[2J");
	printf("STARTED!\r\n");
	_delay_ms(200);

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
	l3g4200d_getdata(&gx,&gy,&gz);
	adxl345_getdata(&ax, &ay, &az);

	angle = (0.96)*(angle + gy*0.004096) + (0.04)*((az*180)/3.14159);

	PID.myInput = angle;
	PID_Compute(&PID);

	printf("\e[1;1H\e[2J");
	printf("FUCKING ANGLE: %f\r\n", angle);
	printf("PID output: %f\r\n", PID.myOutput);
}
