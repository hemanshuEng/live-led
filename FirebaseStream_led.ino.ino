//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseStream_ESP8266 is a sample that stream bitcoin price from a
// public Firebase and optionally display them on a OLED i2c screen.

#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>


// Set these to run example.
#define WIFI_SSID "VM7979384"
#define WIFI_PASSWORD "dzhg7CcFskm5"


void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin("mcu-led.firebaseio.com");
  Firebase.stream("/led"); 
  pinMode(16,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(16,Firebase.getInt("led/LEDA"));
  digitalWrite(5,Firebase.getInt("led/LEDB"));
  digitalWrite(2,Firebase.getInt("led/LEDC"));
  digitalWrite(14,Firebase.getInt("led/LEDD"));
  digitalWrite(4,Firebase.getInt("led/LEDE"));
  digitalWrite(13,Firebase.getInt("led/LEDF"));
}


void loop() {
  if (Firebase.failed()) {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
    ESP.reset();
  }
  
  if (Firebase.available()) {
     FirebaseObject event = Firebase.readEvent();
     String eventType = event.getString("type");
     String path = event.getString("path");
     eventType.toLowerCase();
     path.toLowerCase();
     
     Serial.print("event: ");
     Serial.println(eventType);
      Serial.print("path: ");
     Serial.println(path);
     if (eventType == "patch") {
//       String led = event.getString("path");
//       int data = event.getInt("data"); 
//       Serial.print("path: ");
//       Serial.println(event.getString("path"));
//       Serial.print("data: ");
//       Serial.println(event.getInt("data"));
//       if(led =="/LEDA")
//       {
//        digitalWrite(LED_BUILTIN, data);
//        Serial.print("case 1");
//       }
        digitalWrite(16,Firebase.getInt("led/LEDA"));
        digitalWrite(5,Firebase.getInt("led/LEDB"));
        digitalWrite(2,Firebase.getInt("led/LEDC"));
        digitalWrite(14,Firebase.getInt("led/LEDD"));
        digitalWrite(4,Firebase.getInt("led/LEDE"));
        digitalWrite(13,Firebase.getInt("led/LEDF"));
        
       
     }
  }   
}
