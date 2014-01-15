/**
 * @author Alexander Entinger, MSc
 * @brief this module performs the readout of the encoder values - this module is written for quadrature wheel encoders - falling and rising edges are counted
 * @file encoder.c
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#include "encoder.h"
#include "hal.h"
#include <avr/interrupt.h>

static volatile E_ENCODER_STATE m_encoder_state = ENCODER_OFF;
static volatile uint16_t enc1_counter = 0;
static volatile uint16_t enc2_counter = 0;

/** 
 * @brief initializes the encoder module
 */
void init_encoder() {
	// set both encoder input pins to inputs with activated pullups
	ENC1_PORT |= (1<<ENC1);
	ENC1_DDR &= ~(1<<ENC1);
	ENC2_PORT |= (1<<ENC2);
	ENC2_DDR &= ~(1<<ENC2);
	// count both rising and falling edges on both INT0 (ENC1) and INT1 (ENC2)
	EICRA |= (1<<ISC00) | (1<<ISC01);
	EICRA |= (1<<ISC10) | (1<<ISC11);
}

/**
 * @brief returns the encoder state
 */
E_ENCODER_STATE get_encoder_state() {
	return m_encoder_state;
}	

/** 
 * @brief activates the encoder module
 */
void enable_encoder() {
	EIMSK |= (1<<INT0) | (1<<INT1); 
	m_encoder_state = ENCODER_ON;
}

/** 
 * @brief disable encoder module
 */
void disable_encoder() {
	EIMSK &= ~((1<<INT0) | (1<<INT1)); 
	m_encoder_state = ENCODER_OFF;
}

/** 
 * @brief read the value of the encoder 1 counter and clear the counter in the process
 */
uint16_t read_encoder_1() {
	uint16_t const enc_1_ret = enc1_counter;
	enc1_counter = 0;
	return enc_1_ret;
}

/** 
 * @brief read the value of the encoder 2 counter and clear the counter in the process
 */
uint16_t read_encoder_2() {
	uint16_t const enc_2_ret = enc2_counter;
	enc2_counter = 0;
	return enc_2_ret;
}

/** 
 * @brief Interrupt Service Routine for external interrupt 0 (ENC1)
 */
ISR(INT0_vect) {
	enc1_counter++;
}

/** 
 * @brief Interrupt Service Routine for external interrupt 1 (ENC2)
 */
ISR(INT1_vect) {
	enc2_counter++;
}