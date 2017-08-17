WiFiClient client;

void connect_to_wifi()
{
  WiFi.begin(ssid, password);
  int tries=0;
  for(tries=0;tries<20 && WiFi.status()!=WL_CONNECTED;++tries)
  {
    digitalWrite(D0,(tries&1)==1?HIGH:LOW);
    Serial.print(".");
    delay(500);
  }
  if (tries>=20)
  {
    status=0;
    Serial.println("Failed to connect to WiFi");
  }
  else
  {
    Serial.println("Connected to WiFi");
    if (client.connect(addr, port))
    {
      Serial.println("Connected to server");
      client.println("Connected");
    }
    else
    {
      Serial.println("Failed to connect to server");
      status=0;
    }
  }
}

void setup() {
  pinMode(D0,OUTPUT);
  digitalWrite(D0,LOW);
  Serial.begin(115200);
  while (!Serial) delay(10);
  connect_to_wifi();
}

void loop() {
  if (status==0)
  {
    digitalWrite(D0,HIGH);
    delay(300);
    digitalWrite(D0,LOW);
    delay(300);
  }
  else
  {
    digitalWrite(D0,HIGH);
    delay(100);
    digitalWrite(D0,LOW);
    delay(100);
    int av=Serial.available();
    if (av>0)
    {
      client.println(av);
      for(int i=0;i<av;++i)
      {
        int c=Serial.read();
        client.print(char(c));
      }
    }
  }
}
