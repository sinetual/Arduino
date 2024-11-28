#include <Arduino.h>

const int IO_BUZZER = 5;

void playStarWarsTheme() {
  int melody[] = {
    440, 440, 440, 349, 523, 440, 349, 523, 440, 0, 659, 659, 659, 698, 523, 415,
    349, 523, 440, 0, 523, 523, 523, 587, 659, 523, 587, 659, 0, 880, 880, 880,
    784, 659, 523, 440, 349, 523, 440, 0, 349, 349, 349, 415, 523, 349, 523, 440
  };

  int noteDuration = 250;

  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    if (melody[i] == 0) {
      noTone(IO_BUZZER);
    } else {
      tone(IO_BUZZER, melody[i], noteDuration);
      delay(noteDuration * 1.5); 
    }
  }
}

void setup() {
  pinMode(IO_BUZZER, OUTPUT);
}

void loop() {
  playStarWarsTheme();
  delay(2000); 
}
