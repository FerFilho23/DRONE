#include <Wire.h>
int16_t Gyro_X, Gyro_Y, Gyro_Z;


void setup() {
  Serial.begin(57600);    //Start serial port at 57600bps
  Wire.setClock(400000);   //Set the I2C clock speed to 400kHz
  Wire.begin();           //Start the I2C as master
  delay(250);             //Give the gyro time to start

  Wire.beginTransmission(0x68);       //Start communication w/ the MPU-6050
  Wire.write(0X6B);                   //Start writing at this register (PWR_MGMT_1)
  Wire.write(0x00);                   //Set register 0x6B to zero (wakes up the MPU-6050)
  Wire.endTransmission();             //Terminate the connection
}

void loop() {
  Wire.beginTransmission(0x68);             //Start communication w/ the MPU-6050
  Wire.write(0x43);                         //Sent byte to 0x43 to indicate start register
  Wire.endTransmission();                   //Terminate the connection
  Wire.requestFrom(0x68,6);                 //Request 6 bytes from the MPU-6050
  Gyro_X = Wire.read()<<8 | Wire.read();    //Shift high byte left and add low and high byte to Gyro_X  
  Gyro_Y = Wire.read()<<8 | Wire.read();    //Shift high byte left and add low and high byte to Gyro_Y  
  Gyro_Z = Wire.read()<<8 | Wire.read();    //Shift high byte left and add low and high byte to Gyro_Z
 
  Serial.print("X = ");          //Print variables to serial output
  Serial.print(Gyro_X);
  Serial.print(" Y = ");
  Serial.print(Gyro_Y);
  Serial.print(" Z = ");
  Serial.print(Gyro_Z);
  Serial.print("\n");
  delay(250);  
}
