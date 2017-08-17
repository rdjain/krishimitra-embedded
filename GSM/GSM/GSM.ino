#include <SoftwareSerial.h>

#define rxPin 10
#define txPin 11


SoftwareSerial mySerial(rxPin,txPin); // RX, TX

void issueCommand(char* msg){
  mySerial.println(msg);
  Serial.print(msg);
  delay(10);
}

void readSerial(){
  
  while (mySerial.available()){
    Serial.write(mySerial.read());
    delay(10);
    //i++;
  }
  //return (String (str));
}


int val=0;

void setup(){

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  Serial.begin(9600);
  Serial.println("Arduino serial initialized!");
  delay(10);

  mySerial.begin(9600);
  Serial.println("Software serial initialized!");
  delay(10);
  issueCommand("AT");
  delay(500);
  readSerial();
  issueCommand("ATS0=10");
  //delay(500);
  //readSerial();
  issueCommand("AT+CLIP=1");
  delay(500);
  readSerial();
  issueCommand("AT+QTONEDET=1");
  delay(500);
  readSerial();
  
  
}

void loop(){
  readSerial();
   val= mySerial.parseInt();
   if(val>47 && val<59){
    val-=48;
      
    }
    
  }
