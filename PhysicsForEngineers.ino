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
void calibrateMinMax() {
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
    sensorMax3 = flexADC3;
  }

  if (flexADC4 < sensorMin4) {
    sensorMin4 = flexADC4;
  }
  if (flexADC4 > sensorMax4) {
    sensorMax4 = flexADC4;
  }

  if (flexADC5 < sensorMin5) {
    sensorMin5 = flexADC5;
  }
  if (flexADC4 > sensorMax5) {
    sensorMax5 = flexADC5;
  }
}

// !!! THIS FUNCTION MODIFIES THE flexADC VARIABLES !!!
void readAndRemapFlexValues(){
  flexADC1 = analogRead(FLEX_PIN1);
  flexADC2 = analogRead(FLEX_PIN2);
  flexADC3 = analogRead(FLEX_PIN3);
  flexADC4 = analogRead(FLEX_PIN4);
  flexADC5 = analogRead(FLEX_PIN5);

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
// 1024 is the max instead of 1023 because we only check if flexADC < flexMax
//                             { MIN , MAX , || MIN , MAX , || MIN , MAX , || MIN , MAX , || MIN , MAX  }
const LetterFlexRange rangeA = { 0   , 100 ,    900 , 1024,    900 , 1024,    900 , 1024,    900 , 1024 };
const LetterFlexRange rangeB = { 200 , 1024,    0   , 200 ,    0   , 200 ,    0   , 200 ,    0   , 200  };
const LetterFlexRange rangeC = { 200 , 1024,    0   , 500 ,    0   , 900 ,    0   , 900 ,    0   , 900  };
const LetterFlexRange rangeD = { 0   , 1024,    0   , 100 ,    800 , 1024,    800 , 1024,    800 , 1024 }; // fix A0
const LetterFlexRange rangeE = { 900 , 1024,    900 , 1024,    900 , 1024,    900 , 1024,    900 , 1024 };
const LetterFlexRange rangeF = { 0   , 100 ,    500 , 1024,    0   , 700 ,    0   , 100 ,    0   , 200  };
const LetterFlexRange rangeG = { 0   , 1024,    0   , 100 ,    800 , 1024,    800 , 1024,    800 , 1024 }; // fix A0
const LetterFlexRange rangeH = { 0   , 300 ,    500 , 900 ,    500 , 900 ,    900 , 1024,    900 , 1024 };
const LetterFlexRange rangeI = { 0   , 100 ,    900 , 1024,    900 , 1024,    300 , 1000,    0   , 1024 };
const LetterFlexRange rangeJ = { 0   , 100 ,    900 , 1024,    900 , 1024,    300 , 1000,    0   , 1024 }; // read from acc aswell
const LetterFlexRange rangeK = { 0   , 100 ,    0   , 100 ,    0   , 400 ,    0   , 900 ,    900 , 1024 };
const LetterFlexRange rangeL = { 0   , 300 ,    0   , 100 ,    900 , 1024,    900 , 1024,    900 , 1024 };
const LetterFlexRange rangeM = { 0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024 };
const LetterFlexRange rangeN = { 0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024 };
const LetterFlexRange rangeO = { 0   , 100 ,    800 , 1024,    900 , 1024,    900 , 1024,    900 , 1024 };
const LetterFlexRange rangeP = { 0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024 };
const LetterFlexRange rangeQ = { 0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024 };
const LetterFlexRange rangeR = { 0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024 };
const LetterFlexRange rangeS = { 0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024 };
const LetterFlexRange rangeT = { 0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024 };
const LetterFlexRange rangeU = { 0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024 };
const LetterFlexRange rangeV = { 0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024 };
const LetterFlexRange rangeW = { 0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024 };
const LetterFlexRange rangeX = { 0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024 };
const LetterFlexRange rangeY = { 0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024 };
const LetterFlexRange rangeZ = { 0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024,    0   , 1024 };

bool doesSensorMatchLetterFlex(LetterFlexRange letterRange){
  return flexADC1 < letterRange.flexMax1 && flexADC1 >= letterRange.flexMin1 &&
         flexADC2 < letterRange.flexMax2 && flexADC2 >= letterRange.flexMin2 &&
         flexADC3 < letterRange.flexMax3 && flexADC3 >= letterRange.flexMin3 &&
         flexADC4 < letterRange.flexMax4 && flexADC4 >= letterRange.flexMin4 &&
         flexADC5 < letterRange.flexMax5 && flexADC5 >= letterRange.flexMin5;
}

// ************************************
// * MPU6500 sensor data ranges
// ************************************

xyzFloat gValue = xyzFloat(0, 0, 0);
xyzFloat gyr = xyzFloat(0, 0, 0);
// float resultantG = myMPU6500.getResultantG(gValue);

void GetMPU7600Data(){
  gValue = myMPU6500.getGValues();
  gyr = myMPU6500.getGyrValues();
}


const LetterXYZRange accRangeNormal = {xyzFloat(-100.0f, -0.5f, -0.5f), xyzFloat(-1.0f, 0.5f, 0.5f)};

const LetterXYZRange accRangeG = {xyzFloat(-1.0f, -1.0f, -100.0f), xyzFloat(-0.5f, -0.5f, 100.0f)};
const LetterXYZRange accRangeH = {xyzFloat(-1.0f, -1.0f, -100.0f), xyzFloat(-0.5f, -0.5f, 100.0f)};

const LetterXYZRange gyrRangeNormal = {xyzFloat(-100.0f, -100.0f, -100.0f), xyzFloat(100.0f, 100.0f, 100.0f)};

// letter J is anything outside of normal

bool doesSensorMatchLetterAcceleration(LetterXYZRange letterXYZRange){
  return gValue.x < letterXYZRange.maximumRange.x && gValue.x >= letterXYZRange.minimumRange.x &&
         gValue.y < letterXYZRange.maximumRange.y && gValue.y >= letterXYZRange.minimumRange.y &&
         gValue.z < letterXYZRange.maximumRange.z && gValue.z >= letterXYZRange.minimumRange.z;
}
bool doesSensorMatchLetterGyro(LetterXYZRange letterXYZRange){
  return gyr.x < letterXYZRange.maximumRange.x && gyr.x >= letterXYZRange.minimumRange.x &&
         gyr.y < letterXYZRange.maximumRange.y && gyr.y >= letterXYZRange.minimumRange.y &&
         gyr.z < letterXYZRange.maximumRange.z && gyr.z >= letterXYZRange.minimumRange.z;
}


// ************************************
// * Letter finders
// ************************************
uint32_t letterBitMask;
uint32_t accBitMask;
uint32_t gyroBitMask;

void matchLetterWithFlex(){
  letterBitMask = 0;

  if(doesSensorMatchLetterFlex(rangeA)){
    letterBitMask |= (uint32_t)1 << 0;
  }
  if(doesSensorMatchLetterFlex(rangeB)){
    letterBitMask |= (uint32_t)1 << 1;
  }
  if(doesSensorMatchLetterFlex(rangeC)){
    letterBitMask |= (uint32_t)1 << 2;
  }
  if(doesSensorMatchLetterFlex(rangeD)){
    letterBitMask |= (uint32_t)1 << 3;
  }
  if(doesSensorMatchLetterFlex(rangeE)){
    letterBitMask |= (uint32_t)1 << 4;
  }
  if(doesSensorMatchLetterFlex(rangeF)){
    letterBitMask |= (uint32_t)1 << 5;
  }
  if(doesSensorMatchLetterFlex(rangeG)){
    letterBitMask |= (uint32_t)1 << 6;
  }
  if(doesSensorMatchLetterFlex(rangeH)){
    letterBitMask |= (uint32_t)1 << 7;
  }
  if(doesSensorMatchLetterFlex(rangeI)){
    letterBitMask |= (uint32_t)1 << 8;
  }
  if(doesSensorMatchLetterFlex(rangeJ)){
    letterBitMask |= (uint32_t)1 << 9;
  }
  if(doesSensorMatchLetterFlex(rangeK)){
    letterBitMask |= (uint32_t)1 << 10;
  }
  if(doesSensorMatchLetterFlex(rangeL)){
    letterBitMask |= (uint32_t)1 << 11;
  }
  if(doesSensorMatchLetterFlex(rangeM)){
    letterBitMask |= (uint32_t)1 << 12;
  }
  if(doesSensorMatchLetterFlex(rangeN)){
    letterBitMask |= (uint32_t)1 << 13;
  }
  if(doesSensorMatchLetterFlex(rangeO)){
    letterBitMask |= (uint32_t)1 << 14;
  }
  if(doesSensorMatchLetterFlex(rangeP)){
    letterBitMask |= (uint32_t)1 << 15;
  }
  if(doesSensorMatchLetterFlex(rangeQ)){
    letterBitMask |= (uint32_t)1 << 16;
  }
  if(doesSensorMatchLetterFlex(rangeR)){
    letterBitMask |= (uint32_t)1 << 17;
  }
  if(doesSensorMatchLetterFlex(rangeS)){
    letterBitMask |= (uint32_t)1 << 18;
  }
  if(doesSensorMatchLetterFlex(rangeT)){
    letterBitMask |= (uint32_t)1 << 19;
  }
  if(doesSensorMatchLetterFlex(rangeU)){
    letterBitMask |= (uint32_t)1 << 20;
  }
  if(doesSensorMatchLetterFlex(rangeV)){
    letterBitMask |= (uint32_t)1 << 21;
  }
  if(doesSensorMatchLetterFlex(rangeW)){
    letterBitMask |= (uint32_t)1 << 22;
  }
  if(doesSensorMatchLetterFlex(rangeX)){
    letterBitMask |= (uint32_t)1 << 23;
  }
  if(doesSensorMatchLetterFlex(rangeY)){
    letterBitMask |= (uint32_t)1 << 24;
  }
  if(doesSensorMatchLetterFlex(rangeZ)){
    letterBitMask |= (uint32_t)1 << 25;
  }
}

void matchLetterWithAcc(){
  accBitMask = 0;

  if(doesSensorMatchLetterAcceleration(accRangeNormal)){
    // all except G and H
    accBitMask |= ~(((uint32_t)1 << 6) + ((uint32_t)1 << 7));
  }
  if(doesSensorMatchLetterAcceleration(accRangeG)){
    accBitMask |= (uint32_t)1 << 6;
  }
  if(doesSensorMatchLetterAcceleration(accRangeH)){
    accBitMask |= (uint32_t)1 << 7;
  }
}

void matchLetterWithGyro(){
  gyroBitMask = 0;

  if(doesSensorMatchLetterGyro(gyrRangeNormal)){
    // all except letter J
    gyroBitMask = ~((uint32_t)1 << 9);
  }else{
    // letter J
    gyroBitMask |= (uint32_t)1 << 9;
  }
}

// could replace each (uint)1 << x with #DEFINEs for each letter, but that's a little more messy

uint32_t matchAllMasks(){
  matchLetterWithFlex();
  matchLetterWithAcc();
  matchLetterWithGyro();
  return letterBitMask & accBitMask & gyroBitMask;
}