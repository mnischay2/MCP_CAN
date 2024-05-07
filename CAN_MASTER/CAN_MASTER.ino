#include <SPI.h>          //Library for using SPI Communication 
#include <mcp2515.h>      //Library for using CAN Communication (https://github.com/autowp/arduino-mcp2515/)
 
struct can_frame canMsg1;
MCP2515 mcp2515(10);
int s1=4 ;
 
void setup(){
  canMsg1.can_id  = 0x0F6;           //CAN id as 0x036
  canMsg1.can_dlc = 1;               //CAN data length as 8
  pinMode(s1,INPUT_PULLUP);
  
  while (!Serial);
  Serial.begin(115200);
 
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();
  Serial.println("Example: Write to CAN");

}
 
 
void loop(){
  int h=0; 
  int s=digitalRead(s1);
  if (s==1){
    h=0;
   canMsg1.data[0] = 0x00;
  
  }
  else{
  canMsg1.data[0] = 0x01;
  
  }
  Serial.println("switch state= ");
  Serial.println(h);
  mcp2515.sendMessage(&canMsg1);     //Sends the CAN message
  }