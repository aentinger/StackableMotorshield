/**
 * @author Alexander Entinger, MSc
 * @brief this module is responsible for controlling the motor via the half bridge
 * @file motor_control.h
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include <stdint.h>

typedef enum {FWD, BWD} E_DIRECTION ;
static const uint8_t MAX_MOTOR_SPEED = 200;

/**
 * @brief initializes motor control
 */
void init_motor_control();

/** 
 * @brief this function sets direction of the motor
 * @param dir direction of the motor (FWD, BWD)
 */
void set_motor_direction(E_DIRECTION const dir);

/** 
 * @brief returns the current motor direction
 */
E_DIRECTION get_motor_direction();

/** 
 * @brief this function sets the speed of the motor
 * @param speed sets the speed of the motor (0 => stop(break), 200 => full speed)
 */
void set_motor_speed(uint8_t const speed);

/** 
 * @brief returns the current motor speed
 */
uint8_t get_motor_speed();


#endif /* MOTOR_CONTROL_H_ */