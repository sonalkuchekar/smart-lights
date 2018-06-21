#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
int pir=D2;
int value=0;
void setup() {
  Serial.begin(9600);
  pinMode(pir, INPUT);
  Serial.println();
  
  Serial.println("Connecting to Wifi");
  WiFi.begin("sona", "sona@123");
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}
void loop() {
long state = digitalRead(pir);

 if (state == HIGH) 
 {
   // Serial.println("1");
    value = 1;
  } 
  else 
  {
    //  Serial.println("0");
    value = 0;
  }

  HTTPClient http;
  http.begin("http://192.168.43.38/sensorData/post.php");
  http.addHeader("Content-Type","application/x-www-form-urlencoded");
  http.POST("pirsensor1=" + String(value));
  String payload = http.getString();
  Serial.println("value="+payload);
  //http.writeToStream(&Serial);
  http.end();
  delay(5000);
}
