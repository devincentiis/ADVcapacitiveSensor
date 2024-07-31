#ifndef ADVcapacitiveSensor_h
#define ADVcapacitiveSensor_h

#include "Arduino.h"

class ADVcapacitiveSensor {
public:
  ADVcapacitiveSensor();
  double begin(int send, int receive, double voltage, int frequency, int breakthreshold, double exceptratio);
  double touch();
  bool booltouch();

private:
  int FREQUENCY;
  int BREAKTHRESHOLD;
  double EXCEPTRATIO;
  int SEND;
  int RECEIVE;
  double VOLTAGE;
  double OFFSETZERO;	
};

#endif