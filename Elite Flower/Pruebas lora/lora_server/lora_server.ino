// rf95_server.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing server
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95  if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example rf95_client
// Tested with Anarduino MiniWirelessLoRa, Rocket Scream Mini Ultra Pro with
// the RFM95W, Adafruit Feather M0 with RFM95

#include <SPI.h>
#include <RH_RF95.h>

//Yún HTTP Client
#include <Bridge.h>
#include <HttpClient.h>

// Singleton instance of the radio driver
RH_RF95 rf95;
//RH_RF95 rf95(5, 2); // Rocket Scream Mini Ultra Pro with the RFM95W
//RH_RF95 rf95(8, 3); // Adafruit Feather M0 with RFM95

// Need this on Arduino Zero with SerialUSB port (eg RocketScream Mini Ultra Pro)
//#define Serial SerialUSB

//int led = 13;

void setup()
{
  // Rocket Scream Mini Ultra Pro with the RFM95W only:
  // Ensure serial flash is not interfering with radio communication on SPI bus
  //  pinMode(4, OUTPUT);
  //  digitalWrite(4, HIGH);

  //pinMode(led, OUTPUT);
  Serial.begin(9600);
  while (!Serial) ; // Wait for serial port to be available

  // Bridge takes about two seconds to start up
  // it can be helpful to use the on-board LED
  // as an indicator for when it has initialized
  //digitalWrite(led, LOW);
  Bridge.begin();
  //digitalWrite(led, HIGH);

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
  if (rf95.available())
  {
    // Should be a message for us now
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len))
    {
      Serial.println("-----------------> Recibido paquete LoRa");
      //digitalWrite(led, HIGH);
      RH_RF95::printBuffer("request: ", buf, len);
      Serial.println("Number of bytes recieved: " + (String)len);
      Serial.print("Temperature: ");
      float temp;
      memcpy(&temp, buf, len);
      Serial.println(temp);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);

      // Send a reply
      uint8_t data[] = "OK";
      rf95.send(data, sizeof(data));
      rf95.waitPacketSent();
      Serial.println("Sent a reply");
//      digitalWrite(led, LOW);

      if ((temp < 100) && (temp > -20)) { //Evitar mandar datos erroneos
        // Initialize the client library to send data to server (gateway)
        HttpClient client;
        // Make a HTTP request:
        String request = "http://www.aprendiendoarduino.com/servicios/datos/grabaDatos.php?arduino=2&dato=" + (String)temp;
        Serial.println("Reenvio datos a servidor. Petición: " + request);
        client.get(request);
        delay(1000);
        // if there are incoming bytes available
        // from the server, read them and print them:
        while (client.available()) {
          char c = client.read();
          Serial.print(c);
        }
        Serial.println();
        Serial.flush();
        request = "http://api.thingspeak.com/update?api_key=writeapikey&field1=" + (String)temp;
        Serial.println("Reenvio datos a Thinkspeak. Petición: " + request);
        client.get(request);
        delay(1000);
        // if there are incoming bytes available
        // from the server, read them and print them:
        while (client.available()) {
          char c = client.read();
          Serial.print(c);
        }
        Serial.println();
        Serial.flush();
      }
    }
    else
    {
      Serial.println("recv failed");
    }
  }
}
