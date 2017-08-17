#include <SoftwareSerial.h>

#define rxPin 10
#define txPin 11


SoftwareSerial mySerial(rxPin,txPin); // RX, TX

void issueCommand(char* msg){
  mySerial.println(msg);
  Serial.print(msg);
  delay(10);
}

//void readSerial(){
//  
//  while (mySerial.available()){
//    Serial.write(mySerial.read());
//    delay(10);
//    //i++;
//  }
//
//}


int val=0;
String pnum;
void setup(){
  

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  Serial.begin(115200);
  Serial.println("Arduino serial initialized!");
  delay(10);

  mySerial.begin(9600);
  Serial.println("Software serial initialized!");
  delay(10);
  issueCommand("AT");
  delay(50);
  //readSerial();
  issueCommand("ATS0=3");
  //delay(500);
  //readSerial();
  issueCommand("AT+CLIP=1");
  delay(50);
  //readSerial();
  issueCommand("AT+QTONEDET=1");
  delay(50);
  //readSeral();
  
  
}

void loop(){


  val= mySerial.parseInt();
    if(val>48 && val<53){
    val-=48;
    Serial.println(val); 
    }
    
  if(mySerial.find("+9"))
      {
    Serial.println(mySerial.readStringUntil('"'));
      }
           
  }
