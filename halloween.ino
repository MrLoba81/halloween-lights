#include <avr/io.h>
#include <avr/interrupt.h>

#define N_STATUSES (uint8_t)2
#define YELLOW (uint8_t)0
#define RED_R (uint8_t)1
#define RED_L (uint8_t)4
#define BTN_PIN (uint8_t)3
#define EXT_BLINK_LED (uint8_t)2

#define adc_disable() (ADCSRA &= ~(1<<ADEN)) // disable ADC

volatile boolean interrupted = false;
uint8_t status = 0;
unsigned long lastDebounceTime = 0;

static inline void initInterrupt(void)
{
  GIMSK |= (1 << PCIE);   // pin change interrupt enable
  PCMSK |= (1 << PCINT3); // pin change interrupt enabled for PCINT3
  sei();                  // enable interrupts
}

ISR(PCINT0_vect)
{
  unsigned long currTime = millis();
  //debounce the press
  if (currTime - lastDebounceTime > 500) {
    interrupted = true;
    lastDebounceTime = currTime;
  }
}

void setup() {
  pinMode(YELLOW, OUTPUT);
  pinMode(RED_R, OUTPUT);
  pinMode(RED_L, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(EXT_BLINK_LED, OUTPUT); 

  adc_disable();

  initInterrupt();
}

void loop() {
  if (interrupted) { // manage the interrup due to pushbutton press
    status = ((status + 1) % N_STATUSES);
    interrupted = false;
  }

  switch (status) {
    case 0:
      flicker();
      break;
    case 1:
      breathe();
      break;
  }
}

void breathe() {
  static boolean isBlow = true;
  static unsigned long lastCheckTime = 0;
  static uint8_t counter = 9;

  unsigned long currTime = millis();

  if (currTime - lastCheckTime >= 10) {
    if (isBlow) {
      if (++counter == 255) isBlow = false;
    } else {
      if (--counter == 10) isBlow = true;
    }
    analogWrite(YELLOW, counter);
    analogWrite(RED_R, counter - 10);
    analogWrite(RED_L, counter - 10);

    lastCheckTime = currTime;
  }

  //Simulation of PWM
  digitalWrite(EXT_BLINK_LED, HIGH);
  delayMicroseconds(counter - 10);
  digitalWrite(EXT_BLINK_LED, LOW);
  delayMicroseconds(255 - counter + 10); 
}

void flicker() {
  analogWrite(YELLOW, random(10, 255));
  delay(20);
  analogWrite(RED_R, random(1, 150));
  delay(20);
  analogWrite(RED_L, random(1, 150));
  delay(20);

  // Simulation of PWM: Approximately 1%/5% duty cicle @ ~60/63Khz (3 x delay(20) + random(600, 3000))
  digitalWrite(EXT_BLINK_LED, HIGH);
  delayMicroseconds(random(600, 3000));
  digitalWrite(EXT_BLINK_LED, LOW);
}
