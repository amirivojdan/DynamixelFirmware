/*
* SerialPort.cpp
*
* Created: 4/1/2013 3:19:44 AM
*  Author: Ahmad Amiri
*  E-Mail: ahmad.aav@gmail.com
*/
#include "SerialPort.h"

namespace Uart{
	
	void (*rxInterrupt)();
	void (*txInterrupt)();

	unsigned long int _baudRate;
	
	
	void Initialize(unsigned long int baudrate,Mode mode){
		
		
		unsigned char prescaler;
		if(mode==DoubleSpeed){
			prescaler=8;
			UCSRA |= (1<<U2X) ;
		}
		else if(mode==Normal){
			prescaler=16;
			UCSRA &= ~(1<<U2X);
		}
		else {
			prescaler=2;
		}

		_baudRate=baudrate;
		unsigned int ubbr = (unsigned int) ((F_CPU/(prescaler *_baudRate )) - 1);
		
		UBRRH = (ubbr>>8);
		UBRRL = ubbr;
		
		
		UCSRB = (1<<RXEN)|(1<<TXEN); // Enable receiver and transmitter
		UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1); // Set frame format to 8 data bits, no parity, 1 stop bit
		
	}

	unsigned long int GetBaudRate(){
		
		return _baudRate;
	}

	void SendByte(unsigned char data){
		
		
		//Wait until the transmitter is ready
		while(!(UCSRA & (1<<UDRE)))
		{
			//Do nothing ( Polling Method )
		}
		UDR=data;
		//Now write the data to USART buffer
		
	}

	void WriteLine(char* str){
		int len=strlen(str);
		for (int i=0;i<len;i++)
		{
			SendByte(str[i]);
		}
	}

	unsigned char GetByte(){
		
		//Wait until a data is available
		while(!(UCSRA & (1<<RXC)))
		{
			//Do nothing ( Polling Method )
		}
		//Now USART has got data from host
		//and is available in buffer
		return UDR;
	}

	void EnableReceive(){
		
		UCSRB |= (1<<RXEN);
	}

	void DisableReceive(){
		
		UCSRB &= ~(1<<RXEN);
	}

	void EnableTransmit(){
		UCSRB |= (1<<TXEN);
	}

	void DisableTransmit(){
		UCSRB &= ~(1<<TXEN);
	}

	void EnableRxInterrupt(void (*fptr)()){
		rxInterrupt=fptr;
		UCSRB |= (1 << RXCIE);
	}

	void DisableRxInterrupt(){
		UCSRB &= ~(1 << RXCIE);
		rxInterrupt = NULL;
	}

	void EnableTxInterrupt(void (*fptr)()){
		txInterrupt=fptr;
		UCSRB |= (1 << TXCIE);
	}

	void DisableTxInterrupt(){

		UCSRB &= ~(1 << TXCIE);
		txInterrupt = NULL;
	}

	ISR(USART_RXC_vect){
		if (rxInterrupt!=NULL)
		{
			rxInterrupt();
		}
		
	}

	ISR(USART_TXC_vect){
		if (txInterrupt!=NULL)
		{
			txInterrupt();
		}
	}
}

