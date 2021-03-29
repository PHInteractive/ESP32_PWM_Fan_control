#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3D

int PWM_Speed_Percent = 50;
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT);

void setup() {
  Serial.begin(115200);
  OLED.clearDisplay();
  ledcSetup(0,25000, 10);
  ledcAttachPin(33, 0);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
}

void loop() {
  ledcWrite(0, PWM_Speed_Percent*10.24);
  OLED.clearDisplay();
  OLED.setCursor(0, 0);
  OLED.print("PWM Speed:");
  OLED.setCursor(1, 0);
  OLED.print(PWM_Speed_Percent + "%");

  if(digitalRead(18) == 0){
    if(PWM_Speed_Percent >= 1){
      PWM_Speed_Percent--;
    }
  }
  if(digitalRead(19) == 0){
    if(PWM_Speed_Percent <= 99){
      PWM_Speed_Percent++;
    }
  }
  vTaskDelay(500 / portTICK_PERIOD_MS);
}