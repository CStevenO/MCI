#include <Wire.h>
#include "Adafruit_MCP23017.h"

// Basic pin reading and pullup test for the MCP23017 I/O expander
// public domain!

// Connect pin #12 of the expander to Analog 5 (i2c clock)
// Connect pin #13 of the expander to Analog 4 (i2c data)
// Connect pins #15, 16 and 17 of the expander to ground (address selection)
// Connect pin #9 of the expander to 5V (power)
// Connect pin #10 of the expander to ground (common ground)
// Connect pin #18 through a ~10kohm resistor to 5V (reset pin, active low)

// Output #0 is on pin 21 so connect an LED or whatever from that to ground

Adafruit_MCP23017 mcp;
  
void setup() {  
  mcp.begin();      // use default address 0

  mcp.pinMode(7, OUTPUT);
  mcp.pinMode(6, OUTPUT);
  mcp.pinMode(5, OUTPUT);
  mcp.pinMode(4, OUTPUT);
}


// flip the pin #0 up and down

void loop() {
  delay(100);
  mcp.digitalWrite(7, HIGH);
  mcp.digitalWrite(6, HIGH);
  mcp.digitalWrite(5, HIGH);
  mcp.digitalWrite(4, LOW);

  delay(5000);

   mcp.digitalWrite(7, HIGH);
  mcp.digitalWrite(6, HIGH);
  mcp.digitalWrite(5, HIGH);
  mcp.digitalWrite(4, HIGH);

delay(5000);
//  mcp.digitalWrite(6, HIGH);
//
//  delay(2000);
//
//  mcp.digitalWrite(6, LOW);
//
//
//delay(2000);
}
