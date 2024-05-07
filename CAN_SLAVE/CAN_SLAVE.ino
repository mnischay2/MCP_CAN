#include <SPI.h>              //Library for using SPI Communication 
#include <mcp2515.h>          //Library for using CAN Communication (https://github.com/autowp/arduino-mcp2515/)
 
struct can_frame canMsg; 
MCP2515 mcp2515(10);                 // SPI CS Pin 10
 
 
void setup(){
  pinMode(6,1);
  Serial.begin(115200);                //Begins Serial Communication at 9600 baudrate
  SPI.begin();     
                    //Begins SPI communication

  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();                  //Sets CAN at normal mode
  Serial.println("------- CAN Read ----------");
  Serial.println("ID = 036  DLC   DATA");

 }
 
 
void loop()
{
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK){
    if(canMsg.can_id==0x0F6){
      for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
        int x = canMsg.data[i];
        digitalWrite(6,x);
        Serial.print(canMsg.data[i],HEX);
        Serial.print(" ");
    
      }
    Serial.println();     }
}}