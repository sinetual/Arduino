#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

void setup() {
  matrix.begin(0x70);
}
static const uint8_t PROGMEM
    bigring_bmp[] =
    {
      B00011000,
      B00100100,
      B01000010,
      B10000001,
      B10000001,
      B01000010,
      B00100100,
      B00011000
    },
    mediumring_bmp[] =
    {
      B00000000,
      B00011000,
      B00100100,
      B01000010,
      B01000010,
      B00100100,
      B00011000,
      B00000000
    },
    smallring_bmp[] =
    {
      B00000000,
      B00000000,
      B00000000,
      B00011000,
      B00011000,
      B00000000,
      B00000000,
      B00000000,
    },
    biggerring_bmp[] =
    {
      B00100100,
      B01000010,
      B10000001,
      B00000000,
      B00000000,
      B10000001,
      B01000010,
      B00100100
    };

void drawLine(int x0, int y0, int x1, int y1) {
  int dx = abs(x1 - x0);
  int dy = -abs(y1 - y0);
  int sx = x0 < x1 ? 1 : -1;
  int sy = y0 < y1 ? 1 : -1;
  int err = dx + dy; /* error value e_xy */

  while (true) {
    matrix.drawPixel(x0, y0, 1);
    matrix.writeDisplay();
    delay(10);

    if (x0 == x1 && y0 == y1) {
      break;
    }

    int e2 = 2 * err;
    if (e2 >= dy) {
      err += dy; /* e_xy+e_x > 0 */
      x0 += sx;
    }
    if (e2 <= dx) {
      err += dx; /* e_xy+e_y < 0 */
      y0 += sy;
    }
  }
}

void loop() {
  matrix.clear();
int MAX = 8;
int MIN=1;
int ON = 1;

  // Draw diagonal line from (1,1) to (8,8)
  for (int i = 0; i <= 8; i++) {
    matrix.drawPixel(i, i, 1);
    matrix.writeDisplay();
    delay(100);
  }
  for (int i = 0; i <= 8; i++) {
    int x = 8 - i - 1; // reverse order
    int y = i;
    matrix.drawPixel(x, y, 1);
    matrix.writeDisplay();
    delay(100);
  }
  matrix.clear();
  
  for (int y = 0; y <= 7; y++) {
    matrix.drawPixel(7, y, 1);
    matrix.writeDisplay();
    delay(20);
  }
  // Draw line from (8,1) to (1,1)
  for (int x = 7; x >= 0; x--) {
    matrix.drawPixel(x, 7, 1);
    matrix.writeDisplay();
    delay(20);
  }
  for (int x = 7; x >= 0; x--) {
    matrix.drawPixel(0, x, 1);
    matrix.writeDisplay();
    delay(20);
  }
  for (int x = 0; x <= 7; x++) {
    matrix.drawPixel(x, 0, 1);
    matrix.writeDisplay();
    delay(20);
  }
  matrix.clear();
  drawLine(1, 1, 1, 6);
  drawLine(1, 6, 6, 6);
  drawLine(6, 6, 6, 1);
  drawLine(6, 1, 1, 1);
  matrix.clear();
  drawLine(2, 2, 2, 5);
  drawLine(2, 5, 5, 5);
  drawLine(5, 5, 5, 2);
  drawLine(5, 2, 2, 2);
  matrix.clear();
  drawLine(3, 3, 3, 4);
  drawLine(3, 4, 4, 4);
  drawLine(4, 4, 4, 3);
  matrix.clear();
  matrix.drawBitmap(0,0,smallring_bmp,8,8, ON);
      matrix.writeDisplay();
      delay(20);
      matrix.clear();
matrix.drawBitmap(0,0,mediumring_bmp, 8, 8, ON);
      matrix.writeDisplay();
      delay(20);
      matrix.clear();
matrix.drawBitmap(0,0,bigring_bmp,8,8, ON);
      matrix.writeDisplay();
      delay(20);
      matrix.clear();
  matrix.drawBitmap(0,0,biggerring_bmp,8,8, ON);
      matrix.writeDisplay();
      delay(20);
      matrix.clear();
  matrix.drawPixel(0,6,1);
  matrix.writeDisplay();
  matrix.drawPixel(1,7,1);
  matrix.writeDisplay();
  matrix.drawPixel(0,1,1);
  matrix.writeDisplay();
  matrix.drawPixel(1,0,1);
  matrix.writeDisplay();
  matrix.drawPixel(6,0,1);
  matrix.writeDisplay();
  matrix.drawPixel(7,1,1);
  matrix.writeDisplay();
  matrix.drawPixel(6,7,1);
  matrix.writeDisplay();
  matrix.drawPixel(7,6,1);
  matrix.writeDisplay();
  matrix.clear();
  delay(20);
  matrix.drawPixel(0,0,1);
  matrix.writeDisplay();
  matrix.drawPixel(0,7,1);
  matrix.writeDisplay();
  matrix.drawPixel(7,7,1);
  matrix.writeDisplay();
  matrix.drawPixel(7,0,1);
  matrix.writeDisplay();
  matrix.clear();
  delay(1000); // Optional delay between squares
}
