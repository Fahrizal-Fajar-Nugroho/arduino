include <DHT.h>
#include <SoilHygrometer.h>
#include "thingProperties.h"

#define DHT11_PIN 2
#define SOIL_MOISTURE_PIN A0
#define DHTTYPE DHT11

DHT dht(DHT11_PIN, DHTTYPE);
SoilHygrometer soilHygrometer(SOIL_MOISTURE_PIN); // Changed from hygrometer to soilHygrometer

void setup() {
  Serial.begin(9600);
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  Serial.println(F("DHT11 & Soil Moisture Sensor READY"));
  dht.begin(); // Memanggil metode begin() dari objek dht
  pinMode(SOIL_MOISTURE_PIN, INPUT);
}

void loop() {
  ArduinoCloud.update();
  
  Serial.println(F("Reading DHT11 sensor..."));
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  
  if (!isnan(temp)) {
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" °C");
    // Kirim data ke Arduino Cloud
    temperature = temp;
  } else {
    Serial.println("Error reading temperature!");
  }
  
  if (!isnan(hum)) {
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.println(" %");
    // Kirim data ke Arduino Cloud
    kelembapan = hum;
  } else {
    Serial.println("Error reading humidity!");
  }

  int soilMoistureValue = 100 - soilHygrometer.read(0, 100); // Membaca nilai kelembaban tanah dengan dua argumen
  Serial.print("Soil hygrometer value: ");
  Serial.println(soilMoistureValue);
  // Kirim data ke Arduino Cloud
  soilMoisture = soilMoistureValue;
  Serial.println();
}