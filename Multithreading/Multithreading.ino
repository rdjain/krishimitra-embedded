#include <Thread.h>
#include <ThreadController.h>
#include<SoftwareSerial.h>
#define rxPin 10
#define txPin 11



SoftwareSerial mySerial(rxPin,txPin); // RX, TX
ThreadController control = ThreadController();
Thread gsmThread = Thread();
Thread blinkThread = Thread();

unsigned short int val=0;
String num = "" ;
unsigned short int count = 0;
unsigned short int access = 3 ;

void pollGSM(){
    long int start;
    if(count == 0){
        delay(10);
         Serial.println("cntloop\n");
        if(mySerial.find("+91")){
            Serial.println("hi");
            num = mySerial.readStringUntil('"');
            Serial.println(num);
            access=numCheck(num);
            count = 1;
            }
        }
      if (access == 1){
        start=millis();
        while((millis()-start) <= 18000 ){
        Serial.println("Access Granted");
        val= mySerial.parseInt();
        if( val>48 && val<53 ){
            val-=48;
            Serial.println(val); 
//            count = 0;
//            issueCommand("ATH");
//            access = 3 ;
            break ;
            }
        }  
            count = 0;    //part of while loop
            issueCommand("ATH");
            access = 3 ;
      }
      else if(access == 2) {
            issueCommand("ATH");
            access = 3 ;
            count = 0;
          }
       Serial.println("bleh!");
  }



void blinkLED(){
  
    digitalWrite(13,HIGH);
    delay(500);
    Serial.println(millis());
    digitalWrite(13,LOW);
    delay(500);
    Serial.println(millis());
  }


  
void issueCommand(char* msg){
    mySerial.println(msg);
    Serial.print(msg);
    delay(10);
    }

   

unsigned short int numCheck ( String numb){
    if ( numb == "7892953709" || numb == "9986277113" || numb == "9743451835"){
        return(1);
      } 
     else {return(2);}
  }


  
//unsigned short int val=0;
//String num = "" ;
//unsigned short int count = 0;
//unsigned short int access = 3 ;


  
void setup(){
  
      pinMode(rxPin, INPUT);
      pinMode(txPin, OUTPUT);
      pinMode(13,OUTPUT);
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
      gsmThread.onRun(pollGSM);
      gsmThread.setInterval(250);
      blinkThread.onRun(blinkLED);
      blinkThread.setInterval(100);
      control.add(&gsmThread);
      control.add(&blinkThread);
      
}

void loop(){
    control.run();
    
  }
