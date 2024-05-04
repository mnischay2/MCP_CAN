// Master Module Code
//VCC -> 5V
//GND -> GND
//SCK -> SCK (Arduino)
//SO -> MISO (Arduino)
//SI -> MOSI (Arduino)
//CS -> Digital Pin (e.g., 10)
//INT -> Digital Pin (e.g., 2)

#include <SPI.h>
#include <mcp_can.h>

const int ledPin = 6; // LED pin

// CAN variables
const int SPI_CS_PIN = 10; // CS pin for MCP2515
MCP_CAN CAN(SPI_CS_PIN);

void setup() {
  pinMode(ledPin, OUTPUT);
  SPI.begin();
  CAN.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ);
}

void loop() {
  // Send command to turn on LED on Slave 1
  byte data[] = {1};
  CAN.sendMsgBuf(0x100, 0, sizeof(data), data);
  
  // Send command to turn on LED on Slave 4
  byte data2[] = {1};
  CAN.sendMsgBuf(0x101, 0, sizeof(data2), data2);
  
  delay(1000); // Send commands every second
}
