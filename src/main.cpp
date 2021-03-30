#include <Arduino.h>
#include <SSD1306Wire.h>

#define OLED_ADDR   0x3c  //Addres of the OLED-Module
#define OLED_SDA    21  //GPIO used for I²C SDA
#define OLED_SCL    22  //GPIO used for I²C SCL


SSD1306Wire display(OLED_ADDR, OLED_SDA, OLED_SCL); //Setup Object to control OLED

int PWM_Speed_Percent = 50; //PWM Speed used on startup/restart


void setup() {
  Serial.begin(115200);
  //OLED.clearDisplay();  	//clear OLED in case of restart/reset
  ledcSetup(0,25000, 10); //setup PWM on channel 0, 25kHz switching frequency, 10bit resolution (0-1024)
  ledcAttachPin(33, 0);   //Use GPIO33 as Output on channel 0
  pinMode(18, INPUT_PULLUP);  //pin for PWM Down
  pinMode(19, INPUT_PULLUP);  //pin for PWM Up
  display.init();  //Initialize OLED
  display.flipScreenVertically();  //rotate the OLED by 180° (to normal oriantation)
  display.setFont(ArialMT_Plain_16); //set Font and Size
}

void loop() {
  ledcWrite(0, PWM_Speed_Percent*10.24);  //set PWM duty cycle in relation to the PWM_Speed_Percent int (Multiplyer = MaxResolution/100)
  display.clear();  //clear OLED
  display.drawString(0, 0, "PWM Fan Speed");       
  display.drawString(30, 20, String(PWM_Speed_Percent) + " %");
  display.display();  //prints the above Strings on the OLED

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
  vTaskDelay(100 / portTICK_PERIOD_MS);
}