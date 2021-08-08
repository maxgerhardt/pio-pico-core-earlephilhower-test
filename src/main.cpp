#ifdef NO_USB
/* hardware UART*/
#define SERIAL_TO_USE Serial1
#else
/* USB */
#define SERIAL_TO_USE Serial
#endif
/* change to 1 to run blinky demo, change to 0 for LittleFS demo */
#if 1
#include <Arduino.h>
int led = PIN_LED;

void setup() {
  pinMode(led, OUTPUT);
  SERIAL_TO_USE.begin(115200);
}

void loop() {
  SERIAL_TO_USE.println("Test");
  digitalWrite(led, HIGH);   // turn the LED on
  delay(200);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off
  delay(200);               // wait for a second
}

#else
#include <LittleFS.h>
#include <strings.h>

void setup() {
  SERIAL_TO_USE.begin(115200);
  delay(5000);
  LittleFS.begin();
  char buff[32];
  int cnt = 1;
  File f = LittleFS.open("counts.txt", "r");
  if (f) {
    bzero(buff, 32);
    if (f.read((uint8_t *)buff, 31)) {
      sscanf(buff, "%d", &cnt);
      SERIAL_TO_USE.printf("I have been run %d times\n", cnt);
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

  SERIAL_TO_USE.println("---------------");
  File i = LittleFS.open("file1.txt", "r");
  if (i) {
    while (i.available()) {
      SERIAL_TO_USE.write(i.read());
    }
    SERIAL_TO_USE.println("---------------");
    i.close();
  }
}


void loop() {
}
#endif