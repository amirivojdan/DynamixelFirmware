/*
* Dynamixel.cpp
*
* Created: 11/5/2013 4:00:09 PM
*  Author: Ahmad Amiri
*/

#include "Dynamixel.h"
#include <avr/eeprom.h>
namespace Dynamixel{
	unsigned char ControlTable[CONTROL_TABLE_SIZE]={28,0,25,1,34,250,0,0,255,3,0,80,60,190,255,3,2,36,36,0,0,0,0,0,0,0,1,1,32,32,255,0,255,0,255,0,5,255,0,255,0,200,0,12,24,0,0,0,0,32,0};
	
	
	void Initialize(){
		ControlTable[ModelNumberL]= EEPROM::ReadByte(ModelNumberL);
		ControlTable[ModelNumberH]= EEPROM::ReadByte(ModelNumberH);
		
		ControlTable[FirmwareVersion]= EEPROM::ReadByte(FirmwareVersion);
		ControlTable[ReturnDelayTime]= EEPROM::ReadByte(ReturnDelayTime);
		
		ControlTable[BaudNum]=EEPROM::ReadByte(BaudNum);
		
		Uart::Initialize(2000000/(ControlTable[BaudNum]+1),F_CPU,Uart::DoubleSpeed);
		ControlTable[ID]=EEPROM::ReadByte(ID);
		
		Uart::EnableRxInterrupt(Interpreter::RxInterruptHandler);
	}
	void Reset(){

		EEPROM::WriteByte(ID,default_ID);
		EEPROM::WriteByte(FirmwareVersion,default_FirmwareVersion);
		EEPROM::WriteWord(ModelNumberL,default_ModelNumber);
		EEPROM::WriteByte(BaudNum,default_BaudNum);
		EEPROM::WriteByte(ReturnDelayTime,default_ReturnDelayTime);
	}
	
	unsigned char GetByte(unsigned char address){
		return ControlTable[address];
	}
	
	unsigned int GetWord(unsigned char address){
		return ControlTable[address]+(ControlTable[address+1]<<8);
	}
	
	void SetByte(unsigned char address,unsigned char data){
		ControlTable[address] = data;
	}
	
	void SetBaudRate(unsigned char baudNum)
	{
		Uart::SetBaudRate((2000000/(baudNum+1)),Uart::DoubleSpeed);
		EEPROM::WriteByte(BaudNum,baudNum);
	}
	
	void SetId(unsigned char id){
		
		ControlTable[ID]=id;
		EEPROM::WriteByte(ID,id);
	}

}