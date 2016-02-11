#include "LS_defines.h"
#include "LS_ATmega328.h"

//#include <avr/io.h>
//#include "LS_i2c_master.h"
//#include "twi_master.h"
#include "i2cmaster.h"
#include "l3g4200d.h"
#include "adxl345.h"

#define SAD 0x69<<1

int main() {
	usartInit(9600);
	usartEnableReceiver();
	usartEnableTransmitter();
	usartStdio();

	i2c_init();

	adxl345_init();

	l3g4200d_init();

	l3g4200d_settemperatureref();

	double ax = 0;
	double ay = 0;
	double az = 0;
	double gx = 0;
	double gy = 0;
	double gz = 0;


	adxl345_getdata(&ax, &ay, &az);
	//adxl345_setoffset(ax, ay, az);
	l3g4200d_getdata(&gx,&gy,&gz);
	l3g4200d_setoffset(gx,gy,gz);

	_delay_ms(200);
	while(1) {

	l3g4200d_getdata(&gx,&gy,&gz);
	adxl345_getdata(&ax, &ay, &az);

//	printf("%c", 27);
//	printf("%c", '[');
//	printf("%c", '2');
//	printf("%c", 'J');
//	printf("\033[2J\f");
	printf("\e[1;1H\e[2J");
	printf("GX: %.2f || AX: %.2f\r\n", gx, ax);
	printf("GY: %.2f || AY: %.2f\r\n", gy, ay);
	printf("GZ: %.2f || AZ: %.2f\r\n", gz, az);

	_delay_ms(200);
	}

	return 0;
}
