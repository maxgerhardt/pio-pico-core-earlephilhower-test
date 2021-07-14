#include <Arduino.h>
#if 0
int led = PIN_LED;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  Serial.println("Test");
//  delay(1000);
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(200);               // wait for a second
}
#endif 

#include <LittleFS.h>
#include <strings.h>

void setup() {
  Serial.begin(115200);
  delay(5000);
  LittleFS.begin();
  char buff[32];
  int cnt = 1;
  File f = LittleFS.open("counts.txt", "r");
  if (f) {
    bzero(buff, 32);
    if (f.read((uint8_t *)buff, 31)) {
      sscanf(buff, "%d", &cnt);
      Serial.printf("I have been run %d times\n", cnt);
    }
    f.close();
  }

  cnt++;
  sprintf(buff, "%d\n", cnt);
  f = LittleFS.open("counts.txt", "w");
  if (f) {
    f.write(buff, strlen(buff));
    f.close();
  }

  Serial.println("---------------");
  File i = LittleFS.open("file1.txt", "r");
  if (i) {
    while (i.available()) {
      Serial.write(i.read());
    }
    Serial.println("---------------");
    i.close();
  }
}


void loop() {
}
