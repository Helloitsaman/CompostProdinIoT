#include <Wire.h>
#include <SoftwareSerial.h>
#include "SparkFun_SCD30_Arduino_Library.h"

SCD30 scd30;

// AOF1010
SoftwareSerial oxygenSerial(2, 3); // RX, TX

// ESP32
SoftwareSerial espSerial(4, 5); // RX, TX

byte packet[12];

float oxygen = -1;
float oxygenTemp = -1;

void readAOF1010()
{
  oxygenSerial.listen();   // Activate AOF1010 port

  unsigned long start = millis();

  while (millis() - start < 300)
  {
    if (oxygenSerial.available() >= 12)
    {
      for (int i = 0; i < 12; i++)
      {
        packet[i] = oxygenSerial.read();
      }

      if (packet[0] == 0x16 && packet[1] == 0x09)
      {
        int o2_raw = (packet[3] << 8) | packet[4];
        int temp_raw = (packet[7] << 8) | packet[8];

        oxygen = o2_raw / 10.0;
        oxygenTemp = temp_raw / 10.0;

        return;
      }
    }
  }
}

void setup()
{
  Serial.begin(9600);

  oxygenSerial.begin(9600);

  espSerial.begin(9600);

  Wire.begin();

  if (!scd30.begin())
  {
    Serial.println("SCD30 not found");
    while (1);
  }

  Serial.println("System Ready");
}

void loop()
{
  // STEP 1: Read oxygen
  readAOF1010();

  // STEP 2: Read SCD30
  float co2 = -1;
  float temp = -1;
  float hum = -1;

  if (scd30.dataAvailable())
  {
    scd30.readMeasurement();

    co2 = scd30.getCO2();
    temp = scd30.getTemperature();
    hum = scd30.getHumidity();
  }

  // STEP 3: Switch to ESP port
  espSerial.listen();

  String json = "{";

  json += "\"o2\":";
  json += String(oxygen, 1);

  json += ",\"o2_temp\":";
  json += String(oxygenTemp, 1);

  json += ",\"co2\":";
  json += String(co2, 0);

  json += ",\"temp\":";
  json += String(temp, 1);

  json += ",\"hum\":";
  json += String(hum, 1);

  json += "}";

  espSerial.println(json);

  // Also print to PC
  Serial.println(json);

  delay(2000);
}