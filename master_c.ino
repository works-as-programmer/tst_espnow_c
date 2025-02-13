#include <WiFi.h>
#include <esp_now.h>

// Left & Right Slaves MAC Addresses
uint8_t leftSlave[] = {0xD8, 0x3B, 0xDA, 0xA3, 0xE5, 0x70};  
uint8_t rightSlave[] = {0x98, 0x3D, 0xAE, 0xEE, 0x98, 0x50};

void setup() {
    Serial.begin(115200);
    
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW Init Failed");
        return;
    }

    esp_now_peer_info_t peerInfo;
    memset(&peerInfo, 0, sizeof(peerInfo));

    memcpy(peerInfo.peer_addr, leftSlave, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    esp_now_add_peer(&peerInfo);

    memcpy(peerInfo.peer_addr, rightSlave, 6);
    esp_now_add_peer(&peerInfo);
}

void loop() {
    const char *message = "Vibrate!";
    
    esp_err_t result = esp_now_send(leftSlave, (uint8_t *)message, strlen(message));
    Serial.println(result == ESP_OK ? "Sent to Left" : "Failed to send Left");

    result = esp_now_send(rightSlave, (uint8_t *)message, strlen(message));
    Serial.println(result == ESP_OK ? "Sent to Right" : "Failed to send Right");

    delay(100);  // Faster transmission
}