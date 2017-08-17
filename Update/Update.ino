#include <SoftwareSerial.h>

#define rxPin 10
#define txPin 11


SoftwareSerial mySerial(rxPin,txPin); // RX, TX

void issueCommand(char* msg){
    mySerial.println(msg);
    Serial.print(msg);
    delay(10);
    }

unsigned short int numCheck ( String num){
    if ( num == "7892953709"){
        return(1);
      } 
     else {return(2);}
  }
  unsigned short int val=0;
  String num = "" ;
  unsigned short int count = 0;
  unsigned short int access = 3 ;
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
      delay(50);
      issueCommand("ATS0=3");
      delay(50);
      issueCommand("AT+CLIP=1");
      delay(50);
      issueCommand("AT+QTONEDET=1");
      delay(50);
      
      
}

void loop(){
    if(count == 0){
      delay(10);
       Serial.println("cntloop\n");
      if(mySerial.find("+91")){
          Serial.println("hi");
          Serial.println(num=mySerial.readStringUntil('"'));
          access=numCheck(num);
          count = 1;
          }
      }
    if (access == 1){
      Serial.println("Access Granted");
      val= mySerial.parseInt();
      if( val>48 && val<53 ){
          val-=48;
          Serial.println(val); 
          count = 0;
          issueCommand("ATH");
          access = 3 ;
          }
    }
    else if(access == 2) {
          issueCommand("ATH");
          access = 3 ;
          count = 0;
        }
     Serial.println("bleh!");

     
  }
