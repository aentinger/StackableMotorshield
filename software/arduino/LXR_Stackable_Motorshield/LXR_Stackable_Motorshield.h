/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this module implements the library for controlling the LXRobotics Stackable Motorshield
 * @file LXR_Stackable_Motorshield.h
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */
 
 #ifndef LXR_STACKABLE_MOTORSHIELD_H_
 #define LXR_STACKABLE_MOTORSHIELD_H_
 
 #include "Arduino.h"
 
 typedef enum {FWD, BWD} E_DIRECTION ;
 static uint8_t const MAX_MOTOR_SPEED = 200;
 
 class LXR_Stackable_Motorshield {
 public:
	/**
	 * @brief Constructor
	 * @param dev_address stackable motorshield device address
	 */
	LXR_Stackable_Motorshield(uint8_t const dev_address);
		
	/** 
	 * @brief this function sets the speed of the motor
	 * @param speed sets the speed of the motor (0 => stop(break), 200 => full speed)
	 */
	void set_speed(uint8_t const speed);
	
	/**
	 * @brief reads the current speed
	 */
	int get_speed();
	
	/** 
	 * @brief this function sets direction of the motor
	 * @param dir direction of the motor (FWD, BWD)
	 */
	void set_direction(E_DIRECTION const dir);
	
	/**
	 * @brief returns the current motor direction
	 */
	E_DIRECTION get_direction();
	
	/**
	 * @brief enables the encoders
	 */
	void enable_encoder();
	
	/**
	 * @brief disables the encoders
	 */
	void disable_encoder();
	
	/**
	 * @brief returns true when the encoders are enabled, false otherwise
	 */
	bool encoder_enabled();
		
	/**
	 * @brief read the encoder ticks measured at encoder 1 and reset the encoder counter in the process
	 */
	int read_encoder_1();
	
	/**
	 * @brief read the encoder ticks measured at encoder 1 and reset the encoder counter in the process
	 */
	int read_encoder_2();
	
	/**
	 * @brief turns the orange led on
	 */
	void turn_orange_led_on();
	
	/**
	 * @brief turns the orange led off
	 */
	void turn_orange_led_off();
 
 private:
	uint8_t m_dev_address; 
 };
 
 #endif
