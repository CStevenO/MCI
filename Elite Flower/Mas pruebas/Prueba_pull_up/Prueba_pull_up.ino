//#include "Adafruit_MCP23017.h"
//Adafruit_MCP23017 mcp;
#define venIn 2
bool valor;
void setup() {
//mcp.begin();
//mcp.pinMode(venIn, INPUT_PULLUP);
pinMode(venIn, INPUT_PULLUP);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//valor = mcp.digitalRead(venIn);
valor = digitalRead(venIn);
Serial.println(valor);
delay(1000);
}
