#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#define DHTPIN 2
#define DHTTYPE DHT11
#define SOIL A0
#define RELAY 7
DHT dht(DHTPIN, DHTTYPE);
int threshold = 500;
void setup() 
{
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}
void loop() {
  delay(2000);
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  int moisture = analogRead(SOIL);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Tempreature: ");
  display.print(t);
  display.println(" C");
  display.print("Humidity: ");
  display.print(h);
  display.println(" %");
  display.print("Soilmoist: ");
  display.println(moisture);

  if (moisture > threshold) {
    digitalWrite(RELAY, HIGH);
    display.println("Pump: ON");
  } else {
    digitalWrite(RELAY, LOW);
    display.println("Pump: OFF");
  }

  display.display();
}
