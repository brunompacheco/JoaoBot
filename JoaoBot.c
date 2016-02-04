#include "LS_defines.h"
#include "LS_ATmega328.h"
#include "twi_master.h"

int main() {
	usartInit(9600);
	usartEnableReceiver();
	usartEnableTransmitter();
	usartStdio();

	twiMasterInit(0x48, 20);

	printf("START\n\r");

	// ------------------------------------------------//
	// SDO/SA0 is HIGH
	char SAD = 0b1101001;
	//			   	 SUB	DATA	DATA
	char send[3] = 	{0x0F, 	0, 		0		};

	char buff[5] = {0, 0, 0, 0, 0};

	printf("TRANSMIT\n\r");
	twiTransmitData(SAD, send, 1);
	printf("REQUEST\n\r");
	twiRequestData(SAD, 1);

	printf("GET RECEIVED\n\r");
	twiGetReceivedData(buff, 1);

	printf("twi data = %#X \n\r", buff[0]);

	return 0;
}
