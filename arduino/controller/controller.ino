
// Basic demo for accelerometer readings from Adafruit LIS3DH

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10

// software SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

void setup(void) {
  Serial.begin(9600);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    while (1) yield();
  }


  // lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!

  2 << lis.getRange();
  

  // lis.setDataRate(LIS3DH_DATARATE_50_HZ);
    switch (lis.getDataRate()) {
    case LIS3DH_DATARATE_1_HZ: break;
    case LIS3DH_DATARATE_10_HZ: break;
    case LIS3DH_DATARATE_25_HZ: break;
    case LIS3DH_DATARATE_50_HZ: break;
    case LIS3DH_DATARATE_100_HZ: break;
    case LIS3DH_DATARATE_200_HZ: break;
    case LIS3DH_DATARATE_400_HZ: break;

    case LIS3DH_DATARATE_POWERDOWN: Serial.println("Powered Down"); break;
    case LIS3DH_DATARATE_LOWPOWER_5KHZ: Serial.println("5 Khz Low Power"); break;
    case LIS3DH_DATARATE_LOWPOWER_1K6HZ: Serial.println("16 Khz Low Power"); break;
  }
}

void loop() {
  lis.read();
  sensors_event_t event;
  lis.getEvent(&event);
  Serial.print("X");
  Serial.print(event.acceleration.x);
  Serial.print(";Y");
  Serial.print(event.acceleration.y);
  Serial.print(";Z");
  Serial.print(event.acceleration.z);
  Serial.print(";");
  delayMicroseconds(100);
}
