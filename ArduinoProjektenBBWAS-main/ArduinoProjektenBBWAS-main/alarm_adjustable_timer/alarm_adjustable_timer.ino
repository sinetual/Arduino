#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

const int IO_RX = 0;
const int IO_TX = 1;
const int IO_IR_REC = 2;
const int IO_IR_SEND = 3;
const int IO_BUTTON_UP = 4;
const int IO_BUZZER = 5;
const int IO_LED_RGB_GREEN = 6;
const int IO_BUTTON_DOWN = 7;
const int IO_LED_GREEN = 8;
const int IO_LED_RGB_RED = 9;
const int IO_SERVO_1 = 9;
const int IO_SERVO_2 = 10;
const int IO_LED_RGB_BLUE = 10;
const int IO_LED_CENTER = 11;
const int IO_LED_YELLOW = 12;
const int IO_LED_RED = 13;

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();
int Timer = 0;
int alarmDurationInSeconds = 32400; 
int remainingHours = alarmDurationInSeconds / 3600;

void displayRemainingTime(int remainingHours) {
  matrix.clear();
  matrix.setCursor(0, 0);
  matrix.print(remainingHours);
  matrix.writeDisplay();
}

void playAlarm() {
  tone(IO_BUZZER, 1000, 2000);
  delay(2000);
  noTone(IO_BUZZER);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Alarm Clock Setup");

  pinMode(IO_LED_GREEN, OUTPUT);
  pinMode(IO_LED_YELLOW, OUTPUT);
  pinMode(IO_LED_RED, OUTPUT);
  pinMode(IO_LED_CENTER, OUTPUT);

  pinMode(IO_BUTTON_UP, INPUT);
  pinMode(IO_BUTTON_DOWN, INPUT);

  matrix.begin(0x70);
  matrix.setBrightness(15); 
  matrix.clear(); 
  matrix.writeDisplay();

  pinMode(IO_BUZZER, OUTPUT);
}

void loop() {
  int ON = 1;
  int OFF = 0;
  digitalWrite(IO_LED_RED, OFF);
  digitalWrite(IO_LED_YELLOW, OFF);
  digitalWrite(IO_LED_GREEN, OFF);
  digitalWrite(IO_LED_CENTER, OFF);

  if (digitalRead(IO_BUTTON_UP) == 1) {
    if (digitalRead(IO_BUTTON_DOWN) == 1) {
      digitalWrite(IO_LED_GREEN, ON);
    } else {
      digitalWrite(IO_LED_RED, ON);

      alarmDurationInSeconds = alarmDurationInSeconds + 3600;
      remainingHours = alarmDurationInSeconds / 3600;
      displayRemainingTime(remainingHours);
    }
  } else if (digitalRead(IO_BUTTON_DOWN) == 1) {
    digitalWrite(IO_LED_YELLOW, ON);

    if (alarmDurationInSeconds > 3600) {
      alarmDurationInSeconds = alarmDurationInSeconds - 3600;
      remainingHours = alarmDurationInSeconds / 3600;
      displayRemainingTime(remainingHours);
    }
    delay(500); 
  } else {
    digitalWrite(IO_LED_CENTER, ON);
  }
  delay(200);
  displayRemainingTime(remainingHours);
  if (Timer < alarmDurationInSeconds) {
    delay(1000);
    Timer++;
    remainingHours = (alarmDurationInSeconds - Timer) / 3600;
  } else {
    Serial.println("Alarm!");
    playAlarm();
    delay(60000); 
    Timer = 0;
  }
}

