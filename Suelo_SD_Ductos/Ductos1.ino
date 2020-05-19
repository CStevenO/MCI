
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
}
