/*
 * I2C.h
 * I2C Driver For Master Atmega16/32
 * Created: 3/5/2022 6:06:03 PM
 * Author : Habeba Hamada
 */ 

#ifndef I2C_H_Driver

#define F_CPU 8000000UL

#include "BIT Macros.h"
#include <avr/io.h>
#include <stdint.h>

#define Start_ACK            0x08
#define Rep_Start_ACK        0x01
#define SLA_WR_T_and_ACK_R   0x18          //Slave ADD and WRITE BIT transmitted and ACK received
#define SLA_WR_T_and_NACK_R  0x20          //Slave ADD and WRITE BIT transmitted and NACK received
#define DATA_T_WITH_ACK      0x28          //Master Transmitted Data with ACK
#define DATA_T_WITH_NACK     0x30          //Master Transmitted Data with NACK
#define SLA_RD_T_and_ACK_R   0x40          //Slave ADD and READ BIT transmitted and NACK received
#define DATA_R_WITH_ACK      0x50          //Master received Data with ACK
#define DATA_R_WITH_NACK     0x58          //Master received Data with NACK

//define Used Registers
#define  TWI_Direction         DDRC
#define  TWI_Port              PORTC
#define  TWI_Bit_Rate_Register TWBR
#define  TWI_Control_Register  TWCR
#define  TWI_Status_Register   TWSR
#define  TWI_Data_Register     TWDR
#define  TWI_Address_Register  TWAR

#define Condition_ACK     1
#define Condition_NACK    0

//Define TWI pins
#define  SCL   0
#define  SDA   1

//Define TWCR Register PINS

#define   TWINT  7
#define   TWEA   6
#define   TWSTA  5
#define   TWSTO  4
#define   TWWC   3
#define   TWEN   2
#define   TWIE   0

//Define TWSR Register PINS

#define   TWPS0   0
#define   TWPS1   1

// pre_scale values               TWPS1   TWPS0
#define Pre_Scaler_1     1     //     0       0
#define Pre_Scaler_4     4     //     0       1
#define Pre_Scaler_16    16    //     1       0
#define Pre_Scaler_64    64    //     1       1

//CLOCK FREQUENCY
#define  SCL_F_100   100
#define  SCL_F_400   400



void TWI_INIT(uint8_t SCL_FR ,uint8_t Pre_scale)
{
	TWI_Bit_Rate_Register=(F_CPU/SCL_FR-16)/2*Pre_scale;
	
}

uint8_t TWI_Start()
{
	TWI_Control_Register =(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
	while(!GET_BIT(TWI_Control_Register,TWINT));
	return(TWI_Status_Register & 0xF8);
}

uint8_t TWI_Repeated_Start()
{
	TWI_Control_Register =(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
	while(!GET_BIT(TWI_Control_Register,TWINT));
	return(TWI_Status_Register & 0xF8);
}
 
uint8_t TWI_SLA_AND_WR(unsigned char SLA)
{
	TWI_Data_Register=(SLA<<1);
	TWI_Control_Register =(1<<TWEN)|(1<<TWINT);
	while(!GET_BIT(TWI_Control_Register,TWINT));
	return(TWI_Status_Register & 0xF8);
}

uint8_t TWI_SLA_AND_RD(unsigned char SLA)
{
	TWI_Data_Register=(SLA<<1);
	SET_BIT(TWI_Data_Register,0);
	TWI_Control_Register =(1<<TWEN)|(1<<TWINT);
	while(!GET_BIT(TWI_Control_Register,TWINT));
	return(TWI_Status_Register & 0xF8);
}

uint8_t TWI_Write(unsigned char Data)
{
	    TWI_Data_Register =Data;
		TWI_Control_Register =(1<<TWEN)|(1<<TWINT);
		while(!GET_BIT(TWI_Control_Register,TWINT));
		return(TWI_Status_Register & 0xF8);	
}

uint8_t TWI_Read(uint8_t* Data, uint8_t Condition)
{
	TWI_Control_Register =(1<<TWEN)|(1<<TWINT)|(READ_BIT(Condition, 0)<<TWEA);;
	while(!GET_BIT(TWI_Control_Register,TWINT));
	*Data = TWI_Data_Register;
	return(TWI_Status_Register & 0xF8);	
	
}
void TWI_STOP()
{
	TWI_Control_Register =(1<<TWSTO)|(1<<TWEN)|(1<<TWINT);
	while(GET_BIT(TWI_Control_Register,TWSTO));
}



#endif