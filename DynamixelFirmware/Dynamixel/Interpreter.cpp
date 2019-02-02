/*
* Interpreter.cpp
*
* Created: 7/4/2013 12:55:56 AM
*  Author: Ahmad Amiri
*/

#include "Interpreter.h"

namespace Dynamixel{
	namespace Interpreter{
		
		volatile unsigned char state=1;
		volatile unsigned char id;
		volatile unsigned char length;
		volatile unsigned char instruction;
		volatile unsigned char parameterCount;
		volatile unsigned char parameterIndex;
		volatile unsigned int  checksum;
		volatile unsigned char inputchecksum;
		volatile unsigned char computedchecksum;
		volatile unsigned char error;
		volatile unsigned char parameters[255];
		
		unsigned char data0;
		unsigned char data1;

		void RxInterruptHandler(){
			cli();
			RingBuffer::PutChar(UDR);
			sei();
		}

		void Dispatch(unsigned char data){

			//Set the timeout timer
			//timer1(TIMER1_PRESCALER_1024, TIMEOUT_DURATION, Timeout);
			if(state==1)
			{
				// First Header
				if(data==HEADER)
				{
					state=2;
				}
			}
			else if (state==2)
			{
				//Uart::WriteLine("2");
				// Second Header
				if (data==HEADER)
				{
					state=3;
				}
				else{
					state=1;
				}
			}
			
			else if(state==3)
			{
				if(data!=HEADER)
				{
					// ID
					if(data==GetByte(ID))
					{
						id=data;
						checksum=id;
						state=4;
					}
					else{
						state=1;
					}
				}
			}
			else if (state==4)
			{
				length=data;
				checksum+=length;
				parameterCount=(data-2);
				state=5;
			}
			else if (state==5)
			{
				instruction=data;
				checksum+=instruction;
				parameterIndex=0;
				state=6;
			}
			else if(state==6){
				
				if(instruction==PING){
					inputchecksum=data;
					Analyze();
				}
				else if(parameterCount>0 && parameterIndex<parameterCount){
					
					parameters[parameterIndex]=data;
					checksum+=data;
					parameterIndex++;
					if(!(parameterIndex<parameterCount)){
						state=7;
					}
				}
			}
			else if (state==7)
			{
				inputchecksum=data;
				Analyze();
			}
		}

		void Analyze(){
			state=1;
			computedchecksum = ~((unsigned char)checksum);
			Validate();
			// TODO: Execute();
			Response();
		}
		
		void Validate(){
			// make error response
			error=0;
			if (inputchecksum!=computedchecksum)
			{
				error= 1<< ChecksumError;
			}
			
			//if (instruction!=PING && instruction!=READ && instruction!= SYNC_WR && instruction!=REG_WRITE && instruction!=WRITE && instruction!=ACTION && instruction!=RESET)
			//{
			//error= 1<<InstructionError;
			//}
			
			if( !(instruction>=PING || instruction<=RESET) && instruction!=SYNC_WRITE){
				error= 1<<InstructionError;
			}
		}
		
		void Response(){

			if(instruction==PING){

				cli();
				checksum =~ ((unsigned char) (GetByte(ID)+2+error));
				Uart::SendByte(HEADER);
				Uart::SendByte(HEADER);
				Uart::SendByte(GetByte(ID));
				Uart::SendByte(0x02);
				Uart::SendByte(error);
				Uart::SendByte(checksum);
				sei();
			}
			else if (instruction==READ_DATA)
			{
				cli();
				
				Uart::SendByte(HEADER);
				Uart::SendByte(HEADER);
				Uart::SendByte(GetByte(ID));
				checksum = GetByte(ID)+error+parameters[1]+2;
				Uart::SendByte(parameters[1]+2); // Length
				Uart::SendByte(error);
				for (unsigned char i=parameters[0];i<parameters[0]+parameters[1];i++)
				{
					checksum += GetByte(i);
					Uart::SendByte(GetByte(i));
				}
				Uart::SendByte(~((unsigned char) checksum));
				sei();
			}
			
			else if (instruction == WRITE_DATA)
			{
				unsigned char paramIndex=1;
				for (unsigned char address=parameters[0];address<parameters[0]+length-3;address++)
				{
					SetByte(address,parameters[paramIndex]);
					if (address==ID)
					{
						SetId(parameters[paramIndex]);
					}
					else if (address==BaudNum)
					{
						SetBaudRate(parameters[paramIndex]);
					}
					paramIndex++;
				}				
			}
		}
		
		void Timeout(){
			state=1;
		}
	}
}