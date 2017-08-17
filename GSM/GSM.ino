#include <SoftwareSerial.h>
#include <GSM.h>
GSMVoiceCall vcs;
#define rxPin 10
#define txPin 11

SoftwareSerial mySerial(rxPin,txPin); // RX, TX

void setup(){

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  Serial.begin(9600);
  Serial.println("Arduino serial initialized!");
  delay(10);

  mySerial.begin(9600);
  Serial.println("Software serial initialized!");
  delay(10);
}

void loop(){
  issueCommand("AT");
  delay(500);
  readSerial();
  issueCommand("AT+CLIP=1");
  delay(500);
  readSerial();
  issueCommand("ATD9743451835");
  delay(500);
  readSerial();


  while(true){
    readSerial();
  }
}

void issueCommand(char* msg){
  mySerial.println(msg);
  Serial.print(msg);
  delay(10);
}

void readSerial(){
  while (mySerial.available()){
    Serial.write(mySerial.read());
    delay(10);
  }
}
