/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <esp_now.h>
#include <WiFi.h>
//#include <ezButton.h>

#define VRX_PIN  A0 // ESP32 pin GPIO36 (ADC0) connected to VRX pin
#define VRY_PIN  A3 // ESP32 pin GPIO39 (ADC3) connected to VRY pin
#define SW_PIN   17 // ESP32 pin GPIO17 connected to SW  pin
int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis
int bValue = 0; // To store value of the button


//ezButton button(SW_PIN); // joystick button


// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xC8, 0xC9, 0xA3, 0x38, 0xFA, 0x99};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  
  // gyroscope/imaging information  (send a string with the correct "command"/gesture  -  If no gestures made, send a "NULL" or "none")
  char gesture[32] = "hello";

  // joystick information (string that can be u, d, l, r, n  standing for up, down, left, right, none)
  char joystick_direction;

  // button information (button to determine the function of the joystick)
  bool state_button;

} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  //button.setDebounceTime(50); // set debounce time to 50 milliseconds
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() { // -----------------------------------------------------------------------------------------------


  // CONDITIONS

  // read conditions of the joystick -> x and y analog values
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);

  Serial.println(xValue);
  Serial.println(yValue);

  bValue = false;//button.getState();

  if (/* button.isPressed() */ bValue == true) {
    // Serial.println("The button is pressed");
    myData.state_button = true;
  } else {
    myData.state_button = false;
  }

  if(xValue <= 100 && 1700 <= yValue <= 2300){
    myData.joystick_direction = 'l';

  } else if(1700 <= xValue <= 2300 && yValue <= 100){
    myData.joystick_direction = 'd';

  } else if(3000 <= xValue && 1700 <= yValue <= 2300){
    myData.joystick_direction = 'r';

  } else if(1700 <= xValue <= 2300 && 3000 <= yValue){
    myData.joystick_direction = 'u';

  } else if(1700 <= xValue <= 2300 && 1700 <= yValue <= 2300){
    myData.joystick_direction = 'n';
  }


  // read parameters of the image

  //myData.gesture = "hello";

  // Set values to send - set each variable in struct message
  
  
  // Send message via ESP-NOW
  
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(1000);


}