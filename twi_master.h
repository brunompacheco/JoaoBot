//------------------------------------------------------------------------------
// File:		twi_master.h
// Purpose:		Two-wire master implementation for ATmega328P
// Version:		1.0
// Author:		Hazael dos Santos Batista
//------------------------------------------------------------------------------

#ifndef __I2C_MASTER_H_DEFINED
#define __I2C_MASTER_H_DEFINED

#ifndef TRUE
#	define TRUE		1
#endif
#ifndef FALSE
#	define FALSE	0
#endif

#define TWI_START					0x08
#define TWI_REP_START				0x10
#define TWI_ARB_LOST				0x38

#define TWI_MTX_ADR_ACK				0x18
#define TWI_MTX_ADR_NACK			0x20
#define TWI_MTX_DATA_ACK			0x28
#define TWI_MTX_DATA_NACK			0x30

#define TWI_MRX_ADR_ACK				0x40
#define TWI_MRX_ADR_NACK			0x48
#define TWI_MRX_DATA_ACK			0x50
#define TWI_MRX_DATA_NACK			0x58

#define TWI_STX_ADR_ACK				0xA8
#define TWI_STX_ADR_ACK_M_ARB_LOST	0xB0
#define TWI_STX_DATA_ACK			0xB8
#define TWI_STX_DATA_NACK			0xC0
#define TWI_STX_DATA_ACK_LAST_BYTE	0xC8

#define TWI_SRX_ADR_ACK				0x60
#define TWI_SRX_ADR_ACK_M_ARB_LOST	0x68
#define TWI_SRX_GEN_ACK				0x70
#define TWI_SRX_GEN_ACK_M_ARB_LOST	0x78
#define TWI_SRX_ADR_DATA_ACK		0x80
#define TWI_SRX_ADR_DATA_NACK		0x88
#define TWI_SRX_GEN_DATA_ACK		0x90
#define TWI_SRX_GEN_DATA_NACK		0x98
#define TWI_SRX_STOP_RESTART		0xA0

#define TWI_NO_STATE				0xF8
#define TWI_BUS_ERROR				0x00

void			twiMasterInit(unsigned char twbr, unsigned char bufferSize);
void			twiStartTransceiver(void);
void			twiTransmitData(unsigned char slaveAddr, char* msg, unsigned char msgSize);
void			twiRequestData(unsigned char slaveAddr, unsigned char msgSize);
unsigned char	twiGetReceivedData(char *msg, unsigned char msgSize);
unsigned char	twiIsTransceiverBusy(void);
unsigned char	twiGetStateInfo(void);

#endif