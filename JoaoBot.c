#include "LS_defines.h"
#include "LS_ATmega328.h"

int main() {
	int rcv = 0;

	usartInit(9600);
	usartEnableReceiver();
	usartEnableTransmitter();
	usartStdio();

	printf("waiting for input");
	do {
		rcv = usartReceive();
	} while(rcv != 10);

	return 0;
}
