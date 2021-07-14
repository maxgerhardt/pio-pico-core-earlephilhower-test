#include <Arduino.h>
int led = PIN_LED;

void setup() {
  pinMode(led, OUTPUT);
 // Serial.begin(115200);
}

void loop() {
//  Serial.println("Test");
//  delay(1000);
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}