#include <ESP8266WiFi.h>
const char* ssid     = "SSID";
const char* password = "PASSWORD";

const char* host = "http://farmit.herokuapp.com";

void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

 while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }


 String data = "moisture=20&EC=30&user=9986277113"; 

   Serial.print("Requesting POST: ");
   // Send request to the server:
   client.println("POST /api/postinfo HTTP/1.1");
   client.println("Host: farmit.herokuapp.com");
   client.println("Cache-Control: no-cache");
   client.println("Content-Type: application/x-www-form-urlencoded");
   client.print("Content-Length: ");
   client.println(data.length());
   client.println();
   client.print(data);

   delay(2000); // Can be changed
  if (client.connected()) { 
    client.stop();  // DISCONNECT FROM THE SERVER
  }
  Serial.println();
  Serial.println("closing connection");
  delay(5000);
}
void loop(){}
