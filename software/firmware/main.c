/**
* @author Alexander Entinger, MSc
* @brief main file for the stackable motor driver firmware
* @file main.c
* @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
*/

#include <avr/interrupt.h>
#include "motor_control.h"
#include "encoder.h"
#include "status_led_control.h"
#include "i2c.h"

/* PROTOTYPE SECTION */
void init_application();

int main(void) {
	
	init_application();
	
	for(;;) { // main working loop
		// loop forever	
	}
}

/**
 * @brief initializes the required peripherals
 */
void init_application() {
	
	init_motor_control();
	
	init_encoder();
	
	init_status_led_control();
	
	init_i2c();
		
	sei();
}