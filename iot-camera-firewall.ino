//==================
//Basic code for connecting the camera //
//==================

// #include <WiFi.h>
// #include <WiFiClient.h>
// #include <WebServer.h>
// #include "esp_camera.h"
// #include "soc/soc.h"
// #include "soc/rtc_cntl_reg.h"

// const char* ssid = "";
// const char* password = "";

// WebServer server(80);

// // Function prototypes
// void handleRoot();
// void handleStream();

// void setup() {
//   Serial.begin(115200);
//   initCamera();
//   connectToWiFi();
//   setupRoutes();
// }

// void loop() {
//   server.handleClient();
// }

// void initCamera() {
//   camera_config_t config;
//   config.pin_pwdn = -1; // Power down is not used
//   config.pin_reset = -1; // Reset pin is not used
//   config.pin_xclk = 0;
//   config.pin_sscb_sda = 26;
//   config.pin_sscb_scl = 27;
//   config.pin_d7 = 35;
//   config.pin_d6 = 34;
//   config.pin_d5 = 39;
//   config.pin_d4 = 36;
//   config.pin_d3 = 21;
//   config.pin_d2 = 19;
//   config.pin_d1 = 18;
//   config.pin_d0 = 5;
//   config.pin_vsync = 25;
//   config.pin_href = 23;
//   config.pin_pclk = 22;
//   config.xclk_freq_hz = 20000000;
//   config.pixel_format = PIXFORMAT_JPEG;
  
//   if(psramFound()){
//     config.frame_size = FRAMESIZE_UXGA;
//     config.jpeg_quality = 10;
//     config.fb_count = 2;
//   } else {
//     config.frame_size = FRAMESIZE_SVGA;
//     config.jpeg_quality = 12;
//     config.fb_count = 1;
//   }
  
//   // Init camera
//   esp_err_t err = esp_camera_init(&config);
//   if (err != ESP_OK) {
//     Serial.printf("Camera init failed with error 0x%x", err);
//     return;
//   }
// }

// void connectToWiFi() {
//   Serial.println("Connecting to WiFi");
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Connecting to WiFi...");
//   }
//   Serial.println("Connected to WiFi");
// }

// void setupRoutes() {
//   server.on("/", HTTP_GET, handleRoot);
//   server.on("/stream", HTTP_GET, handleStream);
//   server.begin();
//   Serial.println("HTTP server started");
// }

// void handleRoot() {
//   server.send(200, "text/html", "<h1>ESP32-CAM Web Server</h1><p><a href=\"/stream\">Click here to view stream</a></p>");
// }

// void handleStream() {
//   camera_fb_t * fb = NULL;
//   fb = esp_camera_fb_get();
//   if (!fb) {
//     Serial.println("Camera capture failed");
//     server.send(500, "text/plain", "Camera capture failed");
//     return;
//   }

//   // Convert buffer to String
//   String response = String((const char*)fb->buf, fb->len);

//   server.send(200, "image/jpeg", response);
//   esp_camera_fb_return(fb);
// }

//
//============
// This Code has the connection with the twilio app for sending messages
//==============
//

//
// The main Vulnerability of the code is that can be hacked in routersploit
//


// #include <WebServer.h>
// #include <HTTPClient.h>
// #include <WiFi.h>
// #include "esp_camera.h"
// #include "soc/soc.h"
// #include "soc/rtc_cntl_reg.h"
// #include "base64.h"

// const char* ssid = "";
// const char* password = "";

// WebServer server(80);

// // Pin Definitions for Camera
// #define PWDN_GPIO_NUM     -1
// #define RESET_GPIO_NUM    -1
// #define XCLK_GPIO_NUM     0
// #define SIOD_GPIO_NUM     26
// #define SIOC_GPIO_NUM     27

// #define Y9_GPIO_NUM       35
// #define Y8_GPIO_NUM       34
// #define Y7_GPIO_NUM       39
// #define Y6_GPIO_NUM       36
// #define Y5_GPIO_NUM       21
// #define Y4_GPIO_NUM       19
// #define Y3_GPIO_NUM       18
// #define Y2_GPIO_NUM       5
// #define VSYNC_GPIO_NUM    25
// #define HREF_GPIO_NUM     23
// #define PCLK_GPIO_NUM     22

// // Twilio configuration
// const char* twilioServer = "api.twilio.com";
// const char* accountSid = "";
// const char* authToken = "";
// const char* twilioNumber = "";
// const char* recipientNumber = "";

// // Function prototypes
// void handleRoot();
// void handleStream();
// void sendSMS();
// void initCamera();
// void connectToWiFi();
// void setupRoutes();

// void setup() {
//   Serial.begin(115200);
//   initCamera();
//   connectToWiFi();
//   setupRoutes();
// }

// void loop() {
//   server.handleClient();
// }

// void initCamera() {
//   camera_config_t config;
//   config.ledc_channel = LEDC_CHANNEL_0;
//   config.ledc_timer = LEDC_TIMER_0;
//   config.pin_d0 = Y2_GPIO_NUM;
//   config.pin_d1 = Y3_GPIO_NUM;
//   config.pin_d2 = Y4_GPIO_NUM;
//   config.pin_d3 = Y5_GPIO_NUM;
//   config.pin_d4 = Y6_GPIO_NUM;
//   config.pin_d5 = Y7_GPIO_NUM;
//   config.pin_d6 = Y8_GPIO_NUM;
//   config.pin_d7 = Y9_GPIO_NUM;
//   config.pin_xclk = XCLK_GPIO_NUM;
//   config.pin_pclk = PCLK_GPIO_NUM;
//   config.pin_vsync = VSYNC_GPIO_NUM;
//   config.pin_href = HREF_GPIO_NUM;
//   config.pin_sscb_sda = SIOD_GPIO_NUM;
//   config.pin_sscb_scl = SIOC_GPIO_NUM;
//   config.pin_pwdn = PWDN_GPIO_NUM;
//   config.pin_reset = RESET_GPIO_NUM;
//   config.xclk_freq_hz = 20000000;
//   config.pixel_format = PIXFORMAT_JPEG;

//   if (psramFound()) {
//     config.frame_size = FRAMESIZE_UXGA;
//     config.jpeg_quality = 10;
//     config.fb_count = 2;
//   } else {
//     config.frame_size = FRAMESIZE_SVGA;
//     config.jpeg_quality = 12;
//     config.fb_count = 1;
//   }

//   esp_err_t err = esp_camera_init(&config);
//   if (err != ESP_OK) {
//     Serial.printf("Camera init failed with error 0x%x", err);
//     return;
//   }
// }

// void connectToWiFi() {
//   Serial.println("Connecting to WiFi");
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Connecting to WiFi...");
//   }
//   Serial.println("Connected to WiFi");
// }

// void setupRoutes() {
//   server.on("/", HTTP_GET, handleRoot);
//   server.on("/stream", HTTP_GET, handleStream);
//   server.on("/sendSMS", HTTP_GET, sendSMS);
//   server.begin();
//   Serial.println("HTTP server started");
// }

// void handleRoot() {
//   server.send(200, "text/html", "<h1>ESP32-CAM Web Server</h1><p><a href=\"/stream\">Click here to view stream</a></p>");
// }

// void handleStream() {
//   camera_fb_t * fb = NULL;
//   fb = esp_camera_fb_get();
//   if (!fb) {
//     Serial.println("Camera capture failed");
//     server.send(500, "text/plain", "Camera capture failed");
//     return;
//   }

//   String response = String((const char*)fb->buf, fb->len);
//   server.send(200, "image/jpeg", response);
//   esp_camera_fb_return(fb);
// }

// void sendSMS() {
//   HTTPClient http;
//   String url = "https://" + String(twilioServer) + "/2010-04-01/Accounts/" + String(accountSid) + "/Messages.json";
//   String postData = "To=" + String(recipientNumber) + "&From=" + String(twilioNumber) + "&Body=Hello+from+ESP32-CAM";

//   String auth = String(accountSid) + ":" + String(authToken);
//   String authHeader = "Basic " + base64::encode(auth);

//   http.begin(url);
//   http.addHeader("Authorization", authHeader);
//   http.addHeader("Content-Type", "application/x-www-form-urlencoded");

//   int httpResponseCode = http.POST(postData);

//   if (httpResponseCode > 0) {
//     String response = http.getString();
//     Serial.println(httpResponseCode);
//     Serial.println(response);
//   } else {
//     Serial.print("Error on sending POST: ");
//     Serial.println(httpResponseCode);
//   }

//   http.end();
// }

//===============
// This code can be exploited by using the ip address of the user... 
//===============

// #include <WebServer.h>
// #include <HTTPClient.h>
// #include <WiFi.h>
// #include "esp_camera.h"
// #include "soc/soc.h"
// #include "soc/rtc_cntl_reg.h"
// #include "base64.h"

// const char* ssid = "Your_WiFi_SSID";
// const char* password = "Your_WiFi_Password";

// const char* twilioServer = "api.twilio.com";
// const char* accountSid = "";
// const char* authToken = "";
// const char* twilioNumber = "";
// const char* recipientNumber = "";

// const char* validUsername = "admin";
// const char* validPassword = "password";

// WebServer server(80);

// // Pin Definitions for Camera
// #define PWDN_GPIO_NUM     -1
// #define RESET_GPIO_NUM    -1
// #define XCLK_GPIO_NUM     0
// #define SIOD_GPIO_NUM     26
// #define SIOC_GPIO_NUM     27

// #define Y9_GPIO_NUM       35
// #define Y8_GPIO_NUM       34
// #define Y7_GPIO_NUM       39
// #define Y6_GPIO_NUM       36
// #define Y5_GPIO_NUM       21
// #define Y4_GPIO_NUM       19
// #define Y3_GPIO_NUM       18
// #define Y2_GPIO_NUM       5
// #define VSYNC_GPIO_NUM    25
// #define HREF_GPIO_NUM     23
// #define PCLK_GPIO_NUM     22

// // Function prototypes
// void handleRoot();
// void handleLogin();
// void handleStream();
// void sendSMS();
// void initCamera();
// void connectToWiFi();
// void setupRoutes();

// bool isAuthenticated = false;

// void setup() {
//   Serial.begin(115200);
//   initCamera();
//   connectToWiFi();
//   setupRoutes();
// }

// void loop() {
//   server.handleClient();
// }

// void initCamera() {
//   //Camera initialization code
//   camera_config_t config;
//   config.ledc_channel = LEDC_CHANNEL_0;
//   config.ledc_timer = LEDC_TIMER_0;
//   config.pin_d0 = Y2_GPIO_NUM;
//   config.pin_d1 = Y3_GPIO_NUM;
//   config.pin_d2 = Y4_GPIO_NUM;
//   config.pin_d3 = Y5_GPIO_NUM;
//   config.pin_d4 = Y6_GPIO_NUM;
//   config.pin_d5 = Y7_GPIO_NUM;
//   config.pin_d6 = Y8_GPIO_NUM;
//   config.pin_d7 = Y9_GPIO_NUM;
//   config.pin_xclk = XCLK_GPIO_NUM;
//   config.pin_pclk = PCLK_GPIO_NUM;
//   config.pin_vsync = VSYNC_GPIO_NUM;
//   config.pin_href = HREF_GPIO_NUM;
//   config.pin_sscb_sda = SIOD_GPIO_NUM;
//   config.pin_sscb_scl = SIOC_GPIO_NUM;
//   config.pin_pwdn = PWDN_GPIO_NUM;
//   config.pin_reset = RESET_GPIO_NUM;
//   config.xclk_freq_hz = 20000000;
//   config.pixel_format = PIXFORMAT_JPEG;

//   if (psramFound()) {
//     config.frame_size = FRAMESIZE_UXGA;
//     config.jpeg_quality = 10;
//     config.fb_count = 2;
//   } else {
//     config.frame_size = FRAMESIZE_SVGA;
//     config.jpeg_quality = 12;
//     config.fb_count = 1;
//   }

//   esp_err_t err = esp_camera_init(&config);
//   if (err != ESP_OK) {
//     Serial.printf("Camera init failed with error 0x%x", err);
//     return;
//   }
// }

// void connectToWiFi() {
//   // WiFi connection code
//   Serial.println("Connecting to WiFi");
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Connecting to WiFi...");
//   }
//   Serial.println("Connected to WiFi");
// }

// void setupRoutes() {
//   server.on("/", HTTP_GET, handleRoot);
//   server.on("/login", HTTP_POST, handleLogin);
//   server.on("/stream", HTTP_GET, handleStream);
//   server.on("/sendSMS", HTTP_GET, sendSMS);
//   server.begin();
//   Serial.println("HTTP server started");
// }

// void handleRoot() {
//   if (!isAuthenticated) {
//     server.send(200, "text/html", "<h1>Login</h1><form action='/login' method='POST'>Username:<br><input type='text' name='username'><br>Password:<br><input type='password' name='password'><br><br><input type='submit' value='Submit'></form>");
//   } else {
//     server.send(200, "text/html", "<h1>ESP32-CAM Web Server</h1><p><a href=\"/stream\">Click here to view stream</a></p>");
//   }
// }

// void handleLogin() {
//   String username = server.arg("username");
//   String password = server.arg("password");

//   if (username.equals(validUsername) && password.equals(validPassword)) {
//     isAuthenticated = true;
//     server.sendHeader("Location", "/stream");
//     server.send(302, "text/plain", "");
//   } else {
//     isAuthenticated = false;
//     server.send(401, "text/plain", "Unauthorized");
//   }
// }

// void handleStream() {
//   // Stream handling code without vulnerability
//   if (!isAuthenticated) {
//     server.send(401, "text/plain", "Unauthorized");
//     return;
//   }
//   camera_fb_t * fb = NULL;
//   fb = esp_camera_fb_get();
//   if (!fb) {
//     Serial.println("Camera capture failed");
//     server.send(500, "text/plain", "Camera capture failed");
//     return;
//   }

//   // Encode the image data in Base64 format
//   String base64Data = base64::encode(fb->buf, fb->len);
  
//   // Send the Base64 encoded image data in the HTTP response
//   server.send(200, "text/plain", base64Data);
  
//   // Free the camera frame buffer
//   esp_camera_fb_return(fb);
// }

// void sendSMS() {
//   // Send SMS using Twilio
//   HTTPClient http;
//   String url = "https://" + String(twilioServer) + "/2010-04-01/Accounts/" + String(accountSid) + "/Messages.json";
//   String postData = "To=" + String(recipientNumber) + "&From=" + String(twilioNumber) + "&Body=Hello+from+ESP32-CAM";

//   String auth = String(accountSid) + ":" + String(authToken);
//   String authHeader = "Basic " + base64::encode(auth);

//   http.begin(url);
//   http.addHeader("Authorization", authHeader);
//   http.addHeader("Content-Type", "application/x-www-form-urlencoded");

//   int httpResponseCode = http.POST(postData);

//   if (httpResponseCode > 0) {
//     String response = http.getString();
//     Serial.println(httpResponseCode);
//     Serial.println(response);
//   } else {
//     Serial.print("Error on sending POST: ");
//     Serial.println(httpResponseCode);
//   }

//   http.end();
// }

//===================
// Secured Code for Iot Devices 
//==================

#include <WebServer.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include "esp_camera.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "base64.h"

// WiFi credentials
const char* ssid = ""; // Change to your WiFi SSID
const char* password = ""; // Change to your WiFi password

// Twilio configuration
const char* twilioServer = "api.twilio.com";
const char* accountSid = "";
const char* authToken = "";
const char* twilioNumber = ""; // Twilio phone number
const char* recipientNumber = ""; // Recipient phone number

// Valid login credentials
const char* validUsername = "admin"; // Change to your desired username
const char* validPassword = "password"; // Change to your desired password

WebServer server(80); // Web server instance

// Pin Definitions for Camera
#define PWDN_GPIO_NUM     -1
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM     0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM       5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

bool isAuthenticated = false; // Variable to track authentication status

// Function prototypes
void handleRoot();
void handleLogin();
void handleStream();
void sendSMS();
void initCamera();
void connectToWiFi();
void setupRoutes();
void sendSMSUnauthorizedAccess(String ipAddress); // New function declaration

void setup() {
  Serial.begin(115200); // Start serial communication
  initCamera(); // Initialize camera
  connectToWiFi(); // Connect to WiFi
  setupRoutes(); // Setup HTTP routes
}

void loop() {
  server.handleClient(); // Handle client requests
}

void initCamera() {
  // Camera initialization code
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if (psramFound()) {
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
}

void connectToWiFi() {
  // WiFi connection code
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void setupRoutes() {
  // Define HTTP routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/login", HTTP_POST, handleLogin); // Changed method to POST
  server.on("/stream", HTTP_GET, handleStream);
  server.on("/sendSMS", HTTP_GET, sendSMS);
  server.begin();
  Serial.println("HTTP server started");
}

void handleRoot() {
  // Handle root request
  if (!isAuthenticated) {
    // If not authenticated, show login form
    server.send(200, "text/html", "<h1>Login</h1><form action='/login' method='POST'>Username:<br><input type='text' name='username'><br>Password:<br><input type='password' name='password'><br><br><input type='submit' value='Submit'></form>");
  } else {
    // If authenticated, show stream link
    server.send(200, "text/html", "<h1>ESP32-CAM Web Server</h1><p><a href=\"/stream\">Click here to view stream</a></p>");
  }
}

void handleLogin() {
  // Handle login request
  String username = server.arg("username");
  String password = server.arg("password");

  // Get the client's IP address
  IPAddress clientIP = server.client().remoteIP();

  // Define the expected IP address
  IPAddress expectedIP(192, 168, 1, 100); // Change to your expected IP address

  // Compare the client's IP address with the expected IP address
  if (clientIP == expectedIP && username.equals(validUsername) && password.equals(validPassword)) {
    // If IP address and credentials match, set isAuthenticated to true
    isAuthenticated = true;
    server.sendHeader("Location", "/stream");
    server.send(302, "text/plain", "");
  } else {
    // If IP address or credentials don't match, set isAuthenticated to false
    isAuthenticated = false;
    // Print vulnerability message to serial monitor
    Serial.println("Device is vulnerable. Unauthorized access attempted from IP address: " + clientIP.toString());
    // Send SMS to user about unauthorized access
    sendSMSUnauthorizedAccess(clientIP.toString());
    server.send(401, "text/plain", "Unauthorized");
  }
}

void handleStream() {
  // Handle stream request
  if (!isAuthenticated) {
    // If not authenticated, deny access
    server.send(401, "text/plain", "Unauthorized");
    return;
  }
  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get();
  if (!fb) {
    // If camera capture failed, send error response
    Serial.println("Camera capture failed");
    server.send(500, "text/plain", "Camera capture failed");
    return;
  }
    // Encode the image data in Base64 format
  String base64Data = base64::encode(fb->buf, fb->len);
  
  // Send the Base64 encoded image data in the HTTP response
  server.send(200, "text/plain", base64Data);
  
  // Free the camera frame buffer
  esp_camera_fb_return(fb);
}

void sendSMS() {
  // Send SMS using Twilio
  HTTPClient http;
  String url = "https://" + String(twilioServer) + "/2010-04-01/Accounts/" + String(accountSid) + "/Messages.json";
  String postData = "To=" + String(recipientNumber) + "&From=" + String(twilioNumber) + "&Body=Hello+from+ESP32-CAM";

  String auth = String(accountSid) + ":" + String(authToken);
  String authHeader = "Basic " + base64::encode(auth);

  http.begin(url);
  http.addHeader("Authorization", authHeader);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpResponseCode = http.POST(postData);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  } else {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}

void sendSMSUnauthorizedAccess(String ipAddress) {
  // Send SMS to notify unauthorized access attempt
  String message = "Unauthorized access attempted from IP: " + ipAddress;
  String url = "https://" + String(twilioServer) + "/2010-04-01/Accounts/" + String(accountSid) + "/Messages.json";
  String postData = "To=" + String(recipientNumber) + "&From=" + String(twilioNumber) + "&Body=" + message;

  String auth = String(accountSid) + ":" + String(authToken);
  String authHeader = "Basic " + base64::encode(auth);

  HTTPClient http;
  http.begin(url);
  http.addHeader("Authorization", authHeader);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpResponseCode = http.POST(postData);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  } else {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}


  

