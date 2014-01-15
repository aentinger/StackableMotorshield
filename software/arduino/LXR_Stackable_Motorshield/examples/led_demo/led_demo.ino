/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this arduino sketch implements the test code for testing the led turning on and off functionality
 * @file led_demo.ino
 * @license CC BY-NC-SA 3.0 ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */
 
#include <LXR_Stackable_Motorshield.h>
#include <Wire.h> // Important: Dont forget to include the Wire Library here too !

LXR_Stackable_Motorshield sm_0(0x57);
 
void setup() {
  sm_0.enable_encoder(); // enable the encoder output
}

void loop() {
  delay(1000);
  sm_0.turn_orange_led_on();  
  delay(1000);
  sm_0.turn_orange_led_off();
}

