#include <SPI.h>          //Library for using SPI Communication 
#include <mcp2515.h>      //Library for using CAN Communication (https://github.com/autowp/arduino-mcp2515/)
 
struct can_frame canMsg1; //inbuilt struct datatype for storing data 
MCP2515 mcp2515(10); // CS pin at D10
int s1=4 ; //Switch pin at D4
 
void setup(){
  canMsg1.can_id  = 0x0F6;           //CAN id as 0x0F6
  canMsg1.can_dlc = 1;               //CAN data length as 8
  pinMode(s1,INPUT_PULLUP);          //internal pullup resistor to prevent any electric interference
  
  while (!Serial);                  //function in mcp2515 library to check whether can is working or not
  Serial.begin(115200);
 
  mcp2515.reset();                 //resets the CAN module 
  mcp2515.setBitrate(CAN_500KBPS); //Sets CAN at speed 500KBPS
  mcp2515.setNormalMode();
  Serial.println("Example: Write to CAN");

}
 
 
void loop(){
  int h=0; 
  int s=digitalRead(s1);
  if (s==1){// due to internal pullup logic is inverted. so when switch is open 's' will be 1 
    h=0;
   canMsg1.data[0] = 0x00;
  
  }
  else{ // due to internal pullup logic is inverted. so when switch is closed 's' will be 0 
  canMsg1.data[0] = 0x01;
  
  }
  Serial.println("switch state= ");
  Serial.println(h);
  mcp2515.sendMessage(&canMsg1);     //Sends the CAN message
  }
