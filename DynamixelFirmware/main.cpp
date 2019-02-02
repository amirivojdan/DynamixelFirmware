/*
* DynamixelFirmware.cpp
*
* Created: 4/1/2013 3:10:09 AM
*  Author: Ahmad Amiri
*/

#define F_CPU 8000000UL


#include <avr/io.h>
#include "Dynamixel/Dynamixel.h"
#include "MPU-6050/MPU6050.h"
#include "SerialPort/SerialPort.h"
#include <util/delay.h>
#define TRUE 1

int main(void)
{
	
	sei();
	//Dynamixel::Reset();
	Dynamixel::Initialize();
	
	unsigned char data;
	while(TRUE)
	{
		if(RingBuffer::GetChar(data)){
			Dynamixel::Interpreter::Dispatch(data);
		}
	}
	
	//MPU6050::Initialize();
	//Uart::Initialize(250000,F_CPU,Uart::DoubleSpeed);
	//Uart::SendByte(MPU6050::GetByte(MPU6050_PWR_MGMT_1));
	//MPU6050::WriteByte(MPU6050_PWR_MGMT_1,0);
	//Uart::WriteLine("IMU Configured !");
	//while(TRUE)
	//{
	//
	//Uart::SendByte(MPU6050::GetByte(67));
	//Uart::SendByte(MPU6050::GetByte(68));
	//
	//}
}