#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid = "JMD109_2.4";
const char* password = "JMD01109";

// Replace with your ngrok URL and endpoint (using HTTPS)
const char* serverUrl = "http:///503c-2402-a00-408-3e9a-1862-abf1-d78-d22b.ngrok-free.app/api/data/";

unsigned long previousMillis = 0;
const long interval = 10000; // Interval in milliseconds (10 seconds)

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");

   // Print the IP address of the ESP32
  IPAddress ip = WiFi.localIP();
  Serial.print("ESP32 IP Address: ");
  Serial.println(ip);
}

void loop() {
  unsigned long currentMillis = millis();

  // Check if 10 seconds have passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Save the last time you sent the request

    // Make the POST request
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      
      // Specify the request type and URL
      http.begin(serverUrl);
      http.addHeader("Content-Type", "application/json");

      // Create the payload
      String payload = "{\"temperature\":23.5,\"humidity\":60,\"status\":\"active\"}";

      // Send the POST request
      int httpResponseCode = http.POST(payload);

      // Print the response
      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Response code: " + String(httpResponseCode));
        Serial.println("Response: " + response);
      } else {
        Serial.println("Error code: " + String(httpResponseCode));
      }

      // End the HTTP request
      http.end();
    }
  }
}
