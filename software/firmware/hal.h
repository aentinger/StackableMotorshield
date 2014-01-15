/**
 * @author Alexander Entinger, MSc
 * @brief hardware abstraction layer file 
 * @file hal.h
 * @license Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#ifndef HAL_H_
#define HAL_H_

#include <avr/io.h>
#include <avr/portpins.h>

// output ports
#define INH_DDR			(DDRB)
#define INH_PORT		(PORTB)
#define INH				(1)

#define INLEFT_DDR		(DDRD)
#define INLEFT_PORT		(PORTD)
#define INLEFT			(6)

#define INRIGHT_DDR		(DDRB)
#define INRIGHT_PORT	(PORTB)
#define INRIGHT			(0)

#define LED_RED_DDR		(DDRD)
#define LED_RED_PORT	(PORTD)
#define LED_RED			(7)

#define LED_ORANGE_DDR	(DDRD)
#define LED_ORANGE_PORT	(PORTD)
#define LED_ORANGE		(5)

// input ports
#define ENC1_DDR		(DDRD)
#define ENC1_PORT		(PORTD)
#define ENC1			(2)

#define ENC2_DDR		(DDRD)
#define ENC2_PORT		(PORTD)
#define ENC2			(3)

#define I2C_ADR_BIT_0_DDR	(DDRC)
#define I2C_ADR_BIT_0_PORT	(PORTC)
#define I2C_ADR_BIT_0_PIN	(PINC)
#define I2C_ADR_BIT_0		(0)

#define I2C_ADR_BIT_1_DDR	(DDRC)
#define I2C_ADR_BIT_1_PORT	(PORTC)
#define I2C_ADR_BIT_1_PIN	(PINC)
#define I2C_ADR_BIT_1		(1)

#define I2C_ADR_BIT_2_DDR	(DDRC)
#define I2C_ADR_BIT_2_PORT	(PORTC)
#define I2C_ADR_BIT_2_PIN	(PINC)
#define I2C_ADR_BIT_2		(2)


#endif /* HAL_H_ */