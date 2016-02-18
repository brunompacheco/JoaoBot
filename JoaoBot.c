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

ISR(TIMER0_OVF_vect);

PidType PID;

int main() {
	motorInit();

	usartInit(57600);
	usartEnableReceiver();
	usartEnableTransmitter();
	usartStdio();

	timer0ClockPrescaller256();
	timer0NormalMode();
	timer0OC0AOff();
	timer0OC0BOff();
	timer0ActivateOverflowInterrupt();


	i2c_init();

	adxl345_init();

	l3g4200d_init();
	l3g4200d_setoffset(0.11, -1.71, -0.46);
	//l3g4200d_settemperatureref();

	PID_init(&PID, 5,0,0, 0);
	PID_SetMode(&PID, 1);
	PID_SetOutputLimits(&PID, -255, 255);

	PID.mySetpoint = 0;

	_delay_ms(200);

	sei();
	while(1) {



//	printf("%c", 27);
//	printf("%c", '[');
//	printf("%c", '2');
//	printf("%c", 'J');

//	printf("\033[2J\f");
	}

	return 0;
}

ISR(TIMER0_OVF_vect) {
	l3g4200d_getdata(&gx,&gy,&gz);
	adxl345_getdata(&ax, &ay, &az);

	angle = (0.96)*(angle + gy*0.004096) + (0.04)*((az*180)/3.14159);

	PID.myInput = angle;
	PID_Compute(&PID);

	printf("\e[1;1H\e[2J");
	printf("FUCKING ANGLE: %f\r\n", angle);
	printf("PID output: %f\r\n", PID.myOutput);
	printf("GX: %.2f\t|| AX: %.2f\r\n", gx, ax);
	printf("GY: %.2f\t|| AY: %.2f\r\n", gy, ay);
	printf("GZ: %.2f\t|| AZ: %.2f\r\n", gz, az);
}
