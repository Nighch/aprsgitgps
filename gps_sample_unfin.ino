#include "Wire.h"
#include  "LiquidCrystal_I2C.h"
#include "TinyGPS++.h"
#include "SoftwareSerial.h"
// 設定 LCD I2C 位址
// Set the pins on the I2C chip used for LCD connections:
// addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
SoftwareSerial serial_connection(10, 11); //RX=pin 10, TX=pin 11
TinyGPSPlus gps;//This is the GPS object that will pretty much do all the grunt work with the NMEA data

void setup() {
Serial.begin(115200);
serial_connection.begin(9600);
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
delay(8000);
lcd.clear(); //顯示清除
}
void loop() {
 while(serial_connection.available())//While there are characters to come from the GPS
{
  gps.encode(serial_connection.read());//This feeds the serial NMEA data into the library one char at a time
}
if(gps.location.isUpdated())
{
  lcd.setCursor(0, 0); // 設定游標位置在第一行行首
lcd.print(gps.location.lat(), 6);
lcd.setCursor(0, 1); // 設定游標位置在第二行行首
lcd.print(gps.satellites.value());
}

}
