#include <Wire.h>

 
void setup() 
{
  Wire.begin();   
  Wire.beginTransmission(0x20);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
}
 
void loop()
{
  
Wire.beginTransmission(0x20); 
  Wire.write(0x12); 
  Wire.write(11110000); //gpa7
  Wire.endTransmission();
  delay(5000);

Wire.beginTransmission(0x20); 
  Wire.write(0x12); 
  Wire.write(11011000); //gpa6
  Wire.endTransmission();
  delay(5000);

   
  Wire.beginTransmission(0x20); 
  Wire.write(0x12); 
  Wire.write(11010010); //gpa5
  Wire.endTransmission();
  delay(5000);

  Wire.beginTransmission(0x20); 
  Wire.write(0x12); 
  Wire.write(00001001); //gpa4
  Wire.endTransmission();
  delay(5000);



//
// Wire.beginTransmission(0x20); 
//  Wire.write(0x12); 
//  Wire.write(00111000); 
//  Wire.endTransmission();
//  delay(5000);
//
//
//  Wire.beginTransmission(0x20); 
//  Wire.write(0x12); 
//  Wire.write(11111111);
//  Wire.endTransmission();
//  delay(5000);

//  Wire.beginTransmission(0x20); 
//  Wire.write(0x12); 
//  Wire.write(00010000); 
//  delay(250);
//  Wire.write(00000000);
//  Wire.endTransmission();
//  delay(250);

}
