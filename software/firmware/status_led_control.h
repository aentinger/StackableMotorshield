/**
 * @author Alexander Entinger, MSc
 * @brief this module implements the control of the two status leds
 * @file status_led_control.h
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#ifndef STATUS_LED_CONTROL_H_
#define STATUS_LED_CONTROL_H_

/** 
 * @brief initializes the modul
 */
void init_status_led_control();

/** 
 * @brief turns red led on
 */
void red_led_on();

/** 
 * @brief turns red led off
 */
void red_led_off();

/** 
 * @brief turns the orange status led on
 */
void orange_led_on();

/** 
 * @brief turns the orange status led off
 */
void orange_led_off();

#endif /* STATUS_LED_CONTROL_H_ */