/*
* SerialPort.h
*
* Created: 4/1/2013 3:19:23 AM
*  Author: Ahmad Amiri
*  E-Mail: ahmad.aav@gmail.com
*/


#ifndef SERIALPORT_H_
#define SERIALPORT_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/signal.h>
#include <string.h>
#include <util/delay.h>

namespace Uart{

	enum Mode{
	
		DoubleSpeed,
		Normal,
		Master
	};

	void Initialize(unsigned long int baudRate,Mode mode);
	unsigned long int GetBaudRate();
    void SendByte(unsigned char data);
	unsigned char GetByte();	
	void WriteLine(char*);	
	void EnableReceive();
	void DisableReceive(); 
	void EnableTransmit();
	void DisableTransmit();	
    void EnableRxInterrupt(void (*fptr)());
	void DisableRxInterrupt();
	void EnableTxInterrupt(void (*fptr)());
	void DisableTxInterrupt();
}	 

#endif /* SERIALPORT_H_ */


