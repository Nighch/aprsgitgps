#include "Wire.h"
#include  "LiquidCrystal_I2C.h"
#include "TinyGPS++.h"
#include "SoftwareSerial.h"
// 設定 LCD I2C 位址
// Set the pins on the I2C chip used for LCD connections:
// addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
SoftwareSerial ss(4,3);


void setup() {
Serial.begin(9600);
ss.begin(9600);
Serial.println("GPS Start");
// 初始化 LCD，一行 16 的字元，共 2 行，預設開啟背光
lcd.begin(16, 2);

// 閃爍三次
lcd.backlight();

// 輸出初始化文字
lcd.setCursor(0, 0); // 設定游標位置在第一行行首
lcd.print("Maker_Nighch&Bee");
delay(1000);
lcd.setCursor(0, 1); // 設定游標位置在第二行行首
lcd.print("GPS START");
delay(3000);
lcd.clear(); //顯示清除

}
void loop() {
 while (ss.available() > 0){
   byte gpsData = ss.read();
    Serial.write(gpsData);
    lcd.print(gpsData);
  }
 
// lcd.setCursor(0, 0); // 設定游標位置在第一行行首
//lcd.print(gps.location.lat(), 6);
//lcd.setCursor(0, 1); // 設定游標位置在第二行行首
////lcd.print(gps.satellites.value());
//lcd.print(gps.read());
delay(1000);
lcd.clear();

}
