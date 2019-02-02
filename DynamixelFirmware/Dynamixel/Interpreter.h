/*
* Interpreter.h
*
* Created: 7/4/2013 12:55:37 AM
*  Author: Ahmad Amiri
*/


#ifndef INTERPRETER_H_
#define INTERPRETER_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../Utility/RingBuffer.h"
#include "../Timers/Timers.h"
#include "../SerialPort/SerialPort.h"
#include "Dynamixel.h"

namespace Dynamixel{
	namespace Interpreter{
		enum Instruction{
			
			PING=0x01,
			READ_DATA=0x02,
			WRITE_DATA=0x03,
			REG_WRITE=0x04,
			ACTION=0x05,
			RESET=0x06,
			SYNC_WRITE=0x83
			
		};
		
		enum Error{
			InputVoltageError=0,
			AngleLimitError=1,
			OverheatingError=2,
			RangeError=3,
			ChecksumError=4,
			OverloadError=5,
			InstructionError=6,
		};

		#define MASTER_ID		0xFE
		#define BROADCAST_ID    0xFF
		#define HEADER    0xFF
		#define TIMEOUT_DURATION 1000U
		
		void RxInterruptHandler();
		void Timeout();
		void Dispatch(unsigned char data);
		void Analyze();
		void Validate();
		void Execute();
		void Response();
		unsigned char GetChecksum();
	}
}
#endif /* INTERPRETER_H_ */