#include <TridentTD_LineNotify.h>
///////////// include for GPS neo-6m /////////////
#include <TinyGPS++.h>
#include <HardwareSerial.h>

#define RXPin (21)
#define TXPin (19)

static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object /
TinyGPSPlus gps;

// The serial connection to the GPS device
HardwareSerial ss(2);

////////////// variable for Linenotify ////////////////
#define SSID        "******"                                     //ใส่ ชื่อ Wifi ที่จะเชื่อมต่อ
#define PASSWORD    "******"                                   //ใส่ รหัส Wifi
#define LINE_TOKEN  "******" //ใส่ รหัส TOKEN ที่ได้มาจากข้างบน

//////////////// Variable GPS NEO-6M ////////////////
float lat1 , long1 , lat2 ,long2 ;
char latchr[15], longchr[15] ;
String latstr1 , longstr1 ,latandlong1 ; 
String comma1 = "," ;
void setup() {
  Serial.begin(115200); 
  Serial.println();
  Serial.println(LINE.getVersion());

////////////// setup for GPS neo-6m //////////////
ss.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin, false);
Serial.println(TinyGPSPlus::libraryVersion());


  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());


}

void loop() {
while (ss.available() > 0)
if (gps.encode(ss.read()))
displayInfo();

Serial.print("Show Variable Latitude and longitude ") ;
Serial.println() ;
Serial.print(latchr);
Serial.print(F(","));
Serial.print(longchr);
Serial.print("\n") ;
////////////// change char to string //////////////////
for( int i=0;i<sizeof(latchr);i++){
   latstr1 += latchr[i] ;
}

for( int i=0;i<sizeof(longchr);i++){
   longstr1 += longchr[i] ;
}


Serial.print("Show Variable Latitude and longitude to string") ;
Serial.println() ;
Serial.print(latchr);
Serial.print(F(","));
Serial.print(longchr);
Serial.print("\n") ;


/////////////////////////  sum string  //////////////

latandlong1 = latstr1 + comma1 + longstr1 ;

if (millis() > 5000 && gps.charsProcessed() < 10)
{
Serial.println(F("No GPS detected: check wiring."));
while(true);
}

delay(3000) ;

 // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);

   // ตัวอย่างส่งข้อมูล ตัวเลข
  LINE.notify(latandlong1) ; 

  ///////////// delay for program send latitude longitude to line /////////////////
  delay(50000);
  ////////////// clear data string /////////////////
  latandlong1 = "" ;
  latstr1 = "" ;
  longstr1 = "" ;
}

////////////////// void displayInfo() //////////////////
void displayInfo()
{
Serial.print(F("Location: "));
if (gps.location.isValid())
{
Serial.print(gps.location.lat(), 6);
Serial.print(F(","));
Serial.print(gps.location.lng(), 6);

// change float and column //
  lat1  = gps.location.lat() ;
  long1 = gps.location.lng() ;

    dtostrf(lat1,8,6,latchr);
    dtostrf(long1,8,6,longchr);

}
else
{
Serial.print(F("INVALID"));
}

Serial.println();
}
