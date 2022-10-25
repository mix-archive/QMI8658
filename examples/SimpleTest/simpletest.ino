#include <Arduino.h>
#include "Wire.h"
#include "QMI8658.h"

QMI8658 qmi8658;

void setup() {
  Serial.begin(115200);
  Wire.begin(14,2);
  if( qmi8658.begin()== 0){
    Serial.println("qmi8658_init fail");
  }
}

void loop() {
  float acc[3];
  float gyro[3];  
  qmi8658.read_xyz(acc,gyro);
  for(int i= 0;i <3;i++){
    Serial.print(acc[i] );
    Serial.print("," );
  }
  for(int i= 0;i < 2;i++){
    Serial.print(gyro[i] );
    Serial.print("," );
  }
  Serial.println(gyro[2] );
  delay(100);
}