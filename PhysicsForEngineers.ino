/**************************************
* This document is compiled first, all others appended
* This file will have functions to match sensor values to letters
**************************************/

// Data ranges, calibrated in setup

int FLEX_PIN1 = A0;
int flexADC1 = 0;
int sensorMin1 = 1023;
int sensorMax1 = 0;

int FLEX_PIN2 = A1;
int flexADC2 = 0;
int sensorMin2 = 1023;
int sensorMax2 = 0;

int FLEX_PIN3 = A2;
int flexADC3 = 0;
int sensorMin3 = 1023;
int sensorMax3 = 0;

int FLEX_PIN4 = A3;
int flexADC4 = 0;
int sensorMin4 = 1023;
int sensorMax4 = 0;

int FLEX_PIN5 = A4;
int flexADC5 = 0;
int sensorMin5 = 1023;
int sensorMax5 = 0;

// Calibrates the min/max range of flex sensors. To be run for 10 secs during startup
void readMinMax() {
  flexADC1 = analogRead(FLEX_PIN1);
  flexADC2 = analogRead(FLEX_PIN2);
  flexADC3 = analogRead(FLEX_PIN3);
  flexADC4 = analogRead(FLEX_PIN4);
  flexADC5 = analogRead(FLEX_PIN5);

  if (flexADC1 < sensorMin1) {
    sensorMin1 = flexADC1;
  }
  if (flexADC1 > sensorMax1) {
    sensorMax1 = flexADC1;
  }

  if (flexADC2 < sensorMin2) {
    sensorMin2 = flexADC2;
  }
  if (flexADC2 > sensorMax2) {
    sensorMax2 = flexADC2;
  }

  if (flexADC3 < sensorMin3) {
    sensorMin3 = flexADC3;
  }
  if (flexADC3 > sensorMax3) {
    sensorMax4 = flexADC4;
  }

  if (flexADC5 < sensorMin5) {
    sensorMin5 = flexADC5;
  }
  if (flexADC5 > sensorMax5) {
    sensorMax5 = flexADC5;
  }

  if (flexADC4 < sensorMin4) {
    sensorMin4 = flexADC4;
  }
  if (flexADC4 > sensorMax4) {
    sensorMax4 = flexADC4;
  }
}