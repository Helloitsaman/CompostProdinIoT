#define MQ9_PIN      34
#define MQ137_PIN    35
#define MICS2714_PIN 32

String unoJson = "{}";

void setup()
{
  Serial.begin(115200);

  // UART from Arduino UNO
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  analogReadResolution(12);

  Serial.println("ESP Ready");
}

void loop()
{
  // Read JSON from UNO
  if (Serial2.available())
  {
    unoJson = Serial2.readStringUntil('\n');

    unoJson.trim();
  }

  // Read ESP sensors
  int mq9Raw = analogRead(MQ9_PIN);
  int mq137Raw = analogRead(MQ137_PIN);
  int micsRaw = analogRead(MICS2714_PIN);

  float mq9Voltage   = (mq9Raw * 3.3) / 4095.0;
  float mq137Voltage = (mq137Raw * 3.3) / 4095.0;
  float micsVoltage  = (micsRaw * 3.3) / 4095.0;

  // Remove outer braces from UNO JSON
  String inside = "";

  if (unoJson.startsWith("{") && unoJson.endsWith("}"))
  {
    inside = unoJson.substring(1, unoJson.length() - 1);
  }

  // Combined JSON
  Serial.print("{");

  if (inside.length() > 0)
  {
    Serial.print(inside);
    Serial.print(",");
  }

  Serial.print("\"mq9_raw\":");
  Serial.print(mq9Raw);

  Serial.print(",\"mq9_v\":");
  Serial.print(mq9Voltage, 3);

  Serial.print(",\"mq137_raw\":");
  Serial.print(mq137Raw);

  Serial.print(",\"mq137_v\":");
  Serial.print(mq137Voltage, 3);

  Serial.print(",\"mics2714_raw\":");
  Serial.print(micsRaw);

  Serial.print(",\"mics2714_v\":");
  Serial.print(micsVoltage, 3);

  Serial.println("}");

  delay(1000);
}