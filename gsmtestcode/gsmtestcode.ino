


void setup(){

  Serial.begin(9600);
  Serial.println("Arduino serial initialized!");
  delay(10);

//  mySerial.begin(9600);
  Serial.println("Software serial initialized!");
  delay(10);
 
  
}
int Count = 0;
String data = "";
void loop(){
  
   
   if(Count%10 ==0)
  { 
   Serial.println("AT");
   delay(10);
   if(Serial.available()>0)

    Serial.println("hi");
   data = Serial.readStringUntil('\r');
   Serial.println(data);
   //}
  }
  //Serial.println("ATH");
  Count++;
  delay(1000);
}
