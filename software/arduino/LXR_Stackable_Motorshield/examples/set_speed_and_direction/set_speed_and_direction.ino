/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this arduino sketch implements the test code for testing tbe setting speed and direction functions of the stackable motorshield
 * @file set_speed_and_direction.ino
 * @license CC BY-NC-SA 3.0 ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */
 
#include <LXR_Stackable_Motorshield.h>
#include <Wire.h> // Important: Dont forget to include the Wire Library here too !

LXR_Stackable_Motorshield sm_0(0x57);
 
void setup() {
}

void loop() {
  
  // drive forward and continously increase speed
  sm_0.set_direction(FWD);
  for(int s=0; s<MAX_MOTOR_SPEED; s+=10) {
    sm_0.set_speed(s);
    delay(100);
  }
  // then reduce the speed to zero again
  for(int s=MAX_MOTOR_SPEED; s>0; s-=10) {
    sm_0.set_speed(s);
    delay(100);
  }
  // drive forward and continously increase speed
  sm_0.set_direction(BWD);
  for(int s=0; s<MAX_MOTOR_SPEED; s+=10) {
    sm_0.set_speed(s);
    delay(100);
  }
  // then reduce the speed to zero again
  for(int s=MAX_MOTOR_SPEED; s>0; s-=10) {
    sm_0.set_speed(s);
    delay(100);
  }
  // and then start from beginning
}
