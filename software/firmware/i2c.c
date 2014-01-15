/**
* @author Alexander Entinger, MSc
* @brief this module is responsible the i2c interface to the functionality of this motor controller
* @file i2c.c
* @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
*/

#include "i2c.h"
#include "hal.h"
#include "motor_control.h"
#include "encoder.h"
#include "status_led_control.h"
#include <stdint.h>
#include <util/delay.h>
#include <util/twi.h>
#include <avr/interrupt.h>

static uint8_t const I2C_SLAVE_BASE_ADDRESS = 0x50; // base address of this motor controller i2c slave node
static uint8_t const TWBR_100 = 72; // TWI Bit Rate register settings for fOSC = 16 MHz and I2C-Rate = 100 k

/**
* @brief this function initializes the i2c interface
*/
void init_i2c() {
	// set all i2c address pins to inputs without pullups
	I2C_ADR_BIT_0_PORT &= ~(1<<I2C_ADR_BIT_0);
	I2C_ADR_BIT_0_DDR &= ~(1<<I2C_ADR_BIT_0);
	I2C_ADR_BIT_1_PORT &= ~(1<<I2C_ADR_BIT_1);
	I2C_ADR_BIT_1_DDR &= ~(1<<I2C_ADR_BIT_1);
	I2C_ADR_BIT_2_PORT &= ~(1<<I2C_ADR_BIT_2);
	I2C_ADR_BIT_2_DDR &= ~(1<<I2C_ADR_BIT_2);
	// wait a little
	_delay_ms(50);
	// read the values
	uint8_t const i2c_adr_offset = (I2C_ADR_BIT_0_PIN & (1<<I2C_ADR_BIT_0)) |
	(I2C_ADR_BIT_1_PIN & (1<<I2C_ADR_BIT_1)) |
	(I2C_ADR_BIT_2_PIN & (1<<I2C_ADR_BIT_2));
	// calculate i2c slave address
	uint8_t const i2c_slave_address = I2C_SLAVE_BASE_ADDRESS | i2c_adr_offset;
	// assign it to the TWI address register
	TWAR = (i2c_slave_address<<1);
	// set the i2c pins to inputs without pullup
	DDRC &= ~((1<<PC4) | (1<<PC5));
	// clear the prescale values
	TWSR &= ~((1<<TWPS1) | (1<<TWPS1));
	// set the twi bit register
	TWBR = TWBR_100;
	// set the control register appopriately
	TWCR = (1<<TWEA) | (1<<TWEN) | (1<<TWIE) | (1<<TWINT);
}

/* REGISTER DESCRIPTION
RegAdr | Descripton
0      | Control-and-Status-Register
WRITE: BIT0 = 1 => FWD
       BIT1 = 1 => BWD
       BIT2 = 1 => Encoders enable
	   BIT3 = 1 => Encoders disable
	   BIT4 = 1 => Turn orange led on
	   BIT5 = 1 => Turn orange led off
READ:  BIT0 = 1 => FWD
	   BIT0 = 0 => BWD 
	   BIT1 = 1 => Encoders enabled
	   BIT1 = 0 => Encoders disabled
1      | Speed Register (Min. 0, max. 200) (R/W)
2      | Encoder 1 Low Byte (RO)
3      | Encoder 1 High Byte (RO)
4      | Encoder 2 Low Byte (RO)
5      | Encoder 2 High Byte (RO)
*/

#define CONTROL_STATUS_REG_ADR		(0x00)
#define SPEED_REG_ADR				(0x01)
#define ENC1_LOW_BYTE_REG_ADR		(0x02)
#define ENC1_HIGH_BYTE_REG_ADR		(0x03)
#define ENC2_LOW_BYTE_REG_ADR		(0x04)
#define ENC2_HIGH_BYTE_REG_ADR		(0x05)

void TWI_ACK() {
	TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN) | (1<<TWIE); // clear the interrupt flag, return ACK for transmitting next byte)
}
void TWI_NACK() {
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWIE); // clear the interrupt flag, return NACK to signalize that this is the last byte to be transmitted)
}
void TWI_RELEASE_BUS() {
	TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN) | (1<<TWIE); // returns to unadressed slave mode in case of error conditions
}
void TWI_STOP() {
	TWCR = (1<<TWEN) | (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWSTO);
	while(TWCR & (1<<TWSTO)) { continue; }
}		

#define INVALID_ADR					(0xFF)
/**
* @brief interrupt service routine
*/
ISR(TWI_vect) {
	static uint8_t register_address = INVALID_ADR;
	
	static uint16_t enc1 = 0x00, enc2 = 0x00;

	switch(TWSR) {
		/* SLAVE TRANSMITTER MODE */
		case TW_ST_SLA_ACK: // slave adress + read intention has been received, ACK has been returned
		case TW_ST_DATA_ACK: { // data has been transmitted, ACK received
		switch(register_address) {
			case CONTROL_STATUS_REG_ADR: {
				uint8_t data = 0x00;
				if(get_motor_direction() == FWD) data |= 0x01;
				if(get_encoder_state() == ENCODER_ON) data |= 0x02;
				TWDR = data;
				register_address++;
				TWI_ACK();
			} break;
			case SPEED_REG_ADR: {
				TWDR = get_motor_speed();
				register_address++;
				TWI_ACK();
			} break;
			case ENC1_LOW_BYTE_REG_ADR: {
				enc1 = read_encoder_1();
				TWDR = (uint8_t)(enc1 & 0xFF);
				register_address++;
				TWI_ACK();
			} break;
			case ENC1_HIGH_BYTE_REG_ADR: {
				TWDR = (uint8_t)((enc1>>8) & 0xFF);
				enc1 = 0x00;
				register_address++;
				TWI_ACK();
			} break;
			case ENC2_LOW_BYTE_REG_ADR: {
				enc2 = read_encoder_2();
				TWDR = (uint8_t)(enc2 & 0xFF);
				register_address++;
				TWI_ACK();
			} break;
			case ENC2_HIGH_BYTE_REG_ADR: {
				TWDR = (uint8_t)((enc2>>8) & 0xFF);
				enc2 = 0x00;
				register_address++;
				TWI_NACK();
			} break;
			default: { TWDR = 0x00; TWI_NACK(); } break;
		}
	} break;
	case TW_ST_DATA_NACK: case TW_ST_LAST_DATA: TWI_ACK(); break;
	/* SLAVE RECEIVER MODE */
	case TW_SR_SLA_ACK: { // slave adress + write intention has been received, ACK has been returned
		register_address = INVALID_ADR;
		TWI_ACK();
	} break;
	case TW_SR_DATA_ACK: { // data has been received, ACK has been returned
		uint8_t const data = TWDR; // read the data from the register
		if(register_address == INVALID_ADR) { // we have not been addressed yet
			register_address = data;
			TWI_ACK();
		} else { // we have been addressed receiving last byte for accessing the registers
			switch(register_address) { // write to the available registers
				case CONTROL_STATUS_REG_ADR: {
					if(data & (1<<0)) set_motor_direction(FWD);
					if(data & (1<<1)) set_motor_direction(BWD);
					if(data & (1<<2)) enable_encoder();
					if(data & (1<<3)) disable_encoder();
					if(data & (1<<4)) orange_led_on();
					if(data & (1<<5)) orange_led_off();
					TWI_NACK();
				} break;
				case SPEED_REG_ADR: {
					set_motor_speed(data);
					if(data > 0) red_led_on();
					else red_led_off();
					TWI_NACK();
				} break;
				default: TWI_NACK(); break;
			}
		}
	} break;
	case TW_SR_DATA_NACK: TWI_NACK(); break;
	case TW_SR_STOP: {
		TWI_STOP();
		TWI_RELEASE_BUS();
	} break;
    case TW_BUS_ERROR: TWI_STOP(); break;

	/* RESET TWI TO BE ADRESSED AGAIN */
	default: TWI_RELEASE_BUS(); break;
	
	} // end of switch	
}