#include "LS_defines.h"
#include "LS_ATmega328.h"

//#include <avr/io.h>
//#include "LS_i2c_master.h"
//#include "twi_master.h"
#include "i2cmaster.h"

#define SAD 0x69<<1

int main() {
	usartInit(9600);
	usartEnableReceiver();
	usartEnableTransmitter();
	usartStdio();

	i2c_init();

	// ------------------------------------------------//
	// SDO/SA0 is HIGH
//		unsigned char SAD = 0x69;
	//			   	 		 SUB	 DATA	 DATA
	unsigned char send[3] = { 0xA8, 0, 0 };

	unsigned char buff[5] = { 0, 0, 0, 0, 0 };

	_delay_ms(1000);

	//START
	printf("START: ");
	if (i2c_start(SAD | I2C_WRITE) == 1) {
		printf("\n\rstart: FAILED TO ACCESS DEVICE\n\r");
		return 0;
	}
	printf("success\n\r");

	//WRITE
	printf("WRITE: ");
	if (i2c_write(send[0]) == 1) {
		printf("\n\rwrite: FAILED TO WRITE\n\r");
		return 0;
	}
	printf("success\n\r");

	//REP START
	printf("REP START: ");
	if (i2c_rep_start(SAD | I2C_READ) == 1) {
		printf("\n\rrep_start: FAILED TO ACCESS DEVICE\n\r");
		return 0;
	}
	printf("success\n\r");

	//READ ACK
	printf("READ ACK: ");
	buff[0] = i2c_readAck();
	printf("success\n\r");

	//READ NAK
	printf("READ NAK: ");
	buff[1] = i2c_readNak();
	printf("success\n\r");

	//STOP
	printf("STOP: ");
	i2c_stop();
	printf("success\n\r");

	printf("OUT_X_L data = %#X \n\r", buff[0]);
	printf("OUT_X_H data = %#X \n\r", buff[1]);

	//Juntar dois bytes
	//var myShort = (short) (myByteArray[0] << 8 | myByteArray[1]);

	return 0;
}
