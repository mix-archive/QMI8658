#include <Arduino.h>
#include "Wire.h"
#include "QMI8658.h"

#include "SPI.h"
#include "TFT_eSPI.h"
#define TFT_BACKLIGHT_PIN 45
TFT_eSPI tft = TFT_eSPI();

QMI8658 qmi8658;

float posX = 115;
float posY = 155;
float last_posX = posX;
float last_posY = posY;

void setup() {
  Serial.begin(115200);

  pinMode( TFT_BACKLIGHT_PIN , OUTPUT);
  digitalWrite( TFT_BACKLIGHT_PIN, HIGH);
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);  
  tft.setTextSize(1);
  tft.print("start...");

  Wire.begin(14,2);
  if( qmi8658.begin()== 0){
    Serial.println("qmi8658_init fail");
  }
}

void loop() {
  float pitch;
  float roll;
  float yaw;

  qmi8658.GetEulerAngles(&pitch,&roll, &yaw);

  Serial.print(pitch );Serial.print(" , " );
  Serial.print(roll );Serial.print(" , " );
  Serial.println(yaw );

  posX -= roll * 10;    // this is the speed; 10 is fast, 50 is slow
  posY += pitch * 10;

  posX = constrain(posX, 0, 230);
  posY = constrain(posY, 0, 310);

  tft.fillCircle(last_posX, last_posY, 10, TFT_BLACK);//擦除
  tft.fillCircle(posX, posY, 10, TFT_RED);

  last_posX = posX;
  last_posY = posY;
    
  delay(10);
}