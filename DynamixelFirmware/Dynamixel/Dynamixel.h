/*
* Dynamixel.h
*
* Created: 11/5/2013 3:59:51 PM
*  Author: Ahmad
*/


#ifndef DYNAMIXEL_H_
#define DYNAMIXEL_H_


#include "../SerialPort/SerialPort.h"
#include "Interpreter.h"
#include "ROM.h"


namespace Dynamixel{
	
	
	#define CONTROL_TABLE_SIZE 128
	
	#define default_ID 0X01
	#define default_FirmwareVersion 23
	#define default_ModelNumber 0X001C
	#define default_BaudNum 0X7
	#define default_ReturnDelayTime 0X1
	
	enum Control_Table_Address{
		ModelNumberL=0,
		ModelNumberH,
		FirmwareVersion,
		ID,
		BaudNum,
		ReturnDelayTime,
		CWAngleLimitL,
		CWAngleLimitH,
		CCWAngleLimitL,
		CCWAngleLimitH,
		HighestLimitTemperature=11,
		LowestLimitVoltage,
		HighestLimitVoltage,
		MaxTorqueL,
		MaxTorqueH,
		StatusReturnLevel,
		AlarmLED,
		AlarmShutdown,
	};

	void Initialize();
	void Reset();
	unsigned char GetByte(unsigned char address);
	unsigned int GetWord(unsigned char address);
	void SetByte(unsigned char address,unsigned char data);
	
	void SetBaudRate(unsigned char baudNum);
	void SetId(unsigned char id);	
	
}

#endif /* DYNAMIXEL_H_ */