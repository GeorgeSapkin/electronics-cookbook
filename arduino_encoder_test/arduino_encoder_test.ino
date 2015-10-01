#include "enc_state.h"

// encoder signal has to be on interrupt pin 2 or 3 on Uno, etc.
#define ENC_RIGHT_SIG_PIN 2
#define ENC_LEFT_SIG_PIN  3
#define BOUD              9600

#define PRINT_DELAY 100
#define ENC_DELAY   25000

volatile EncState rightState = { ENC_RIGHT_SIG_PIN, 0, 0, 0 };
volatile EncState leftState  = { ENC_LEFT_SIG_PIN, 0, 0, 0 };

// shared between all ISRs, since only one is active at a time
volatile uint8_t prev;

void setup() {
  Serial.begin(BOUD);

  attachInterrupt(
    digitalPinToInterrupt(ENC_LEFT_SIG_PIN),
    onLeftEnc,
    CHANGE);

  attachInterrupt(
    digitalPinToInterrupt(ENC_RIGHT_SIG_PIN),
    onRightEnc,
    CHANGE);
}

unsigned long time = 0;

void loop() {
  if (millis() - time < PRINT_DELAY)
    return;

  Serial.print(leftState.count);
  Serial.print(' ');
  Serial.println(rightState.count);
  time = millis();
}

void onEnc(volatile EncState * encState) {
  // debounce interrupts
  if (micros() - encState->time < ENC_DELAY)
    return;

  prev = encState->sig;
  // read pin state directly from port D input pin register
  encState->sig = bitRead(PIND, encState->pin);
  if (prev == encState->sig)
    return;

  encState->time = micros();

  ++(encState->count);
}

void onRightEnc() {
  onEnc(&rightState);
}

void onLeftEnc() {
  onEnc(&leftState);
}
