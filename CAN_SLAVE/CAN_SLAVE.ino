#include <SPI.h>              //Library for using SPI Communication 
#include <mcp2515.h>          //Library for using CAN Communication (https://github.com/autowp/arduino-mcp2515/)
 
struct can_frame canMsg;    //inbuilt struct datatype for storing data
MCP2515 mcp2515(10);                 // SPI CS Pin 10
 
 
void setup(){
  pinMode(6,1);           //LED pin
  Serial.begin(115200);                //Begins Serial Communication at 115200 baudrate
  SPI.begin();     
                    //Begins SPI communication
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();                  //Sets CAN at normal mode
  Serial.println("------- CAN Read ----------");

 }
 
 
void loop()
{
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK){//checks whether CAN module is able to read data or not
    if(canMsg.can_id==0x0F6){// verifies the id
      for (int i = 0; i<canMsg.can_dlc; i++)  {  // stores the data
        int x = canMsg.data[i];
        digitalWrite(6,x); //turns led on or off depending upon incoming data
        Serial.print(canMsg.data[i]);
        Serial.print(" ");
    
      }
    Serial.println();     }
}}
