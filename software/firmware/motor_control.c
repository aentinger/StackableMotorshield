/**
* @author Alexander Entinger, MSc
* @brief this module is responsible for controlling the motor via the half bridge
* @file motor_control.c
* @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
*/

#include "motor_control.h"
#include "hal.h"
#include <avr/interrupt.h>
#include <stdbool.h>

typedef struct {
	E_DIRECTION direction;
	uint8_t speed;
} s_motor_params;
static volatile s_motor_params motor_params = {FWD, 0};

/**
 * @brief initializes motor control
 */
void init_motor_control() {
	INLEFT_PORT &= ~(1<<INLEFT); // and there value to zero which leads to both halfbridges activate their low side switch only (break)
	INLEFT_DDR |= (1<<INLEFT); // set both inleft and inright to output ports
	INRIGHT_PORT &= ~(1<<INRIGHT);
	INRIGHT_DDR |= (1<<INRIGHT); 
	
	INH_PORT |= (1<<INH); // set /INH to output and high
	INH_DDR |= (1<<INH); // thus activating the half bridge
	
	TCNT0 = 0; // reset the tcnt register
	TIMSK0 |= (1<<TOIE0); // enable timer 0 overflow interrupt
	TCCR0B |= (1<<CS01); // prescaler = 8 => 1 Timerstep @ 16 MHz = 500 ns, 200 Timersteps = 100 us => 10 kHz PWM Frequency	
}

/** 
 * @brief this function sets direction of the motor
 * @param dir direction of the motor (FWD, BWD)
 */
void set_motor_direction(E_DIRECTION const dir) {
	motor_params.direction = dir;
}

/** 
 * @brief returns the current motor direction
 */
E_DIRECTION get_motor_direction() {
	return motor_params.direction;
}

/** 
 * @brief this function sets the speed of the motor
 * @param speed sets the speed of the motor (0 => stop(break), 200 => full speed)
 */
void set_motor_speed(uint8_t const speed) {	
	if(speed > MAX_MOTOR_SPEED) motor_params.speed = MAX_MOTOR_SPEED;
	else motor_params.speed = speed;
}

/** 
 * @brief returns the current motor speed
 */
uint8_t get_motor_speed() {
	return motor_params.speed;
}

/** 
 * @brief Timer 0 ISR
 */
ISR(TIMER0_OVF_vect) {
	static bool halfbridge_highside_active = false;
	
	if(motor_params.speed > 0) {

		/* ACTIVATE LOWSIDE DEPENDING ON THE DIRECTION */
		if(motor_params.direction == FWD) {
			INRIGHT_PORT &= ~(1<<INRIGHT); // lowside of right half bridge is constantly activated
		} else if(motor_params.direction == BWD) {
			INLEFT_PORT &= ~(1<<INLEFT); // lowside of left half bridge is constantly activated
		}

		/* TOOGLE HIGHSIDE DEPENDING ON THE DIRECTION */
		if(halfbridge_highside_active) {
			if(motor_params.direction == FWD) INLEFT_PORT |= (1<<INLEFT); // activate highside
			else if(motor_params.direction == BWD) INRIGHT_PORT |= (1<<INRIGHT); // activate highside
			halfbridge_highside_active = false;
			TCNT0 = 0xFF - motor_params.speed;
			} else {
			if(motor_params.direction == FWD) INLEFT_PORT &= ~(1<<INLEFT); // deactivate highside
			else if(motor_params.direction == BWD) INRIGHT_PORT &= ~(1<<INRIGHT); // deactivate highside
			halfbridge_highside_active = true;
			TCNT0 = 0xFF - (MAX_MOTOR_SPEED - motor_params.speed);
		}

	} else {
		INLEFT_PORT &= ~(1<<INLEFT);
		INRIGHT_PORT &= ~(1<<INRIGHT);	
	}
}