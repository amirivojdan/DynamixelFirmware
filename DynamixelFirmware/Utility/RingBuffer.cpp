/*
* RingBuffer.cpp
*
* Created: 7/3/2013 8:51:32 PM
*  Author: Ahmad Amiri
*/
#include "RingBuffer.h"
namespace RingBuffer{
	
	#define BUFFER_SIZE	256
	volatile unsigned char gbDxlBuffer[BUFFER_SIZE] = {0};
	volatile unsigned char gbDxlBufferHead = 0;
	volatile unsigned char gbDxlBufferTail = 0;

	void ClearBuffer(void)
	{
		// Clear communication buffer
		gbDxlBufferHead = gbDxlBufferTail;
	}

	int GetBufferState(void)
	{
		short NumByte;
		
		if( gbDxlBufferHead == gbDxlBufferTail )
		NumByte = 0;
		else if( gbDxlBufferHead < gbDxlBufferTail )
		NumByte = gbDxlBufferTail - gbDxlBufferHead;
		else
		NumByte = BUFFER_SIZE - (gbDxlBufferHead - gbDxlBufferTail);
		
		return (int)NumByte;
	}

	void PutChar( unsigned char data )
	{
		if( GetBufferState() == (BUFFER_SIZE-1) )
		return;
		
		gbDxlBuffer[gbDxlBufferTail] = data;

		if( gbDxlBufferTail == (BUFFER_SIZE-1) )
		gbDxlBufferTail = 0;
		else
		gbDxlBufferTail++;
	}

	bool GetChar(unsigned char & data)
	{
		
		if( gbDxlBufferHead == gbDxlBufferTail ){
			return false;
		}
		
		data = gbDxlBuffer[gbDxlBufferHead];
		if( gbDxlBufferHead == (BUFFER_SIZE-1) )
		{
			gbDxlBufferHead = 0;
		}
		else{
			gbDxlBufferHead++;
		}
		return true;
	}
}