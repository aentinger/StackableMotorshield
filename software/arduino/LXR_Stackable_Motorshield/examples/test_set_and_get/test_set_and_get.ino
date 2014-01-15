/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this arduino sketch implements the test code for testing the set and get functions of the stackable motorshield
 * @file Stackable_Motorshield_Test_3.ino
 * @license CC BY-NC-SA 3.0 ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */
 
#include <LXR_Stackable_Motorshield.h>
#include <Wire.h> // Important: Dont forget to include the Wire Library here too !

LXR_Stackable_Motorshield sm_0(0x57);
 
void setup() {
  randomSeed(analogRead(0)); // initialize random generator
  Serial.begin(115200); // serial interface to the pc
  
  Serial.println("Structure of test messages:\nEXP expected value / REAL received value");
  
  char buf[64]; int length = 0;
  
  sm_0.set_direction(FWD);
  if(sm_0.get_direction() == FWD) Serial.println("EXP: FWD / REAL:FWD");
  else Serial.println("EXP: FWD / REAL: BWD");
  
  sm_0.set_direction(BWD);
  if(sm_0.get_direction() == BWD) Serial.println("EXP: BWD / REAL:BWD");
  else Serial.println("EXP: BWD / REAL: FWD");
  
  sm_0.set_direction(FWD);
  if(sm_0.get_direction() == FWD) Serial.println("EXP: FWD / REAL:FWD");
  else Serial.println("EXP: FWD / REAL: BWD");

  uint8_t i = 0;
  for(; i<=MAX_MOTOR_SPEED; i+=10) {
    sm_0.set_speed(i);
    uint8_t const speed = sm_0.get_speed();
    length = sprintf(buf, "EXP %d / REAL %d\n", i, speed, sm_0.get_speed());
    Serial.write((uint8_t*)(&buf[0]), length);
    delay(100);
  }
  
  sm_0.enable_encoder();
  if(sm_0.encoder_enabled()) Serial.println("EXP: ENABLED / REAL: ENABLED");
  else Serial.println("EXP: ENABLED / REAL: DISABLED");
  
  sm_0.disable_encoder();
  if(!sm_0.encoder_enabled()) Serial.println("EXP: DISABLED / REAL: DISABLED");
  else Serial.println("EXP: DISABLED / REAL: ENABLED");
  
  sm_0.enable_encoder();
  if(sm_0.encoder_enabled()) Serial.println("EXP: ENABLED / REAL: ENABLED");
  else Serial.println("EXP: ENABLED / REAL: DISABLED");
}

void loop() {
 
}
