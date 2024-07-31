#include "ADVcapacitiveSensor.h"
#include <math.h>

ADVcapacitiveSensor::ADVcapacitiveSensor() {
}

static void swap(double* a, double* b) {
  double c = *a;
  *a = *b;
  *b = c;
}

static void sort(double* array) {
  int size = sizeof(array) / sizeof(double);
  for(int i = 0;i < size;i++)
    for(int j = size - 1;j > i; j--)
      if(array[j] < array[j - 1])
        swap(&array[j], &array[j - 1]);
}

double ADVcapacitiveSensor::begin(int send, int receive, double voltage, int frequency, int breakthreshold, double exceptratio) {
  SEND = send;
  RECEIVE = receive;
  VOLTAGE = voltage;
  FREQUENCY = frequency;
  BREAKTHRESHOLD = breakthreshold;
  EXCEPTRATIO = exceptratio;
  OFFSETZERO = 0.00;
  double valtouch = 0.00;
  for (int i = 0; i < 10; i++) { // take the lowest of ten readings
	delay(10);
	valtouch += ADVcapacitiveSensor::touch();
  }
  OFFSETZERO = valtouch/10.3; //  -3% for noise
  return OFFSETZERO;
}

double ADVcapacitiveSensor::touch() {
  double VAL[FREQUENCY];
  double INPUTTHRESHOLD = VOLTAGE * 1024 / 5 * 0.9;
  for (int i = 0; i < FREQUENCY; i++) {
    double val = 0;
    unsigned long starttim;
    digitalWrite(SEND, HIGH);
    starttim = micros();
    while (analogRead(RECEIVE) < INPUTTHRESHOLD) {
      val = micros() - starttim;
      if (val > BREAKTHRESHOLD) {
        int tim = micros() - starttim;
        int vol = analogRead(RECEIVE);
        double gamma = -log(1 - vol / (INPUTTHRESHOLD / 0.9)) / tim;
        val = -log(1 - 0.9) / gamma;
        break;
      }
    }
    digitalWrite(SEND, LOW);
    delayMicroseconds(10);

    if (val > 0) {
      VAL[i] = val;
    } else
      i--;
  }
  sort(VAL);
  double VALsum = 0;
  int except = FREQUENCY * EXCEPTRATIO;
  for (int i = except;i < FREQUENCY - except;i++)
    VALsum += VAL[i];
  int dev = FREQUENCY - 2 * except;
  return VALsum / dev - OFFSETZERO;
}

bool ADVcapacitiveSensor::booltouch() {
  double valtouch = 0.00;
  for (int i = 0; i < 6; i++) { // take tree readings
	valtouch += ADVcapacitiveSensor::touch();
  }
  return valtouch > OFFSETZERO ? HIGH:LOW;
}