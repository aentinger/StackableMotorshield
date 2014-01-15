/**
 * @author Alexander Entinger, MSc
 * @brief this module performs the readout of the encoder values - this module is written for quadrature wheel encoders - falling and rising edges are counted
 * @file encoder.h
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include <stdint.h>

/** 
 * @brief initializes the encoder module
 */
void init_encoder();

typedef enum {ENCODER_ON, ENCODER_OFF} E_ENCODER_STATE;
/**
 * @brief returns the encoder state
 */
E_ENCODER_STATE get_encoder_state();

/** 
 * @brief activates the encoder module
 */
void enable_encoder();

/** 
 * @brief disable encoder module
 */
void disable_encoder();

/** 
 * @brief read the value of the encoder 1 counter and clear the counter in the process
 */
uint16_t read_encoder_1();

/** 
 * @brief read the value of the encoder 2 counter and clear the counter in the process
 */
uint16_t read_encoder_2();


#endif /* ENCODER_H_ */