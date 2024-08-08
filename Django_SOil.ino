#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid = "JMD109_2.4";
const char* password = "JMD01109";

// Replace with your ngrok URL and endpoint (using HTTPS)
const char* serverUrl = "http://192.168.1.10:8000/sensor/receive/";

unsigned long previousMillis = 0;
const long interval = 100; // Interval in milliseconds (10 seconds)

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(serverUrl) + "?temperature=23.5&humidity=60&status=active";
    http.begin(url);
    
    int httpResponseCode = http.GET();
    
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Response code: " + String(httpResponseCode));
      Serial.println("Response: " + response);
    } else {
      Serial.println("Error code: " + String(httpResponseCode));
    }

    http.end();
  }

  delay(100); // Send data every 10 seconds
}
