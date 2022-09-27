// =====================================================================
//
//                    TAURUS - 한국교통대학교 항공우주팀
//                     Science Projectile Aldebaran
//
//              Lee Seung Hwan / Lee Ji Haeng / Choi Hong Suk
//
// =====================================================================

#include "DHT.h"
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

File myFile;
DHT dht(A1, DHT22);

const int MPU_addr=0x68; // MPU-6050 I2C address
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int Buzzer_PIN = 9;

void setup() {
  dht.begin();

  pinMode(Buzzer_PIN, OUTPUT);

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  if (!SD.begin(4)) {
    while (1) { // SD카드 모듈 초기화 실패시 0.5초 간격으로 부저 4번 출력
      for (int i = 0; i < 4; i++) {
        digitalWrite(Buzzer_PIN, HIGH);
        delay(500);
        digitalWrite(Buzzer_PIN, LOW);
        delay(500);
      }
      delay(5000);
    }
  }

  myFile = SD.open("taurus.txt", FILE_WRITE);
  
  myFile.print("================================================\n\n");
  myFile.println("TAURUS Science Projectile - Aldebaran");
  myFile.println("Korea National University of Transportation");
  myFile.println("\nAldebaran MPU6050 / DHT22 Module Data Log");
  myFile.print("\n================================================\n\n");
  myFile.close();
  
  for (int i = 0; i < 2; i++) { // Setup 정상 수행 시 1초 간격으로 부저 2번 출력
    digitalWrite(Buzzer_PIN, HIGH);
    delay(500);
    digitalWrite(Buzzer_PIN, LOW);
    delay(1000);
  }
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float hic = dht.computeHeatIndex(t, h, false);
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  myFile = SD.open("taurus.txt", FILE_WRITE);

  if (myFile) {
    myFile.print("Humidity: "); myFile.print(h);
    myFile.print("% / Temperature: "); myFile.print(t);
    myFile.print("'C\nX=");  myFile.print(AcX);
    myFile.print(" Y=");  myFile.print(AcY);
    myFile.print(" Z=");  myFile.print(AcZ);
    myFile.print("\nROLL=");  myFile.print(GyX);
    myFile.print(" PITCH=");  myFile.print(GyY);
    myFile.print(" YAW=");  myFile.println(GyZ);
    myFile.print("\n================================================\n\n");
    myFile.close();
    delay(500);
  }
 delay(1000);
}
