/*
 * RTC WITH I2C.c
 *
 * Created: 3/12/2022 5:22:20 PM
 * Author : Blu-Ray
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "I2C_DRIVER_MASTER.h"
#include "BIT Macros.h"

#define RTC_Write_address	0xD0
#define RTC_Read_address	0xD1

//TimeKeeper Register in RTC
#define Seconds_Register    0x00
#define Minutes_Register    0x01
#define Hours_Register      0x02
int main(void)
{
    TWI_INIT(SCL_F_100,Pre_Scaler_1);
	TWI_Start();
	TWI_SLA_AND_WR(RTC_Write_address);
    while (1) 
    {
		//second Register
		TWI_Repeated_Start();
		TWI_SLA_AND_WR(RTC_Write_address);
		TWI_Write(Seconds_Register);
		TWI_STOP();
		
		//Minutes Register
		TWI_Repeated_Start();
		TWI_SLA_AND_WR(RTC_Write_address);
		TWI_Write(Minutes_Register);
		TWI_STOP();
		
		//Hours Register
		TWI_Repeated_Start();
		TWI_SLA_AND_WR(RTC_Write_address);
		TWI_Write(Hours_Register);
		TWI_STOP();
		
		_delay_ms(1000);
		
		
    }
}

