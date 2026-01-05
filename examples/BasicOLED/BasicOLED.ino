/*
  BasicOLED.ino - ロータリーエンコーダ + OLED 表示サンプル
  
  必要なライブラリ:
    - Adafruit GFX Library
    - Adafruit SSD1306
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RotaryEncoder.h"

/* OLED 設定 */
#define OLED_WIDTH   128
#define OLED_HEIGHT  64
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(
  OLED_WIDTH,
  OLED_HEIGHT,
  &Wire,
  -1
);

/* ロータリーエンコーダ ピン */
#define ENC_PIN_A 32
#define ENC_PIN_B 33

/* エンコーダオブジェクト */
RotaryEncoder encoder(ENC_PIN_A, ENC_PIN_B);

void setup() {
  // I2C初期化（ESP32の場合: SDA=21, SCL=22）
  Wire.begin(21, 22);
  
  // OLED初期化
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
  display.println("OK");
  display.display();
  
  // エンコーダ初期化
  encoder.begin();
}

void loop() {
  // エンコーダ更新
  encoder.poll();
  
  // 表示更新
  draw();
}

void draw() {
  static int lastValue = INT32_MIN;
  int currentValue = encoder.getValue();
  
  // 値が変わった時のみ更新
  if (currentValue == lastValue) return;
  lastValue = currentValue;
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 20);
  display.println(currentValue);
  display.display();
}
