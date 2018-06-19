#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Connecting to Wifi");
  WiFi.begin("DIGISOL_JOI", "mini@1234");
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}
void loop() {
  HTTPClient http;
  http.begin("http://192.168.2.107/sensorData/post.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.POST("fname=sonal&lname=kuchekar");
  String payload = http.getString();
  Serial.println(payload);
  //http.writeToStream(&Serial);
  http.end();
  delay(5000);
}
