/*
* RingBuffer.h
*
* Created: 7/3/2013 8:51:41 PM
*  Author: Ahmad
*/


#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_
#include <avr/interrupt.h>
namespace RingBuffer{

	void  ClearBuffer(void);
	int   GetBufferState(void);
	void  PutChar( unsigned char data );
	bool GetChar(unsigned char & data);
}
#endif /* RINGBUFFER_H_ */