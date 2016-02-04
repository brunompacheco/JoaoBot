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

	//	twiMasterInit(0x48, 20);
	//	twiStartTransceiver();

	//	i2cMasterInit();

	i2c_init();

		// ------------------------------------------------//
		// SDO/SA0 is HIGH
//		unsigned char SAD = 0x69;
		//			   	 		 SUB	 DATA	 DATA
		unsigned char send[3] = {0x0F	,0		,0		};

		unsigned char buff[5] = {0, 0, 0, 0, 0};

	/*
		printf("TRANSMIT\n\r");
	//	twiTransmitData(SAD, send, 1);
		i2cMasterSendData(SAD, I2C_WRITE, send, 1);
		printf("REQUEST\n\r");
	//	twiRequestData(SAD, 1);
		i2cMasterSendData(SAD, I2C_READ, buff, 1);

	//	printf("GET RECEIVED\n\r");
	//	twiGetReceivedData(buff, 1);
	//	i2cMasterReadFromBuffer(buff, 1);
	*/
		_delay_ms(1000);

		printf("START: ");
		if (i2c_start(SAD | I2C_WRITE)==1) {
			printf("\n\rstart: FAILED TO ACCESS DEVICE\n\r");
			return 0;
		}
	//	i2c_start_wait(SAD+I2C_WRITE);
		printf("success\n\r");

		printf("WRITE: ");
		if (i2c_write(send[0])==1) {
			printf("\n\rwrite: FAILED TO WRITE\n\r");
			return 0;
		}
		printf("success\n\r");

		printf("REP START: ");
		if (i2c_rep_start(SAD | I2C_READ)==1) {
			printf("\n\rrep_start: FAILED TO ACCESS DEVICE\n\r");
			return 0;
		}
		printf("success\n\r");

		printf("READ NAK: ");
		buff[0] = i2c_readNak();
		printf("success\n\r");

		printf("STOP: ");
		i2c_stop();
		printf("success\n\r");


		printf("twi data = %#X \n\r", buff[0]);


	return 0;
}
