/*************************************
* This file is appended after PhysicsForEngineers.ino
* This file will use functions from before to get the letters, then wil write it to the Bluetooth.
* This will also contain the setup / loop functions
*************************************/

/***************************************************************************
* This file uses code from the example for the MPU6500_WE library
*
* The author's blog is here
* https://wolles-elektronikkiste.de/en/mpu9250-9-axis-sensor-module-part-1
* 
***************************************************************************/

int connectTries = 5;

// Initialize/config mpu6500 & calibrate gyroscope
void setupMPU6500(){
  for(int i = 0; i < connectTries; i++){
    if (!myMPU6500.init()) {
      Serial.println("MPU6500 does not respond. Retrying in 3 seconds...");
      if(i == (connectTries - 1)){
        // for-loop just in case this if check doesn't work
        Serial.println("ERROR: Connection to MPU6500 not found after 5 tries. MPU6500 will remain inactive. Continuing with default data...");
        break;
      }
    } else {
      Serial.println("MPU6500 is connected");
      break;
    }
    delay(3000);
  }
  /* Choose the SPI clock speed, default is 8 MHz 
     This function must be used only after init(), not before */
  //myMPU9250.setSPIClockSpeed(4000000);

  Serial.println("Position your MPU6500 flat and don't move it - calibrating...");
  delay(1000);
  myMPU6500.autoOffsets();
  Serial.println("Done!");

  //myMPU6500.setAccOffsets(-14240.0, 18220.0, -17280.0, 15590.0, -20930.0, 12080.0);
  //myMPU6500.setGyrOffsets(45.0, 145.0, -105.0);
  myMPU6500.enableGyrDLPF();
  //myMPU6500.disableGyrDLPF(MPU6500_BW_WO_DLPF_8800); // bandwdith without DLPF
  myMPU6500.setGyrDLPF(MPU6500_DLPF_6);
  myMPU6500.setSampleRateDivider(5);
  myMPU6500.setGyrRange(MPU6500_GYRO_RANGE_250);
  myMPU6500.setAccRange(MPU6500_ACC_RANGE_2G);
  myMPU6500.enableAccDLPF(true);
  myMPU6500.setAccDLPF(MPU6500_DLPF_6);
  //myMPU6500.enableAccAxes(MPU6500_ENABLE_XYZ); // this is the default value
  //myMPU6500.enableGyrAxes(MPU6500_ENABLE_XYZ); // this is the default value

}

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  Serial.begin(9600);
  setupMPU6500();
  Serial.println("Calibrating sensor range");
  // Calibrating the sensors for different bend ranges
  while (millis() < 11000) {
    // millis bc im lazy and dont wanna hog memory
    // we generally either shouldnt care about an extra second of calibration or should notice the extra time taken to connect mpu6500
    calibrateMinMax();
  }
  Serial.print("1: ");
  Serial.println(sensorMin1);
  Serial.print("2: ");
  Serial.println(sensorMin2);
  Serial.print("3: ");
  Serial.println(sensorMin3);
  Serial.print("4: ");
  Serial.println(sensorMin4);
  Serial.print("5: ");
  Serial.println(sensorMin5);

  Serial.print("1: ");
  Serial.println(sensorMax1);
  Serial.print("2: ");
  Serial.println(sensorMax2);
  Serial.print("3: ");
  Serial.println(sensorMax3);
  Serial.print("4: ");
  Serial.println(sensorMax4);
  Serial.print("5: ");
  Serial.println(sensorMax5);

  bool sensorFatal = false;
  if(sensorMin1 == sensorMax1){
    Serial.println("ERROR - FATAL: NO INPUT detected on Thumb (A0)!");
    sensorFatal = true;
  }
  if(sensorMin2 == sensorMax2){
    Serial.println("ERROR - FATAL: NO INPUT detected on Index (A1)!");
    sensorFatal = true;
  }
  if(sensorMin3 == sensorMax3){
    Serial.println("ERROR - FATAL: NO INPUT detected on Middle (A2)!");
    sensorFatal = true;
  }
  if(sensorMin4 == sensorMax4){
    Serial.println("ERROR - FATAL: NO INPUT detected on Ring (A3)!");
    sensorFatal = true;
  }
  if(sensorMin5 == sensorMax5){
    Serial.println("ERROR - FATAL: NO INPUT detected on Pinky (A4)!");
    sensorFatal = true;
  }
  if(sensorFatal){
    delay(60000);
  }

  
  delay(5000);
}



unsigned long lastMillis = 0;


void loop() {
  // over the course of one second, add all possibilities of letters we obtained during each check
  lastMillis = millis();
  masksOverTime = 0;
  while(millis() < (lastMillis + 1000)){
    GetMPU7600Data();
    readAndRemapFlexValues();
    masksOverTime |= matchAllMasks();
  }

  // output debug info

  Serial.println("Acceleration in g (x,y,z):");
  Serial.print(gValue.x);
  Serial.print("   ");
  Serial.print(gValue.y);
  Serial.print("   ");
  Serial.println(gValue.z);

  Serial.println("Gyroscope data in degrees/s: ");
  Serial.print(gyr.x);
  Serial.print("   ");
  Serial.print(gyr.y);
  Serial.print("   ");
  Serial.println(gyr.z);

  Serial.print("1: ");
  Serial.println(flexADC1);
  Serial.print("2: ");
  Serial.println(flexADC2);
  Serial.print("3: ");
  Serial.println(flexADC3);
  Serial.print("4: ");
  Serial.println(flexADC4);
  Serial.print("5: ");
  Serial.println(flexADC5);

  // output data
  Serial.println(letterBitMask);
  Serial.println(accBitMask);
  Serial.println(gyroBitMask);

  // output data to be parsed by the android app
  Serial.print("MASK:");
  Serial.print(masksOverTime);
  Serial.println("//");

  // message delimiter
  Serial.println("********************************************");
}
