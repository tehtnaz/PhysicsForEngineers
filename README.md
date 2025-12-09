# PhysicsForEngineers
## ASL Glove project

This is the code uploaded to the arduino. It reads the analog values from the pressure sensors and determines which letters are being signed, then sends the result through the serial connection (connected to the bluetooth module).
1. The glove goes through a calibration step, the MPU6500 is calibrated, then the full range of motion is done on the glove to get the maximum and minimum range of values from the pressure sensors.
2. The range of values is used to standardize the readings according to the range of motion of each person's hand. (mapped onto 0-1023, the expected range)
3. The glove constantly matches the sensor data (pressure sensor and accelerometer) to a letter(s) and stores the possibilities as a bitmask
4. The data from each frame is added to the next frame (bitwise OR) for one second
5. The data obtained over that second is sent through bluetooth

PhysicsForEngineers.ino is the main file, Runner.ino is appended onto it during compilation.
- PhysicsForEngineers.ino: File that holds calibration functions, temporary stored values, calibrated ranges for each letter, and bitmask builder.
- Runner.ino: Has setup & loop functions which initialize the calibration for MPU6500 and flex sensors, then constantly updates sensor values and outputs data
- structs.h: A file containing a couple structs to make storing the accepted range of values for each letter easier

Members:
- Jase Beaumont
- Vanessa Rozendaal
- Melissa Guenette
- Chelsea Predestin
