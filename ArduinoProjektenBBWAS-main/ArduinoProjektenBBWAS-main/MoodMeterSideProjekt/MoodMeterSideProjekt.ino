#include <Arduino.h>

const int IO_BUTTON_UP = 4;
const int IO_BUTTON_DOWN = 7;
const int IO_LED_RGB_GREEN = 6;
const int IO_LED_RGB_RED = 9;
const int IO_LED_RGB_BLUE = 10;

enum Mood {
  SUNSET,
  COTTON_CANDY,
  DEFAULT_MOOD
};

Mood currentMood = DEFAULT_MOOD;

void setup() {
  pinMode(IO_BUTTON_DOWN, INPUT);
  pinMode(IO_BUTTON_UP, INPUT);

  // Set the LED pins as OUTPUT
  pinMode(IO_LED_RGB_GREEN, OUTPUT);
  pinMode(IO_LED_RGB_RED, OUTPUT);
  pinMode(IO_LED_RGB_BLUE, OUTPUT);
}

void setMoodColor(int red, int green, int blue) {
  analogWrite(IO_LED_RGB_RED, red);
  analogWrite(IO_LED_RGB_GREEN, green);
  analogWrite(IO_LED_RGB_BLUE, blue);
}

void cycleMood() {
  // Turn off the LEDs
  setMoodColor(0, 0, 0);

  // Cycle through moods
  if (currentMood == SUNSET) {
    setMoodColor(255, 150, 0); 
  } else if (currentMood == COTTON_CANDY) {
    setMoodColor(255, 105, 180); 
  } else {
    setMoodColor(255, 255, 255);
  }
}

void loop() {
  if (digitalRead(IO_BUTTON_DOWN) == HIGH) {
    currentMood = static_cast<Mood>((currentMood - 1 + DEFAULT_MOOD) % (DEFAULT_MOOD + 1));
    cycleMood();
    delay(500); 
  }

  if (digitalRead(IO_BUTTON_UP) == HIGH) {
    currentMood = static_cast<Mood>((currentMood + 1) % (DEFAULT_MOOD + 1));
    cycleMood();
    delay(500); 
  }
}
