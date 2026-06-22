#define MQ9_PIN      34
#define MQ137_PIN    35
#define MICS2714_PIN 32

void setup() {

  Serial.begin(115200);

  analogReadResolution(12);      // ADC range: 0 - 4095

  Serial.println("Gas Sensor JSON Output");
}

void loop() {

  int mq9Raw = analogRead(MQ9_PIN);
  int mq137Raw = analogRead(MQ137_PIN);
  int micsRaw = analogRead(MICS2714_PIN);

  float mq9Voltage   = (mq9Raw * 3.3) / 4095.0;
  float mq137Voltage = (mq137Raw * 3.3) / 4095.0;
  float micsVoltage  = (micsRaw * 3.3) / 4095.0;

  // JSON output
  Serial.print("{");

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