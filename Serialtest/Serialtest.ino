#include<SoftwareSerial.h>
SoftwareSerial nodeSerial(11,12);

void setup() {
  // put your setup code here, to run once:
  pinMode(11,INPUT);
  pinMode(12,OUTPUT);
  Serial.begin(115200);
  
}
void loop() {
  // put your main code here, to run repeatedly:
  if(nodeSerial.find("Weather")){
    while(Serial.available()>0){
      nodeSerial.println(Serial.read());
      delay(10);
      }
    String message = Serial.readStringUntil(':');
  }
}
