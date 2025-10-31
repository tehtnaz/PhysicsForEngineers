/**************************************
* This document is compiled first, all others appended
* This file will have functions to match sensor values to letters
**************************************/

// Libraries & MPU6500 definition

#include <MPU6500_WE.h>
#include "structs.h"

const int csPin = 10;     // Chip Select Pin
const bool useSPI = true; // SPI use flag
/* There are two constructors for SPI: */
MPU6500_WE myMPU6500 = MPU6500_WE(&SPI, csPin, useSPI);
/* Use this one if you want to change the default SPI pins (only for ESP32 / STM32 so far): */
// MPU6500_WE myMPU6500 = MPU6500_WE(&SPI, csPin, mosiPin, misoPin, sckPin, useSPI, true);

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
  flexADC1 = map(flexADC1, sensorMin1, sensorMax1, expectedMin, expectedMax);
  flexADC2 = map(flexADC2, sensorMin2, sensorMax2, expectedMin, expectedMax);
  flexADC3 = map(flexADC3, sensorMin3, sensorMax3, expectedMin, expectedMax);
  flexADC4 = map(flexADC4, sensorMin4, sensorMax4, expectedMin, expectedMax);
  flexADC5 = map(flexADC5, sensorMin5, sensorMax5, expectedMin, expectedMax);
}

// ************************************
// * Letter finding data & functions
// ************************************

// Expected range of values for each letter
// NOTE: the flex values MUST be remapped before this

const LetterFlexRange rangeA = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeB = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeC = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeD = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeE = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeF = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeG = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeH = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeI = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeJ = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeK = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeL = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeM = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeN = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeO = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeP = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeQ = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeR = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeS = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeT = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeU = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeV = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeW = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeX = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeY = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};
const LetterFlexRange rangeZ = {0, 1023, 0, 1023, 0, 1023, 0, 1023, 0, 1023};

bool doesSensorMatchLetter(LetterFlexRange letterRange){
  return flexADC1 < letterRange.flexMax1 && flexADC1 > letterRange.flexMin1 &&
        flexADC2 < letterRange.flexMax2 && flexADC2 > letterRange.flexMin2 &&
        flexADC3 < letterRange.flexMax3 && flexADC3 > letterRange.flexMin3 &&
        flexADC4 < letterRange.flexMax4 && flexADC4 > letterRange.flexMin4 &&
        flexADC5 < letterRange.flexMax5 && flexADC5 > letterRange.flexMin5;
}