#include "LS_defines.h"
#include "LS_ATmega328.h"

//#include <avr/io.h>
//#include "LS_i2c_master.h"
//#include "twi_master.h"
#include "i2cmaster.h"
#include "l3g4200d.h"

#define SAD 0x69<<1

int main() {
	usartInit(9600);
	usartEnableReceiver();
	usartEnableTransmitter();
	usartStdio();

	i2c_init();

	l3g4200d_init();

	l3g4200d_settemperatureref();

	int16_t x = 0;
	int16_t y = 0;
	int16_t z = 0;

	//_delay_ms(200);
	while(1) {

	l3g4200d_getrawdata(&x,&y,&z);

	printf("==========\r\n");
	printf("GX: %d\r\n", x);
	printf("GY: %d\r\n", y);
	printf("GZ: %d\r\n", z);
	printf("==========\r\n");

	_delay_ms(200);
	}

	return 0;
}
