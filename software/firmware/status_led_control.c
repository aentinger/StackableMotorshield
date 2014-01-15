/**
 * @author Alexander Entinger, MSc
 * @brief this module implements the control of the two status leds
 * @file status_led_control.c
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#include "status_led_control.h"
#include "hal.h"
#include <avr/interrupt.h>
#include <stdbool.h>

/** 
 * @brief initializes the modul
 */
void init_status_led_control() {
	// turn the led ports to output ports, leds are off
	LED_RED_PORT |= (1<<LED_RED);
	LED_RED_DDR |= (1<<LED_RED);
	LED_ORANGE_PORT |= (1<<LED_ORANGE);
	LED_ORANGE_DDR |= (1<<LED_ORANGE);	
}

/** 
 * @brief turns red led on
 */
void red_led_on() {
	LED_RED_PORT &= ~(1<<LED_RED);
}

/** 
 * @brief turns red led off
 */
void red_led_off() {
	LED_RED_PORT |= (1<<LED_RED);
}

/** 
 * @brief turns the orange status led on
 */
void orange_led_on() {
	LED_ORANGE_PORT &= ~(1<<LED_ORANGE);	
}

/** 
 * @brief turns the orange status led off
 */
void orange_led_off() {
	LED_ORANGE_PORT |= (1<<LED_ORANGE);	
}