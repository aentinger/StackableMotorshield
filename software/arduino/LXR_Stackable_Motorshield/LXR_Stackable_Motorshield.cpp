/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this module implements the library for controlling the LXRobotics Stackable Motorshield
 * @file LXR_Stackable_Motorshield.cpp
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */
 
#include "LXR_Stackable_Motorshield.h"
#include <Wire.h>

static uint8_t const CONTROL_STATUS_REG_ADR = 0;
static uint8_t const SPEED_REG_ADR = 1;
static uint8_t const ENCODER_1_LOW_REG_ADR = 2;
static uint8_t const ENCODER_2_LOW_REG_ADR = 4;
 
/**
 * @brief Constructor
 * @param dev_address stackable motorshield device address
 */
LXR_Stackable_Motorshield::LXR_Stackable_Motorshield(uint8_t const dev_address) : m_dev_address(dev_address) {
	Wire.begin();
}

/** 
 * @brief this function sets the speed of the motor
 * @param speed sets the speed of the motor (0 => stop(break), 200 => full speed)
 */
void LXR_Stackable_Motorshield::set_speed(uint8_t const speed) {
	Wire.beginTransmission(m_dev_address);
	Wire.write(SPEED_REG_ADR);
	Wire.write(speed);
	Wire.endTransmission();
}

/**
 * @brief reads the current speed
 */
int LXR_Stackable_Motorshield::get_speed() {
	Wire.beginTransmission(m_dev_address);
	Wire.write(SPEED_REG_ADR);
	Wire.endTransmission();
	delay(1);
	Wire.requestFrom(m_dev_address, (uint8_t)(2));
	return (int)(Wire.read());
}

/** 
 * @brief this function sets direction of the motor
 * @param dir direction of the motor (FWD, BWD)
 */
void LXR_Stackable_Motorshield::set_direction(E_DIRECTION const dir) {
	Wire.beginTransmission(m_dev_address);
	Wire.write(CONTROL_STATUS_REG_ADR);
	uint8_t data = 0x00;
    if(dir == FWD) data = 0x01;
	else if(dir == BWD) data = 0x02;
    Wire.write(data);
	Wire.endTransmission();
}

/**
 * @brief returns the current motor direction
 */
E_DIRECTION LXR_Stackable_Motorshield::get_direction() {
	Wire.beginTransmission(m_dev_address);
	Wire.write(CONTROL_STATUS_REG_ADR);
	Wire.endTransmission();
	delay(1);
	Wire.requestFrom(m_dev_address, (uint8_t)(2));
	uint8_t const reg_content = Wire.read();
	E_DIRECTION dir = BWD;
	if(reg_content & 0x01) dir = FWD;
	return dir;
}

/**
 * @brief enables the encoders
 */
void LXR_Stackable_Motorshield::enable_encoder() {
	Wire.beginTransmission(m_dev_address);
	Wire.write(CONTROL_STATUS_REG_ADR);
	uint8_t data = 0x04;
    Wire.write(data);
	Wire.endTransmission();
}
	
/**
 * @brief disables the encoders
 */
void LXR_Stackable_Motorshield::disable_encoder() {
	Wire.beginTransmission(m_dev_address);
	Wire.write(CONTROL_STATUS_REG_ADR);
	uint8_t data = 0x08;
    Wire.write(data);
	Wire.endTransmission();
}

/**
 * @brief returns true when the encoders are enabled, false otherwise
 */
bool LXR_Stackable_Motorshield::encoder_enabled() {
	Wire.beginTransmission(m_dev_address);
	Wire.write(CONTROL_STATUS_REG_ADR);
	Wire.endTransmission();
	delay(1);
	Wire.requestFrom(m_dev_address, (uint8_t)(2));
	uint8_t const reg_content = Wire.read();
	return (reg_content & 0x02);
}

/**
 * @brief read the encoder ticks measured at encoder 1 and reset the encoder counter in the process
 */
int LXR_Stackable_Motorshield::read_encoder_1() {
	Wire.beginTransmission(m_dev_address);
	Wire.write(ENCODER_1_LOW_REG_ADR);
	Wire.endTransmission();
	delay(1);
	Wire.requestFrom(m_dev_address, (uint8_t)(2));
	int const low_byte = (int)(Wire.read());
	int const high_byte = (int)(Wire.read());
	return ((high_byte<<8) + low_byte);
}
	
/**
 * @brief read the encoder ticks measured at encoder 1 and reset the encoder counter in the process
 */
int LXR_Stackable_Motorshield::read_encoder_2() {
	Wire.beginTransmission(m_dev_address);
	Wire.write(ENCODER_2_LOW_REG_ADR);
	Wire.endTransmission();
	delay(1);
	Wire.requestFrom(m_dev_address, (uint8_t)(2));
	int const low_byte = (int)(Wire.read());
	int const high_byte = (int)(Wire.read());
	return ((high_byte<<8) + low_byte);
}

/**
 * @brief turns the orange led on
 */
void LXR_Stackable_Motorshield::turn_orange_led_on() {
	Wire.beginTransmission(m_dev_address);
	Wire.write(CONTROL_STATUS_REG_ADR);
	uint8_t data = 0x10;
    Wire.write(data);
	Wire.endTransmission();
}
	
/**
 * @brief turns the orange led off
 */
void LXR_Stackable_Motorshield::turn_orange_led_off() {
	Wire.beginTransmission(m_dev_address);
	Wire.write(CONTROL_STATUS_REG_ADR);
	uint8_t data = 0x20;
    Wire.write(data);
	Wire.endTransmission();
}
