// Slave 2 Code

#include <SPI.h>
#include <mcp_can.h>

const int switchPin = 2; // Switch pin
const int ledPin = 13;   // LED pin

// CAN variables
const int SPI_CS_PIN = 10; // CS pin for MCP2515
MCP_CAN CAN(SPI_CS_PIN);

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  SPI.begin();
  
  if(CAN_OK != CAN.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ)) {
    Serial.println("Error initializing MCP2515");
    while(1); // Hang indefinitely
  }
  
  // Initialize filter to accept messages with ID 0x102
  if (CAN_OK != CAN.init_Mask(0, 0, 0x7FF)) {
    Serial.println("Error initializing mask");
    while(1); // Hang indefinitely
  }
  
  // Accept messages with ID 0x102
  if (CAN_OK != CAN.init_Filt(0, 0, 0x102)) {
    Serial.println("Error initializing filter");
    while(1); // Hang indefinitely
  }
}

void loop() {
  // Variables for storing received message
  unsigned long id;
  unsigned char len = 0;
  unsigned char buf[8];

  if (digitalRead(switchPin) == LOW) {
    byte data[] = {1};
    CAN.sendMsgBuf(0x103, 0, sizeof(data), data);
    delay(1000); // Add a small delay to prevent rapid toggling
  }
}
