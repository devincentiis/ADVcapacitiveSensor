#include <ADVcapacitiveSensor.h>
ADVcapacitiveSensor sensor1;
ADVcapacitiveSensor sensor2;

void setup() {
  pinMode(A0, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, INPUT);
  Serial.begin(9600);
  Serial.print(sensor1.begin(A0, A1, 5.0, 10, 10, 0.2));
  Serial.print("\t");
  Serial.println(sensor2.begin(A2, A3, 5.0, 10, 10, 0.2));
  delay(2000);
}

void loop() {
  Serial.print(sensor1.touch());
  Serial.print("\t");
  Serial.println(sensor2.touch());
  digitalWrite(LED_BUILTIN, sensor1.booltouch());
  digitalWrite(LED_BUILTIN, sensor2.booltouch());
}
