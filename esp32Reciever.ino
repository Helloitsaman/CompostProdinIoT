void setup()
{
  Serial.begin(115200);

  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  Serial.println("ESP Ready");
}

void loop()
{
  if (Serial2.available())
  {
    String json = Serial2.readStringUntil('\n');

    Serial.println("Received:");

    Serial.println(json);
  }
}