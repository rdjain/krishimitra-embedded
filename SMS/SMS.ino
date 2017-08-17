 #include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);
void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(100);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919743451835\"\r"); // Replace x with mobile number
  delay(100);
  mySerial.println("ping1111");// The SMS te want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(250);
  

}

void loop() {
  // put your main code here, to run repeatedly:

}













