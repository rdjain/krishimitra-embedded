#include<SoftwareSerial.h>
SoftwareSerial mySerial(9,10);
void issueCommand(char* msg){
    mySerial.println(msg);
    Serial.print(msg);
    delay(10);
    }
void test(){
  while(mySerial.available()>0){
    test();
    delay(10);
    }
  }
void setup() {
  pinMode(9,INPUT);
  pinMode(10,OUTPUT);
  mySerial.begin(9600);
  Serial.begin(9600);
    // put your setup code here, to run once:
        char* data="moisture=22&EC=30&user=9986277113";
        issueCommand("AT+QIDEACT\r\n"); 
         delay(400);
        issueCommand("AT+CGATT=1\r\n");
        delay(2000);test();
        issueCommand("AT+QIMUX=0");
        delay(2000);test();
        issueCommand("AT+QIREGAPP=\"airtelgrps.com\",\"smartstreet\",\"smartstreet001\"");
        delay(2000);test();
        issueCommand("AT+QISTAT");
        delay(2000);test();
        issueCommand("AT+QIACT");
        delay(2000);test();
        issueCommand("AT+QILOCIP");
        delay(2000);test();
        issueCommand("AT+QIDNSIP=1");
        delay(2000);test();
        issueCommand("AT+QIOPEN=\"TCP\",\"farmit.herokuapp.com\",\"80\"");
        delay(8000);test();
        issueCommand("AT+QISEND");
        delay(1000);test();
        issueCommand("POST /api/postinfo HTTP/1.1");
        mySerial.write(0x0D);
       mySerial.write(0x0A);
        delay(1000);test();
        issueCommand("HOST: farmit.herokuapp.com");
       mySerial.write(0x0D);
       mySerial.write(0x0A);
       delay(1000);test();
       issueCommand("Cache-Control: no-cache");
       mySerial.write(0x0D);
       mySerial.write(0x0A);
       delay(1000);test();
       issueCommand("Content-Type: application/x-www-form-urlencoded");
        mySerial.write(0x0D);
       mySerial.write(0x0A);
       delay(1000);test();
        issueCommand("Content-Length: 34");
        mySerial.write(0x0D);
       mySerial.write(0x0A);
       mySerial.write(0x0D);
       mySerial.write(0x0A);
       delay(1000);test();
        issueCommand(data);
        mySerial.write(0x0D);
       mySerial.write(0x0A);
       mySerial.write(0x0D);
       mySerial.write(0x0A);
       mySerial.write(0x1A);
       delay(5000);test();
}

void loop() {
  // put your main code here, to run repeatedly:

}
//issueCommand("AT+QIDEACT"); 
//          delay(4000);test();
//        issueCommand("AT+CGATT=1");
//        delay(2000);test();
//        issueCommand("AT+QIMUX=0");
//        delay(2000);test();
//        issueCommand("AT+QIREGAPP=\"airtelgrps.com\",\"smartstreet\",\"smartstreet001\"");
//        delay(2000);test();
//        issueCommand("AT+QISTAT");
//        delay(2000);test();
//        issueCommand("AT+QIACT");
//        delay(2000);test();
//        issueCommand("AT+QILOCIP");
//        delay(2000);test();
//        issueCommand("AT+QIDNSIP=1");
//        delay(2000);test();
//        issueCommand("AT+QIOPEN=\"TCP\",\"api.aercloud.aeris.com\",\"80\"");
//        delay(8000);test();
//        issueCommand("AT+QISEND");
//        delay(1000);test();
//        issueCommand("POST /v1/20719/scls/test_sample1/containers/PIC/contentInstances?apiKey=cf662b87-fd96-11e6-83b7-6177f2f76bcc HTTP/1.1");
//        mySerial.write(0x0D);
//       mySerial.write(0x0A);
//        delay(1000);test();
//        issueCommand("HOST: api.aercloud.aeris.com");
//       mySerial.write(0x0D);
//       mySerial.write(0x0A);
//       delay(1000);test();
//       issueCommand("Accept: application/json");
//        mySerial.write(0x0D);
//       mySerial.write(0x0A);
//       delay(1000);test();
//       issueCommand("Content-Type: application/json");
//        mySerial.write(0x0D);
//       mySerial.write(0x0A);
//       delay(1000);test();
//        issueCommand("Content-Length: 50");
//        mySerial.write(0x0D);
//       mySerial.write(0x0A);
//       mySerial.write(0x0D);
//       mySerial.write(0x0A);
//       delay(1000);test();
//        issueCommand("{\"DeviceID\":\"001\",\"Time\":\"01:02:03\",\"status\":\"0N\"}");
//        mySerial.write(0x0D);
//       mySerial.write(0x0A);
//       mySerial.write(0x0D);
//       mySerial.write(0x0A);
//       mySerial.write(0x1A);
//       delay(5000);test();
