// rf95_client.ino
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
//#include <dht.h>

//int led = 9;

// Temperature probe
//dht DHT;
//#define DHT22_PIN 7

// Singleton instance of the radio driver
RH_RF95 rf95;
//RH_RF95 rf95(5, 2); // Rocket Scream Mini Ultra Pro with the RFM95W
//RH_RF95 rf95(8, 3); // Adafruit Feather M0 with RFM95

// Need this on Arduino Zero with SerialUSB port (eg RocketScream Mini Ultra Pro)
//#define Serial SerialUSB

void setup()
{
  // Rocket Scream Mini Ultra Pro with the RFM95W only:
  // Ensure serial flash is not interfering with radio communication on SPI bus
  //  pinMode(4, OUTPUT);
  //  digitalWrite(4, HIGH);
//  pinMode(led, OUTPUT);
//  digitalWrite(led, LOW);
  Serial.begin(9600);
  while (!Serial) ; // Wait for serial port to be available
  if (!rf95.init())
    Serial.println("init failed");
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
  // you can set transmitter powers from 5 to 23 dBm:
  //  driver.setTxPower(23, false);
  // If you are using Modtronix inAir4 or inAir9,or any other module which uses the
  // transmitter RFO pins and not the PA_BOOST pins
  // then you can configure the power transmitter power for -1 to 14 dBm and with useRFO true.
  // Failure to do that will result in extremely low transmit powers.
  //  driver.setTxPower(14, true);
}

void loop()
{
  //Read temperature and humidity
  Serial.println("---------------> Read Temperature");
  Serial.print("DHT22, \t");
  //int chk = DHT.read22(DHT22_PIN);
//  switch (chk)
//  {
//    case DHTLIB_OK:
//      Serial.print("OK,\t");
//      break;
//    case DHTLIB_ERROR_CHECKSUM:
//      Serial.print("Checksum error,\t");
//      break;
//    case DHTLIB_ERROR_TIMEOUT:
//      Serial.print("Time out error,\t");
//      break;
//    default:
//      Serial.print("Unknown error,\t");
//      break;
//  }
  // DISPLAY DATA
  Serial.print(random(0,50));
  Serial.print(",\t");
  Serial.print(random(0,50));
  Serial.println();

  Serial.println("Sending data to rf95_server");
  // Send a message to rf95_server
  float temp = random(0,50);
  uint8_t data[sizeof(float)];
  memcpy(data, &temp, sizeof(temp));
  uint8_t len_data = sizeof(data); //num bytes sent
  Serial.println("Number of bytes sent: " + (String)len_data);
  Serial.print("Data sent: ");
  for (int i = 0; i < len_data; i++) {
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  rf95.send(data, sizeof(data));

  rf95.waitPacketSent();
  // Now wait for a reply
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (rf95.waitAvailableTimeout(3000))
  {
    // Should be a reply message for us now
    if (rf95.recv(buf, &len))
    {
//      digitalWrite(led, HIGH);
      Serial.print("got reply: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);
      delay(300); //Para ver led y saber si tengo respuesta del servidor
//      digitalWrite(led, LOW);
    }
    else
    {
      Serial.println("recv failed");
    }
  }
  else
  {
    Serial.println("No reply, is rf95_server running?");
  }
  delay(10000);
}
