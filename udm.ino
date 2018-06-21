//udm 1 - trig1,echo1
//udm 2 - trig2,echo2

#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>

int trig1 = D1;
int echo1 = D2;
int trig2 = D4;
int echo2 = D3;
long duration=0;
int maxdist1 = 400;
int maxdist2 = 400;
int dist1=0;
int dist2=0;
int i=0;
int count=0;
int countchange = 0;
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  /*Serial.println("Connecting to Wifi");
  WiFi.begin("wow", "ven@2801");
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");*/
  pinMode(trig1,OUTPUT);
  pinMode(echo1,INPUT);
  pinMode(trig2,OUTPUT);
  pinMode(echo2,INPUT);
}
int udm1() //returns distance calculated by udm1
{
  float dist;
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  duration = pulseIn(echo1, HIGH);
  dist = duration*0.034/2;
  return dist;
}
int udm2() //returns distance calculated ny udm2
{
  float dist;
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  duration = pulseIn(echo2, HIGH);
  dist = duration*0.034/2;
  return dist;
}
void checkEntry()
{
  for(i=0;i<20;i++)
    {
      dist2 = udm2();
      if(dist2<maxdist2)
      {
        Serial.println("Crossed udm2 second");
        Serial.println("a person entered room");
        count++;
        break;
      }
    } 
}
void checkExit()
{
  for(i=0;i<20;i++)
    {
      dist1 = udm1();
      if(dist1<maxdist1)
      {
        Serial.println("Crossed udm1 second");
        Serial.println("a person left room");
        count--;
        break;
      }
    }
}
/*void sendCount() //sends the count of people to the server
{
    HTTPClient http;
    String postData = "http://192.168.43.195/udm.php?count=";
    postData.concat(count);
    http.begin(postData);
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.print("Count sent : ");
      Serial.println(payload);
    }
}*/
void loop() {
  // put your main code here, to run repeatedly:
  dist1 = udm1();
  Serial.print("distance calc by udm1 :");
  Serial.println(dist1);
  if(dist1<maxdist1)
  {
    Serial.println("Crossed udm1 first");
    checkEntry();
  }
  Serial.print("distance calc by udm2 :");
  dist2 = udm2();
  Serial.println(dist2);
  if(dist2<maxdist2)
  {
    Serial.println("Crossed udm2 first");
    checkExit();
  }
    Serial.print("No of people currently in room : ");
    Serial.println(count);
    delay(4000);
    Serial.println("Starting in 1sec");
  //sendCount();
  delay(5000);
}

