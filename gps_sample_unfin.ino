// Interfacing Arduino with NEO-6M GPS module
 
#include <TinyGPS++.h>           // Include TinyGPS++ library
#include <SoftwareSerial.h>      // Include software serial library
#include  "LiquidCrystal_I2C.h"
#include <LibAPRS.h>


LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
TinyGPSPlus gps;
 
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
 
  while (SoftSerial.available() > 0) {
 
    if (gps.encode(SoftSerial.read())) {
 
      if (gps.location.isValid()) {
        Serial.print("Latitude   = ");
        Serial.println(gps.location.lat(), 6);
        Serial.print("Longitude  = ");
        Serial.println(gps.location.lng(), 6);
        lcd.setCursor(0, 0);
        lcd.print("Latitude=");
        lcd.print(gps.location.lat(), 6);
        lcd.setCursor(0, 1); 
        lcd.print("Longitude=");
        lcd.print(gps.location.lng(), 6);
        float lx=gps.location.lat();
        float ly=gps.location.lng();
        Serial.println(lx,3);
        Serial.println(ly,3);
        locationUpdate((lx),(ly));
      }
      else
        Serial.println("Location Invalid");
 
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
 
  }
 
}
char *ftoa(char *a, double f, int precision)
{
 long p[] = {0,10,100,1000,10000,100000,1000000,10000000,100000000};
 
 char *ret = a;
 long heiltal = (long)f;
 itoa(heiltal, a, 10);
 while (*a != '\0') a++;
 *a++ = '.';
 long desimal = abs((long)((f - heiltal) * p[precision]));
 itoa(desimal, a, 10);
 return ret;
}
void locationUpdate(float flat,float flon) {
  // Let's first set our latitude and longtitude.
  // These should be in NMEA format!


// flat, negative == Southern hemisphere
// flon, negative == western hemisphere
//  for instance...  43.646808, -116.286437  
//nmea then is:
//  43 .. (.646808*60),N
// 116 .. (.286437*60),W  (w since it was negative)
// APRS chokes when you send a ,N though... 
// it also chokes when you send more than 2 decimal places.

  int temp;
  char y[13];
  char z[13];

// CONVERT to NMEA.  
  if (flat<0){
     temp=-(int)flat;
     flat=temp*100 - (flat+temp)*60;
     ftoa((char*)&y,flat,3);   
     //z[10]=',';
     if (flat > 10000) {
       y[8]='S';
       y[9]=0;
     } else {
       y[7]='S';
       y[8]=0;
     }
  } else {
     temp=(int)flat;
     flat=temp*100 + (flat-temp)*60;
     ftoa((char*)&y,flat,3);      
     //z[10]=',';
     if (flat > 10000) {
       y[8]='N';
       y[9]=0;
     } else {
       y[7]='N';
       y[8]=0;
     }  
   }
     
   //APRS_setLat(y);
   
  Serial.println();
  Serial.println(F("Location Update:"));
  Serial.print(F("Lat: "));
 Serial.print(y);
  Serial.println();
  
  
  if (flon<0){
    temp=-(int)flon;
    flon=temp*100 - (flon+temp)*60;
    ftoa((char*)&z,flon,3);   
     //z[10]=',';
     if (flon > 10000){
       z[8]='W';
       z[9]=0;
     } else {
      z[7]='W';
      z[8]=0; 
     }
  } else {
    temp=(int)flon;
    flon=temp*100 + (flon-temp)*60;
    ftoa((char*)&z,flon,3);   
     //z[10]=',';
     if (flon > 10000){
       z[8]='E';
       z[9]=0;
     } else {
      z[7]='E';
      z[8]=0; 
     }
   Serial.print(z);
  Serial.println();
}}
