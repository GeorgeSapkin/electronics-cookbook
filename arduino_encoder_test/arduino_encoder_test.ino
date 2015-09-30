// encoder signal has to be on interrupt pin 2 or 3 on Uno, etc.
#define ENC_SIG_PIN 2
#define BOUD        9600

#define PRINT_DELAY 100
#define ENC_DELAY   25000

volatile long encCount = 0;

void setup() {
  Serial.begin(BOUD);

  attachInterrupt(
    digitalPinToInterrupt(ENC_SIG_PIN),
    onEnc,
    CHANGE);
}

unsigned long time = 0;

void loop() {
  if (millis() - time < PRINT_DELAY)
    return;

  Serial.println(encCount);
  time = millis();
}

volatile unsigned long encTime   = 0;
volatile uint8_t       encSignal = 0;
volatile uint8_t       encPrev   = 0;

void onEnc() {
  // debounce interrupts
  if (micros() - encTime < ENC_DELAY)
    return;

  encPrev   = encSignal;
  // read pin state directly from port D input pin register
  encSignal = bitRead(PIND, ENC_SIG_PIN);
  if (encPrev == encSignal)
    return;

  encTime = micros();

  encCount++;
}
