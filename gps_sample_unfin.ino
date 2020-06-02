#include <TinyGPS++.h>           // Include TinyGPS++ library
#include <SoftwareSerial.h>      // Include software serial library
#include  "LiquidCrystal_I2C.h"
#include <LibAPRS.h>


LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
TinyGPSPlus gps;


#define ADC_REFERENCE REF_3V3
#define OPEN_SQUELCH false
#define S_RX    4                // Define software serial RX pin
#define S_TX    3                // Define software serial TX pin
boolean gotPacket = false;
AX25Msg incomingPacket;
uint8_t *packetData;

SoftwareSerial SoftSerial(S_RX, S_TX);    // Configure SoftSerial library

void aprs_msg_callback(struct AX25Msg *msg) {
  if (!gotPacket) {
    gotPacket = true;
    memcpy(&incomingPacket, msg, sizeof(AX25Msg));
    if (freeMemory() > msg->len) {
      packetData = (uint8_t*)malloc(msg->len);
      memcpy(packetData, msg->info, msg->len);
      incomingPacket.info = packetData;
    } else {

      gotPacket = false;
    }
  }
}


void setup(void) {
  APRS_init(ADC_REFERENCE, OPEN_SQUELCH);
  APRS_setCallsign("NOCALL", 1);
  APRS_printSettings();
  Serial.print(F("Free RAM:     ")); Serial.println(freeMemory());
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



void locationUpdate(float flat,float flon) {
  int temp;
  char y[13];
  char z[13];
  
// CONVERT to NMEA.  
  if (flat<0){
     temp=-(int)flat;
     flat=temp*100 - (flat+temp)*60;
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
     //z[10]=',';
     if (flat > 10000) {
       y[8]='N';
       y[9]=0;
     } else {
       y[7]='N';
       y[8]=0;
     }  
   }
     
   APRS_setLat(y);
   
  Serial.println();
  Serial.println(F("Location Update:"));
  Serial.print(F("Lat: "));
  Serial.println(y);
  
  if (flon<0){
    temp=-(int)flon;
    flon=temp*100 - (flon+temp)*60;
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
     //z[10]=',';
     if (flon > 10000){
       z[8]='E';
       z[9]=0;
     } else {
      z[7]='E';
      z[8]=0; 
     }
}

    APRS_setLon(z);
  Serial.print(F("Lon:"));
  Serial.println(z);
  char *comment = " JWAprsTrkr";
  APRS_sendLoc(comment, strlen(comment));
}


void messageExample() {
  // We first need to set the message recipient
  APRS_setMessageDestination("AA3BBB", 0);
  
  // And define a string to send
  char *message = "Hi there! This is a message.";
  APRS_sendMsg(message, strlen(message));
  
}

void processPacket() {
  if (gotPacket) {
    gotPacket = false;
    
    Serial.print(F("Received APRS packet. SRC: "));
    Serial.print(incomingPacket.src.call);
    Serial.print(F("-"));
    Serial.print(incomingPacket.src.ssid);
    Serial.print(F(". DST: "));
    Serial.print(incomingPacket.dst.call);
    Serial.print(F("-"));
    Serial.print(incomingPacket.dst.ssid);
    Serial.print(F(". Data: "));

    for (int i = 0; i < incomingPacket.len; i++) {
      Serial.write(incomingPacket.info[i]);
    }
    Serial.println("");

    // Remeber to free memory for our buffer!
    free(packetData);
    
    // Serial.print(F("Free RAM: ")); Serial.println(freeMemory());
  }
}

boolean whichExample = false;


void loop() {

   while (SoftSerial.available() > 0) {
 
    if (gps.encode(SoftSerial.read())) {
 
      if (gps.location.isValid()) {
         if (whichExample) {
        locationUpdate((gps.location.lat(), 6),(gps.location.lng(), 6));
        } else {
         messageExample();
        }
        whichExample ^= true;
        delay(500);
        processPacket();

        
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
      }
      else
        Serial.println("Location Invalid");
    }
   }
 delay(1000);
    }
