#include <SPI.h>
#include <TFT_eSPI.h>
#include "DHTesp.h" 

TFT_eSPI tft = TFT_eSPI();

DHTesp dht;

float temperature = 0;
float humidity = 0;
float lastTemp = 0;
float lastHumid = 0;

unsigned long lastUpdateTime = 0;
const long updateInterval = 2000;  

#define BACKGROUND TFT_BLACK
#define TEXT_COLOR TFT_WHITE
#define TEMP_COLOR TFT_RED
#define HUMID_COLOR TFT_BLUE
#define BORDER_COLOR TFT_GREEN

void setup() {
  Serial.begin(115200);
  Serial.println("DHT11 and ST7789 Display Demo");

  dht.setup(D3, DHTesp::DHT11);

  tft.init();
  tft.setRotation(0);
  tft.fillScreen(BACKGROUND);

  drawStaticElements();

  Serial.println("Setup complete");
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastUpdateTime >= updateInterval) {
    lastUpdateTime = currentTime;

    delay(dht.getMinimumSamplingPeriod());

    humidity = dht.getHumidity();
    temperature = dht.getTemperature();

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Failed to read from DHT sensor!");

      tft.setTextColor(TFT_RED, BACKGROUND);
      tft.setTextSize(1);
      tft.setCursor(20, 200);
      tft.println("Sensor read error!");
      return;
    }

    if (temperature != lastTemp || humidity != lastHumid) {
      updateDisplay();
      lastTemp = temperature;
      lastHumid = humidity;
    }

    Serial.print(dht.getStatusString());
    Serial.print("\t");
    Serial.print(humidity, 1);
    Serial.print("\t\t");
    Serial.print(temperature, 1);
    Serial.print("\t\t");
    Serial.print(dht.toFahrenheit(temperature), 1);
    Serial.print("\t\t");
    Serial.print(dht.computeHeatIndex(temperature, humidity, false), 1);
    Serial.print("\t\t");
    Serial.println(dht.computeHeatIndex(dht.toFahrenheit(temperature), humidity, true), 1);
  }
}

void drawStaticElements() {

  tft.setTextSize(2);
  tft.setTextColor(TEXT_COLOR);
  tft.setCursor(20, 10);
  tft.println("Weather Station");

  tft.drawFastHLine(0, 30, tft.width(), BORDER_COLOR);

  tft.setTextSize(1);
  tft.setCursor(20, 50);
  tft.println("Temperature:");

  tft.setCursor(20, 130);
  tft.println("Humidity:");

  tft.drawRect(0, 0, tft.width(), tft.height(), BORDER_COLOR);
}

void updateDisplay() {

  tft.fillRect(20, 200, 200, 10, BACKGROUND);

  tft.fillRect(20, 70, 200, 40, BACKGROUND);

  tft.setTextSize(3);
  tft.setTextColor(TEMP_COLOR);
  tft.setCursor(20, 70);
  tft.print(temperature, 1);
  tft.println(" C");

  drawThermometer(170, 80);

  tft.fillRect(20, 150, 200, 40, BACKGROUND);

  tft.setTextSize(3);
  tft.setTextColor(HUMID_COLOR);
  tft.setCursor(20, 150);
  tft.print(humidity, 1);
  tft.println(" %");

  drawDroplet(170, 160);
}

void drawThermometer(int x, int y) {
  tft.drawRect(x, y-15, 8, 25, TEMP_COLOR);
  tft.fillRect(x+2, y-13, 4, 18, TEMP_COLOR);
  tft.fillCircle(x+4, y+15, 8, TEMP_COLOR);
  tft.fillCircle(x+4, y+15, 4, BACKGROUND);
  tft.fillRect(x+2, y+5, 4, 10, TEMP_COLOR);
}

void drawDroplet(int x, int y) {

  for(int i = 0; i < 8; i++) {
    tft.drawLine(x+i, y-i, x+i, y+i, HUMID_COLOR);
    tft.drawLine(x-i, y-i, x-i, y+i, HUMID_COLOR);
  }
  tft.fillCircle(x, y+5, 8, HUMID_COLOR);

  tft.drawPixel(x-3, y-3, TFT_WHITE);
  tft.drawPixel(x-2, y-2, TFT_WHITE);
}