
// Interfacing Arduino with NEO-6M GPS module
 
#include <TinyGPS++.h>           // Include TinyGPS++ library
#include <SoftwareSerial.h>      // Include software serial library
#include  "LiquidCrystal_I2C.h"


LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
TinyGPSPlus gps;
TinyGPSCustom gpgla(gps,"GPGLL",1);
TinyGPSCustom gpgns(gps,"GPGLL",2);
TinyGPSCustom gpglo(gps,"GPGLL",3);
TinyGPSCustom gpgew(gps,"GPGLL",4);


#define S_RX    4                // Define software serial RX pin
#define S_TX    3                // Define software serial TX pin
 
SoftwareSerial SoftSerial(S_RX, S_TX);    // Configure SoftSerial library
 
void setup(void) {
  Serial.begin(9600);
  SoftSerial.begin(9600); 
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
Serial.println(gpgla.value());
Serial.println(gpgns.value());
Serial.println(gpglo.value());
Serial.println(gpgew.value());
 
//   while (SoftSerial.available() > 0) {
// 
//    if (gps.encode(SoftSerial.read())) {
// 
//      if (gps.location.isValid()) {
//        Serial.print("Latitude   = ");
//        Serial.println(gps.location.lat(), 6);
//        Serial.print("Longitude  = ");
//        Serial.println(gps.location.lng(), 6);
//        lcd.setCursor(0, 0);
//        lcd.print("Latitude=");
//        lcd.print(gps.location.lat(), 6);
//        lcd.setCursor(0, 1); 
//        lcd.print("Longitude=");
//        lcd.print(gps.location.lng(), 6);
//      }
//      else
//        Serial.println("Location Invalid");
//    }
//   }
//      if (gps.altitude.isValid()) {
//        Serial.print("Altitude   = ");
//        Serial.print(gps.altitude.meters());
//        Serial.println(" meters");
//      }
//      else
//        Serial.println("Altitude Invalid");
// 
//      if (gps.speed.isValid()) {
//        Serial.print("Speed      = ");
//        Serial.print(gps.speed.kmph());
//        Serial.println(" kmph");
//      }
//      else
//        Serial.println("Speed Invalid");
// 
//      if (gps.time.isValid()) {
//        Serial.print("Time (GMT) : ");
//        if(gps.time.hour() < 10)     Serial.print("0");
//        Serial.print(gps.time.hour());
//        Serial.print(":");
//        if(gps.time.minute() < 10)   Serial.print("0");
//        Serial.print(gps.time.minute());
//        Serial.print(":");
//        if(gps.time.second() < 10)   Serial.print("0");
//        Serial.println(gps.time.second());
//      }
//      else
//        Serial.println("Time Invalid");
// 
//      if (gps.date.isValid()) {
//        Serial.print("Date       : ");
//        if(gps.date.day() < 10)      Serial.print("0");
//        Serial.print(gps.date.day());
//        Serial.print("/");
//        if(gps.date.month() < 10)    Serial.print("0");
//        Serial.print(gps.date.month());
//        Serial.print("/");
//        Serial.println(gps.date.year());
//      }
//      else
//        Serial.println("Date Invalid");
// 
//      if (gps.satellites.isValid()) {
//        Serial.print("Satellites = ");
//        Serial.println(gps.satellites.value());
//      }
//      else
//        Serial.println("Satellites Invalid");
 delay(1000);
    }
