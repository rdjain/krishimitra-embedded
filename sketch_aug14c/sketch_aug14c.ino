//#include <Wire.h>
#include<SoftwareSerial.h>
//frame for router D1 on 
byte Router_on[] = {0x7E,0x00,0x10,0x17,0x01,0x00,0x13,0xA2,0x00,0x40,0xD7,0xF2,0x91,0xFF,0xFE,0x02,0x44,0x30,0x05,0x20};
//Frame for router D1 off
byte Router_off[] ={0x7E,0x00,0x10,0x17,0x01,0x00,0x13,0xA2,0x00,0x40,0xD7,0xF2,0x91,0xFF,0xFE,0x02,0x44,0x30,0x04,0x21};

SoftwareSerial mySerial(8,9);
void setup()
{
  mySerial.begin(9600);
 delay(5000);//delay of 5 seconds to ensure router and coordinator are joined to each other
 //delay not entirely necessary
}

void loop(){
   //after various trials serial.print(Router_on,20); kept causing the overloaded ambiguous error
   //Serial.write(Router_on,20); does it with no problems
   //the 20 tells the compiler how long the array is
   //Thank you PaulS from the Arduino forum for helping with this 
   
  mySerial.write(Router_on, 20);
  delay(400);
  mySerial.write(Router_off, 20);
  delay(400);
  
  
}
