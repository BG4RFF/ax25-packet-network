// rf95_client.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing client
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example rf95_server
// Tested with Anarduino MiniWirelessLoRa, Rocket Scream Mini Ultra Pro with
// the RFM95W, Adafruit Feather M0 with RFM95

#include <SPI.h>
#include <RH_RF95.h>

// Singleton instance of the radio driver
RH_RF95 rf95;
//RH_RF95 rf95(5, 2); // Rocket Scream Mini Ultra Pro with the RFM95W
//RH_RF95 rf95(8, 3); // Adafruit Feather M0 with RFM95

// Need this on Arduino Zero with SerialUSB port (eg RocketScream Mini Ultra Pro)
//#define Serial SerialUSB

int a,b,c;

uint8_t messageLoop[] = {0xC0, 0x00, 0x82, 0xA0, 0x98, 0x9E, 0xA4, 0x82, 0x60, 0xB2, 0x88,
                         0x60, 0xA6, 0x90, 0xB2, 0x61, 0x03, 0xF0, 0x50, 0x65, 0x72, 0x63,
                         0x6F, 0x62, 0x61, 0x61, 0x6E, 0x20, 0x4C, 0x6F, 0x52, 0x61, 0x20,
                         0x41, 0x58, 0x2E, 0x32, 0x35, 0x20, 0x6D, 0x65, 0x6E, 0x67, 0x67,
                         0x75, 0x6E, 0x61, 0x6B, 0x61, 0x6E, 0x20, 0x4B, 0x49, 0x53, 0x53,
                         0x20, 0x54, 0x4E, 0x43, 0xC0};

void setup()
{
  // Rocket Scream Mini Ultra Pro with the RFM95W only:
  // Ensure serial flash is not interfering with radio communication on SPI bus
//  pinMode(4, OUTPUT);
//  digitalWrite(4, HIGH);

  Serial.begin(19200);
  while (!Serial) ; // Wait for serial port to be available
  if (!rf95.init())
    Serial.println("init failed");
  else
    Serial.println("init success");
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
  // you can set transmitter powers from 5 to 23 dBm:
  // driver.setTxPower(23, false);
  // If you are using Modtronix inAir4 or inAir9,or any other module which uses the
  // transmitter RFO pins and not the PA_BOOST pins
  // then you can configure the power transmitter power for -1 to 14 dBm and with useRFO true.
  // Failure to do that will result in extremely low transmit powers.
  // driver.setTxPower(14, true);
}

void loop()
{
  Serial.write(messageLoop, sizeof(messageLoop));
  Serial.println();
  // Send a message to rf95_server
  a = millis();
  rf95.send(messageLoop, sizeof(messageLoop));

  rf95.waitPacketSent();
  b = millis();
  c = b-a;
  Serial.println(c);
  delay(10000);
}
