/*Program for receiving data from the sender node.
 * Count the elapsed time to receive
 * Data is 16 bit using the S0 variable of frame
 * starting date 1 August 2015, EBUS,SWIN.
 * mhasan@swin.edu.au
 * version v01
 */
#include "variant.h"
#include <due_can.h>

#define TEST1_CAN_TRANSFER_ID    0x1FFFFFFF //BIG ID 29 bits set to high
#define TEST2_CAN_TRANSFER_ID    0x10000001 //SMALL ID 29th bits and 1st bit set to high
#define MAX_CAN_FRAME_DATA_LEN  8
#define MAX_NUM_MSG 100


// CAN FRAME  as incoming frame
CAN_FRAME incomingframe1;
//CAN_FRAME incomingframe[100];

int msgNum=MAX_NUM_MSG; //Number of messages 
int msgData=0; // integer data in outgoingframe.data.s0 
uint16_t dataS0[MAX_NUM_MSG];
uint16_t previousS0=0;
uint16_t currentS0=0;

unsigned long StartTime1,StartTime2,StartTime3,StartTime4; 
unsigned long CurrentTime1,CurrentTime2,CurrentTime3,CurrentTime4; 
unsigned long ElapsedTime1,ElapsedTime2,ElapsedTime3,ElapsedTime4; 
unsigned long TotalTime;

void setup(){
  
 
  //setting up serial port with baud rate 115200
  Serial.begin(115200);
  // Initialize CAN0 and CAN1, baudrate is 250kb/s
   
  Can0.begin(CAN_BPS_250K);
  Can1.begin(CAN_BPS_250K);
  
  int filter;
  //extended
  for (filter = 0; filter < 3; filter++) {
  Can0.setRXFilter(filter, 0, 0, true);
  Can1.setRXFilter(filter, 0, 0, true);
  }  
   //standard
  for (int filter = 3; filter < 7; filter++) {
  Can0.setRXFilter(filter, 0, 0, false);
  Can1.setRXFilter(filter, 0, 0, false);
  }
 
 }
 
void printFrame(CAN_FRAME &frame) {
   Serial.print(" Data: ");
   Serial.print(frame.data.s0);
   //Serial.print("ID:");
 // Serial.print(frame.id);
   Serial.print("\n ID: 0x");
   Serial.print(frame.id, HEX);
   Serial.print(" Len: ");
   Serial.print(frame.length);
   Serial.print(" Data: ");
   Serial.print(frame.data.s0);
   Serial.print(" Data: 0x");
   Serial.print(frame.data.s0, HEX);
   Serial.print(" ");   
   Serial.print("\r\n");
}

void loop(){
  int filter;
  //extended
  for (filter = 0; filter < 3; filter++) {
  Can0.setRXFilter(filter, 0, 0, true);
  Can1.setRXFilter(filter, 0, 0, true);
  }  
   //standard
  for (int filter = 3; filter < 7; filter++) {
  Can0.setRXFilter(filter, 0, 0, false);
  Can1.setRXFilter(filter, 0, 0, false);
  }
  int cnt=0;
  TotalTime=0;
  Can0.watchFor(TEST1_CAN_TRANSFER_ID);
  while(Can0.rx_avail() == 0){}
  StartTime1 = micros();
  
  while(cnt < MAX_NUM_MSG){
    
     while(Can0.available() > 0) { // send when rx line is available
              Can0.read(incomingframe1);
              dataS0[cnt]=incomingframe1.data.s0; 
              cnt++;
     }
    
    
  }
  
  CurrentTime1 = micros();
  ElapsedTime1 = CurrentTime1 - StartTime1;
  TotalTime+=ElapsedTime1;
  
  Serial.print("\n");    
  Serial.print(TotalTime);
  Serial.print(" microseconds to receive ");
  Serial.print(cnt);
  Serial.print(" frames\r\n");
  
  Serial.print("stored DATA print starts ................. \n");

  for(cnt=0;cnt<MAX_NUM_MSG;cnt++){
    Serial.print(dataS0[cnt]);
    Serial.print("\n");
  }
  Serial.print("stored DATA printends................. \n");
 
}

