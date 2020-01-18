char A;

void setup() {
Serial.begin(9600);
}

void loop() {

 if(Serial.available()>0)

 {
  A=Serial.read();
  Serial.print("La letra es ");
  Serial.println(A);
  
 }
}
