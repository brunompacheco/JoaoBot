//------------------------------------------------------------------------------
// File:		twi_master.c
// Purpose:		Two-wire master implementation for ATmega328P
// Version:		1.0
// Author:		Hazael dos Santos Batista
//------------------------------------------------------------------------------

#include <avr/interrupt.h>
#include <stdlib.h>
#include "twi_master.h"

volatile char* twiBuffer = 0;
static volatile unsigned char twiMsgSize;
static volatile unsigned char twiState = TWI_NO_STATE;
static volatile unsigned char lastTransOk = 0;

void twiMasterInit(unsigned char twbr, unsigned char bufferSize)
{
	if(twiBuffer == NULL) {
		twiBuffer = (char*)calloc(bufferSize, sizeof(char));
	}
	TWBR = twbr;
	TWDR = 0xFF;
	TWCR = (1<<TWEN)|
		   (0<<TWIE)|(0<<TWINT)|
		   (0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|
		   (0<<TWWC);
}

unsigned char twiIsTransceiverBusy(void)
{
	return (TWCR & (1<<TWIE));
}

unsigned char twiGetStateInfo(void)
{
	while (twiIsTransceiverBusy());
	return twiState;
}

void twiTransmitData(unsigned char slaveAddr, char* msg, unsigned char msgSize)
{
	unsigned char aux;

	while (twiIsTransceiverBusy());
	
	twiMsgSize = msgSize + 1;
	twiBuffer[0] = slaveAddr << 1;
	for (aux = 0; aux < msgSize; aux++) {
		twiBuffer[aux + 1] = msg[aux];
	}

	lastTransOk = 0;

	twiState = TWI_NO_STATE;

	TWCR = (1<<TWEN)|
		   (1<<TWIE)|(1<<TWINT)|
		   (0<<TWEA)|(1<<TWSTA)|(0<<TWSTO)|
		   (0<<TWWC);
}

void twiRequestData(unsigned char slaveAddr, unsigned char msgSize)
{
	while (twiIsTransceiverBusy());

	twiMsgSize = msgSize + 1;
	twiBuffer[0] = (slaveAddr << 1) | 1;
	
	lastTransOk = 0;
	
	twiState = TWI_NO_STATE;
	
	TWCR = (1<<TWEN)|
		   (1<<TWIE)|(1<<TWINT)|
		   (0<<TWEA)|(1<<TWSTA)|(0<<TWSTO)|
		   (0<<TWWC);
}

void twiStartTransceiver(void)
{
	while (twiIsTransceiverBusy());
	lastTransOk = 0;
	twiState         = TWI_NO_STATE ;
	TWCR = (1<<TWEN)|
		   (1<<TWIE)|(1<<TWINT)|
		   (0<<TWEA)|(1<<TWSTA)|(0<<TWSTO)|
		   (0<<TWWC);
}

unsigned char twiGetReceivedData(char *msg, unsigned char msgSize)
{
	unsigned char i;

	while (twiIsTransceiverBusy());

	if(lastTransOk) {
		for (i = 0; i<msgSize; i++) {
			msg[i] = twiBuffer[i];
		}
	}
	
	return lastTransOk;
}

ISR(TWI_vect)
{
	static unsigned char twiBufPtr;

	switch (TWSR) {
	case TWI_START:
	case TWI_REP_START:
		twiBufPtr = 0;
	case TWI_MTX_ADR_ACK:
	case TWI_MTX_DATA_ACK:
		if (twiBufPtr < twiMsgSize) {
			TWDR = twiBuffer[twiBufPtr++];
			TWCR = (1<<TWEN)|
				   (1<<TWIE)|(1<<TWINT)|
				   (0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|
				   (0<<TWWC);
			} else {
			lastTransOk = TRUE;
			TWCR = (1<<TWEN)|
				   (0<<TWIE)|(1<<TWINT)|
				   (0<<TWEA)|(0<<TWSTA)|(1<<TWSTO)|
				   (0<<TWWC);
		}
		break;
	case TWI_MRX_DATA_ACK:
		twiBuffer[twiBufPtr++] = TWDR;
	case TWI_MRX_ADR_ACK:
		if (twiBufPtr < (twiMsgSize - 1)) {
			TWCR = (1<<TWEN)|
				   (1<<TWIE)|(1<<TWINT)|
				   (1<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|
				   (0<<TWWC);
			} else {
			TWCR = (1<<TWEN)|
				   (1<<TWIE)|(1<<TWINT)|
				   (0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|
				   (0<<TWWC);
		}
		break;
	case TWI_MRX_DATA_NACK:
		twiBuffer[twiBufPtr] = TWDR;
		lastTransOk = TRUE;
		TWCR = (1<<TWEN)|
			   (0<<TWIE)|(1<<TWINT)|
			   (0<<TWEA)|(0<<TWSTA)|(1<<TWSTO)|
			   (0<<TWWC);
		break;
	case TWI_ARB_LOST:
		TWCR = (1<<TWEN)|
			   (1<<TWIE)|(1<<TWINT)|
			   (0<<TWEA)|(1<<TWSTA)|(0<<TWSTO)|
			   (0<<TWWC);
		break;
	case TWI_MTX_ADR_NACK:
	case TWI_MRX_ADR_NACK:
	case TWI_MTX_DATA_NACK:
	case TWI_BUS_ERROR:
	default:
		twiState = TWSR;
		TWCR = (1<<TWEN)|
			   (0<<TWIE)|(0<<TWINT)|
			   (0<<TWEA)|(0<<TWSTA)|(0<<TWSTO)|
			   (0<<TWWC);
	}
}
