/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this arduino sketch implements the test code for testing the encoder function of the stackable motorshield
 * @file encoder_demo_1.ino
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
  static int speed = 20;
  int const speed_offset = random(-20,20);
  speed += speed_offset;
  
  if(speed > MAX_MOTOR_SPEED) speed = MAX_MOTOR_SPEED;
  else if(speed < 0) speed = 0;
  
  sm_0.set_speed((uint8_t)(speed));
  
  delay(1000); // sleep 1 s
  
  // read the encoder values
  int const enc1 = sm_0.read_encoder_1();
  int const enc2 = sm_0.read_encoder_2();
  
  // transmit them to the pc
  char buf[64];
  int const length = sprintf(buf, "Speed: %d, Encoder 1: %d, Encoder 2: %d\n", speed, enc1, enc2);
  Serial.write((uint8_t*)(&buf[0]), length);
}
