/**************************************
* This document is compiled first, all others appended
* This file will have functions to match sensor values to letters
**************************************/

// ************************************
// * Flex sensor data ranges, calibration and range convertor
// ************************************

// Data ranges, calibrated in next function

const int expectedMin = 0;    // (1 <<  0 - 1)
const int expectedMax = 1023; // (1 << 10 - 1)

const int FLEX_PIN1 = A0; // pin #
int flexADC1 = 0;         // Variable storing analogRead data
int sensorMin1 = 1023;    // HIGHEST resistance in range
int sensorMax1 = 0;       // LOWEST resistance in range

const int FLEX_PIN2 = A1; // pin #
int flexADC2 = 0;         // Variable storing analogRead data
int sensorMin2 = 1023;    // HIGHEST resistance in range
int sensorMax2 = 0;       // LOWEST resistance in range

const int FLEX_PIN3 = A2; // pin #
int flexADC3 = 0;         // Variable storing analogRead data
int sensorMin3 = 1023;    // HIGHEST resistance in range
int sensorMax3 = 0;       // LOWEST resistance in range

const int FLEX_PIN4 = A3; // pin #
int flexADC4 = 0;         // Variable storing analogRead data
int sensorMin4 = 1023;    // HIGHEST resistance in range
int sensorMax4 = 0;       // LOWEST resistance in range

const int FLEX_PIN5 = A4; // pin #
int flexADC5 = 0;         // Variable storing analogRead data
int sensorMin5 = 1023;    // HIGHEST resistance in range
int sensorMax5 = 0;       // LOWEST resistance in range

// Calibrates the min/max range of flex sensors. To be run several times for 10 secs during startup
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

// !!! THIS FUNCTION MODIFIES THE flexADC VARIABLES !!!
void remapFlexValues(){
  flexADC1 = map(sensorMin1, sensorMax1, expectedMin, expectedMax);
  flexADC2 = map(sensorMin2, sensorMax2, expectedMin, expectedMax);
  flexADC3 = map(sensorMin3, sensorMax3, expectedMin, expectedMax);
  flexADC4 = map(sensorMin4, sensorMax4, expectedMin, expectedMax);
  flexADC5 = map(sensorMin5, sensorMax5, expectedMin, expectedMax);
}

// ************************************
// *
// ************************************

// Expected range of values for each letter
// NOTE: the flex values MUST be remapped before this

