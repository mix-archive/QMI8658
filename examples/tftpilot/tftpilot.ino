#include <Arduino.h>
#include "Wire.h"
#include "QMI8658.h"

#include "SPI.h"
#include "TFT_eSPI.h"

TFT_eSPI tft = TFT_eSPI();

QMI8658 qmi8658;
#define TFT_BACKLIGHT_PIN 45

void setup() {
  Serial.begin(115200);
  Wire.begin(14,2);
  if( qmi8658.begin()== 0){
    Serial.println("qmi8658_init fail");
  }

  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  pinMode( TFT_BACKLIGHT_PIN , OUTPUT);
  digitalWrite( TFT_BACKLIGHT_PIN, HIGH);
}


int _cnt = 0;
//图表初始位置
int _xc = 160;
int _yc = 160;
int _zc = 160;
float acc[3];
float gyro[3];

void loop() {

  qmi8658.read_xyz(acc,gyro);

  tft.fillRect( 60, 15, 100, 100, TFT_BLACK); //擦除上次的数字

  tft.setTextColor(TFT_RED);
  tft.setCursor(5, 15); tft.print("AcX:");
  tft.setCursor(60, 15); tft.print(acc[0]);
 
  tft.setTextColor(TFT_GREEN);
  tft.setCursor( 5, 45); tft.print( "AcY:");
  tft.setCursor(60, 45); tft.print(acc[1]);

  tft.setTextColor(TFT_BLUE);
  tft.setCursor( 5, 75); tft.print( "AcZ:");
  tft.setCursor(60, 75); tft.print(acc[2]);

    //绘制图表
  int x = int(acc[0]*10)+160;
  int y = int(acc[1]*10)+160;
  int z = int(acc[2]*10)+160;
  tft.drawLine(_cnt-1, _xc, _cnt, x, TFT_RED);
  tft.drawLine(_cnt-1, _yc, _cnt, y, TFT_GREEN);
  tft.drawLine(_cnt-1, _zc, _cnt, z, TFT_BLUE);
  _cnt++;

  _xc = x;
  _yc = y;
  _zc = z;
 //到达画面边缘时复位
 
  if(_cnt > 240){
    _cnt = 0;
    tft.fillScreen(TFT_BLACK);
  }

  delay(10);
}
 


  
