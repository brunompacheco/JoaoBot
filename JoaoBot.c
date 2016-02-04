#include "LS_defines.h"
#include "LS_ATmega328.h"

int main() {
	int rcv = 0;

	usartInit(9600);
	usartEnableReceiver();
	usartEnableTransmitter();
	usartStdio();

	printf("waiting for input\r\n");
	do {
		printf("\r\nnot 10\r\n");
		scanf("%d", &rcv);
	} while(rcv != 10);

	printf("\r\nrcv = %d\r\n", rcv);
	while(1);

	return 0;
}
