#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#define SSID "esw"
#define PASS "esw1234"
#define HOST "esw5009.p-e.kr"
uint16_t port = 5009;
int led = 13;
SoftwareSerial serial(2,3);
using namespace websockets;
WebsocketsClient client;
bool connected = false;
void setup() {
 pinMode(led,OUTPUT);
 initialize();
}
void initialize(){
  Serial.begin(9600);
  WiFi.begin(SSID,PASS);
  while(WiFi.status() != WL_CONNECTED)

  connected = client.connect(HOST,port,"/");
  client.onMessage([&](WebsocketsMessage msg){
    String cmd = msg.data();
    if(cmd.equals("NOTICE")){
        digitalWrite(led,HIGH);
    }else if(cmd.equals("RESET_LED")){
      digitalWrite(led,LOW);
    }
  });
  if(connected){
    String cmd = "POST_222000105";
    client.send(cmd);
  }
}

void loop() {
  if(! connected){
    connected = client.connect(HOST,port,"/");
  }
  if(client.available()){
    client.poll();
  }
  delay(1000);
}
