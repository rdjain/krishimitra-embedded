#include <Thread.h>
#include <ThreadController.h>
#include<SoftwareSerial.h>
#define rxPin 10
#define txPin 11
#define tempPin A0

SoftwareSerial mySerial(rxPin,txPin); // RX, TX
SoftwareSerial zigSerial(8,9);
ThreadController control = ThreadController();
Thread gsmThread = Thread();
//Thread blinkThread = Thread();
Thread datalogThread = Thread();
//Thread mp3Thread = Thread();
//frame for router D1 on 
byte Router_on1[] = {0x7E,0x00,0x10,0x17,0x01,0x00,0x13,0xA2,0x00,0x40,0xD7,0xF2,0x91,0xFF,0xFE,0x02,0x44,0x30,0x05,0x20};
//Frame for router D1 off
byte Router_off1[] ={0x7E,0x00,0x10,0x17,0x01,0x00,0x13,0xA2,0x00,0x40,0xD7,0xF2,0x91,0xFF,0xFE,0x02,0x44,0x30,0x04,0x21};
unsigned short int val=0;
String num = "" ;
unsigned short int count = 0;
unsigned short int access = 5 ;
int cond;
int R1= 470; //Divider Resistance
int Ra=50; //Resistance of powering Pins for conductivity probe
// Pin Diagram    Vin-----Ra--R1----Analogpin----Rc---Ra-----Gnd

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
      if (access < 4){
        start=millis();
        while((millis()-start) <= 25000 ){
        Serial.println("Access Granted");
        playMP3();
        val= mySerial.parseInt();
        if( val>48 && val<53 ){
            val-=48;
            Serial.println(val); 
            if(val == 1 || val == 2 ){
            Serial.println("MotorControl loop entered!");
            xbeeMotorControl( access , val );
        }
//            count = 0;
//            issueCommand("ATH");
//            access = 5 ;
            break ;
            }
        }  
            count = 0;    //part of while loop
            issueCommand("ATH");
            access = 5 ;
      }
      else if(access == 4) {
            issueCommand("ATH");
            access = 5 ;
            count = 0;
          }

       Serial.println("bleh!");
       
  }

void xbeeMotorControl(int access, int val){
    
    if(access == 3 && val == 1){  // 9743451835
        zigSerial.write(Router_on1, 20);
      } 
      else if(access == 3 && val == 2){ //9743451835
        zigSerial.write(Router_off1, 20);
      } 
  }
//void dataLogger(){
//  
//  float PPMconversion=0.64;
//  //*************Compensating for Temperature() ************************************//
//  //0.019 is generaly considered the standard for plant nutrients 
//  float Temperature()Coef = 0.019; //this changes depending on what chemical we are measuring
//  float K=2.88; //Cell Constant
//  float EC=0;
//  float EC25 =0;
//  int ppm =0;
//  float raw= 0;
//  float Vin= 5;
//  float Vdrop= 0;
//  float Rc= 0;
//  float buffer=0;
//
//  raw= analogRead(ECPin);     //Code to read data from XBee
//  raw= analogRead(ECPin);   // First reading will be low beause if charged a capacitor so consider the second one
//  Vdrop= (Vin*raw)/1024.0;
//  Rc=(Vdrop*R1)/(Vin-Vdrop);
//  Rc=Rc-Ra; //acounting for Digital Pin Resitance
//  EC = 1000/(Rc*K);
//  EC25  =  EC/ (1+ Temperature()Coef*(Temperature()-25.0));
//  ppm=(EC25)*(PPMconversion*1000);
//
//}

void playMP3(){
  
    if(digitalRead(6) == HIGH ){
        digitalWrite(7,LOW);
        delay(350);
        digitalWrite(7,HIGH);
      } 
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

float Temperature(){
    float temp = (analogRead(tempPin)*0.488758);
    return(temp);
  }

unsigned short int numCheck ( String numb){
  
    if ( numb == "7892953709"){ 
        access = 1;
      } 
     else if ( numb == "9986277113"){ 
        access = 2;
      } 
     else if ( numb == "9743451835"){ 
        access = 3;
      } 

     else {access = 4;} 
     return(access);
  }



  
void setup(){
  
      pinMode(rxPin, INPUT);
      pinMode(txPin, OUTPUT);
      pinMode(8,INPUT); //XBee RX
      pinMode(9,OUTPUT);  //XBee TX
      pinMode(13,OUTPUT);
      pinMode(6,INPUT);
      pinMode(7,OUTPUT);
      pinMode(A0,INPUT); 
      
      Serial.begin(9600);
      Serial.println("Arduino serial initialized!");
      delay(10);
    
      mySerial.begin(9600);
      Serial.println("Software serial initialized!");
      delay(10);
      
      zigSerial.begin(9600);
      Serial.println("Zig Serial Initialized!");
      delay(10);
      
      issueCommand("AT");
      delay(50);
      
      issueCommand("ATS0=3");
      delay(50);
      
      issueCommand("AT+CLIP=1");
      delay(50);
      
      issueCommand("AT+QTONEDET=1");
      delay(50);

      issueCommand("AT+QISTAT");
      delay(50);

      issueCommand("AT+QIACT");
      delay(50);

      issueCommand("AT+QIDNSIP=1");
      delay(50);

      delay(5000);
      
      gsmThread.onRun(pollGSM);
      gsmThread.setInterval(250);
      
//      blinkThread.onRun(blinkLED);
//      blinkThread.setInterval(100);
      
//      datalogThread.onRun(blinkLED);
//      datalogThread.setInterval(2000);
      
//      mp3Thread.onRun(playMP3);
//      mp3Thread.setInterval(2000);
      
      control.add(&gsmThread);
//      control.add(&blinkThread);
//      control.add(&datalogThread);
//      control.add(&mp3Thread);
      
}

void loop(){
    control.run();
    
  }
