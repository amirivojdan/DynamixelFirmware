/*
* ROM.h
*
* Created: 6/30/2013 3:58:41 AM
*  Author: Ahmad Amiri
*/


#ifndef ROM_H_
#define ROM_H_
#include <avr/eeprom.h>

namespace Dynamixel{
	namespace EEPROM{
		


		void WriteByte(unsigned char address,unsigned char value);
		void WriteWord(unsigned char address,unsigned int value);
		
		unsigned char ReadByte(unsigned char address);
		unsigned int ReadWord(unsigned char address);
		
	}
}
#endif /* ROM_H_ */