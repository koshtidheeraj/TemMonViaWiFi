/* 
**  Connect the ESP8266 unit to an existing WiFi access point
**  For more information see http://42bots.com
*/

#include <ESP8266WiFi.h>

// Replace these with your WiFi network settings
const char* ssid = "dheeraj-hotspot"; //replace this with your WiFi network name
const char* password = "dheeraj123"; //replace this with your WiFi network password
const char* host = "10.42.0.1"; // host IP
const int port = 8080; // host port

void setup()
{
  delay(1000);
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("success!");
  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(5000);

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    return;
  } else {
    Serial.println("connection Successful");
//    return;
  }
  if(Serial.available()>0) {
    String temp = Serial.readString();
    temp = temp.substring(0,2);
    // We now create a URI for the request
    String url = "/input";
    url += "?sensor_number=";
    url += "1";
    url += "&temperature=";
    url += temp;
    Serial.println("URL created");
    
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" + 
                 "Connection: close\r\n\r\n");
  
    Serial.println("GET request sent");
  
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
  }
}
