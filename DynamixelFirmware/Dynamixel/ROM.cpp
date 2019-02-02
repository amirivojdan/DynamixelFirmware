/*
* ROM.c
*
* Created: 6/30/2013 3:59:01 AM
*  Author: Ahmad Amiri
*/

#include "ROM.h"

namespace Dynamixel{
	
	namespace EEPROM{
		
		void WriteByte(unsigned char address,unsigned char value){
			eeprom_write_byte ((uint8_t *)address, value);
		}
		void WriteWord(unsigned char address,unsigned int value){
			eeprom_write_word ((uint16_t *)address,value);
		}
		
		unsigned char ReadByte(unsigned char address){
			return eeprom_read_byte((uint8_t *) address);
		}
		
		unsigned int ReadWord(unsigned char address){
			return eeprom_read_word((uint16_t *) address);
		}
	}
}