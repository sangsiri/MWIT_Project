/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This example shows how value can be pushed from Arduino to
  the Blynk App.

  WARNING :
  For this example you'll need Adafruit DHT sensor libraries:
    https://github.com/adafruit/Adafruit_Sensor
    https://github.com/adafruit/DHT-sensor-library

  App project setup:
    Value Display widget attached to V5
    Value Display widget attached to V6
 *************************************************************/

/* Comment this out to disable prints and save space */
void Line_Notify(String messages) ;
#include <Wire.h>                   // Include library
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1
Adafruit_SSD1306 OLED(OLED_RESET);  // New object OLED

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YOUR 's TOKEN KEY FROM Blynk App";
char ssid[] = "yourNetwork";
char pass[] = "secretPassword";

// Line config
#define LINE_TOKEN "LINE_TOKEN KEY"
 
#define DHTPIN 2            // What digital pin we're connected to D4

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11     // DHT 11
#define DHTTYPE DHT22       // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21     // DHT 21, AM2301
#define Relay1Pin D0        // Relay Pin
#define iGreenPin D5        // LED GREEN
#define iRedPin D6          // LED RED

int pinValue;            // PIN FROM Slider
int BH1750address = 0x23;   // Set BH1750 address
byte buff[2];

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();    // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  OLED.clearDisplay();                  //Clear display
  OLED.setTextColor(WHITE);             //Set text color
  OLED.setCursor(0, 0);                 //Set display start position
  OLED.setTextSize(2);                  //Set text size x1
  OLED.println("H:"+ String(h) + " %"); //Type message
  OLED.setCursor(0, 15);                //Set display postion
  OLED.println("t:"+ String(t) + " C"); // Show result value  
  
  uint16_t val = 0;
  BH1750_Init(BH1750address);             // Initial BH1750
  if (2 == BH1750_Read(BH1750address))    // Read and check data from BH1750
  {
    val = ((buff[0] << 8) | buff[1]) / 1.2;
    OLED.setCursor(0, 30);                //Set display postion
    OLED.println(String(val) + " lx");    // Show result value                                          
  }
  OLED.display();                         //Enable display
  
  if(val<pinValue){ // ถ้าค่าความเข้มแสงล่าสุดมีค่าน้อยกว่าค่าที่ตั้งไว้           
    digitalWrite(iGreenPin,HIGH);
    digitalWrite(iRedPin,LOW);
    digitalWrite(Relay1Pin,HIGH);          
    Serial.println("LED Turn on : ");
    String messages="LED Turn on : ";
    Line_Notify(messages);    
    
  }
  else if(val>=pinValue)  { // ถ้าค่าความเข้มแสงล่าสุดมีค่ามากกว่าหรือเท่ากับค่าที่ตั้งไว้
    digitalWrite(iGreenPin,LOW);
    digitalWrite(iRedPin,HIGH);
    digitalWrite(Relay1Pin,LOW);                     
    Serial.println("LED Turn off : ");    
    String messages="LED Turn off : ";
    Line_Notify(messages);    
  } 
    
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, val);
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin 0
BLYNK_WRITE(V0)
{
  pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V0 Slider value is: ");
  Serial.println(pinValue);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(iGreenPin,OUTPUT);
  digitalWrite(iGreenPin,LOW);
  pinMode(iRedPin,OUTPUT);
  digitalWrite(iRedPin,LOW);
  //########################
  pinMode(Relay1Pin,OUTPUT);
  digitalWrite(Relay1Pin,LOW);
  
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Blynk.begin(auth,ssid,pass);
  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}

int BH1750_Read(int address)              // BH1750 read data function
{
  int i = 0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while (Wire.available())
  {
    buff[i] = Wire.read();                // Read one byte
    i++;
  }
  Wire.endTransmission();
  return i;
}
void BH1750_Init(int address)             // BH1750 initial function
{
  Wire.beginTransmission(address);
  Wire.write(0x10);                       // Start operation
  Wire.endTransmission();
}

void Line_Notify(String messages) {
  WiFiClientSecure client;

  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;   
  }

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + messages).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + messages;
  // Serial.println(req);
  client.print(req);
    
  delay(20);

  // Serial.println("-------------");
  while(client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
    //Serial.println(line);
  }
  // Serial.println("-------------");
}

