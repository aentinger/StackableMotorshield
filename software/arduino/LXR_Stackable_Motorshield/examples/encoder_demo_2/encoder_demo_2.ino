/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this arduino sketch implements the test code for testing the encoder function of the stackable motorshield in more detail
 * @file encoder_demo_2.ino
 * @license CC BY-NC-SA 3.0 ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */
 
#include <LXR_Stackable_Motorshield.h>
#include <Wire.h> // Important: Dont forget to include the Wire Library here too !

LXR_Stackable_Motorshield sm_0(0x57);
 
void setup() {
  randomSeed(analogRead(0)); // initialize random generator
  Serial.begin(115200); // serial interface to the pc
  sm_0.enable_encoder(); // enable the encoder output
}

void loop() {
  static uint8_t speed = 0;
  
  if(Serial.available()) speed = Serial.read(); // speed can be set via serial command - values from 0 to 200, otherwise result is un
  
  sm_0.set_speed(speed); // set the speed
  
  speed = sm_0.get_speed(); // read the speed back
  
  delay(1000); // sleep 1 s
  
  // read the encoder values
  int const enc1 = sm_0.read_encoder_1();
  int const enc2 = sm_0.read_encoder_2();
  
  // transmit them to the pc
  char buf[64];
  int const length = sprintf(buf, "Speed: %d, Encoder 1: %d, Encoder 2: %d\n", speed, enc1, enc2);
  Serial.write((uint8_t*)(&buf[0]), length);
}

