#include <Wire.h>

#define LED_PIN       13
#define SLAVE_ADDRESS 0x07

int number = 0;
int state  = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);

  // initialize i2c
  Wire.begin(SLAVE_ADDRESS);

  // define i2c callbacks
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}

void loop() {
  delay(100);
}

// callback for received data
void receiveData(const int byteCount) {
  while (Wire.available()) {
    number = Wire.read();

    if (number == 1) {
      if (state == 0) {
        // turn LED on
        digitalWrite(LED_PIN, HIGH);
        state = 1;
      }
      else {
        // turn LED off
        digitalWrite(LED_PIN, LOW);
        state = 0;
      }
    }
  }
}

// callback for sending data
void sendData() {
  Wire.write(number);
}


