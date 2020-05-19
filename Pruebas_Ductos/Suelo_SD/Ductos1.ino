#include <Wire.h>
float Pa = 0;
byte dsp_t_sync = 0;
byte dsp_s_sync = 0 ;
byte status_r = 0;
int buffer[3];

void setup() {
  Serial.begin(9600);
    Wire.begin();
    }

void loop() {
ReadPressure_noCRC();

}



void ReadPressure_noCRC() {
Wire.beginTransmission(0x6C); // transmit to device #address = 0x6C
Wire.write(0x2E);
Wire.endTransmission(); // stop transmitting
Wire.requestFrom(0x6C, 6); //Request registers, note that registers 2 bytes wide
//
for (int i = 0; i < 3; i++)
{
buffer[i] = Wire.read(); // read low byte
buffer[i] = buffer[i] | (Wire.read() << 8); // read high byte
}
//
dsp_t_sync = buffer[0]; //dsp_t register (corrected temperature measurement)
dsp_s_sync = buffer[1]; //dsp_s register (corrected pressure measurement)
status_r = buffer[2]; //status_sync register


Pa = ((dsp_s_sync+25600)/20480)*1000;
Serial.print("Pa ");
Serial.print(Pa);
Serial.println("DSP_S: " + String(dsp_s_sync));
Serial.println("DSP_T: " + String(dsp_t_sync));
Serial.println("Status:" + String(status_r, BIN) + "( 0x" + String(status_r, HEX) + " )");
}
