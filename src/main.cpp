#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3D

int PWM_Speed_Percent = 50;
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT); //Setup OLED

void setup() {
  Serial.begin(115200);
  OLED.clearDisplay();  	//clear OLED in case of restart/reset
  ledcSetup(0,25000, 10); //setup PWM on channel 0, 25kHz switching frequency, 10bit resolution (0-1024)
  ledcAttachPin(33, 0);   //Use GPIO33 as Output on channel 0
  pinMode(18, INPUT_PULLUP);  //pin for PWM Down
  pinMode(19, INPUT_PULLUP);  //pin for PWM Up
}

void loop() {
  ledcWrite(0, PWM_Speed_Percent*10.24);  //set PWM duty cycle in relation to the PWM_Speed_Percent int (Multiplyer = MaxResolution/100)
  OLED.clearDisplay();
  OLED.setCursor(0, 0);
  OLED.print("PWM Speed:");
  OLED.setCursor(1, 0);
  OLED.print(PWM_Speed_Percent + "%");  //print PWM Speed in Percent

  if(digitalRead(18) == 0){
    if(PWM_Speed_Percent >= 1){ //Percentage will not go below 0%
      PWM_Speed_Percent--;
    }
  }
  if(digitalRead(19) == 0){
    if(PWM_Speed_Percent <= 99){  //Percentage will not go above 100%
      PWM_Speed_Percent++;
    }
  }
  vTaskDelay(500 / portTICK_PERIOD_MS); //Delay is required to make the OLED more readable and Button Inputs con be used in a more precise way
}