/*Program for sending data to the receiver node.
 * Count the elapsed time to send
 * Data is 16 bit using the S0 variable of frame
 * starting date 1 August 2015, EBUS,SWIN.
 * mhasan
 * version v01
 */
#include "variant.h"
#include <due_can.h>

#define TEST1_CAN_TRANSFER_ID    0x1FFFFFFF //BIG ID 29 bits set to high
#define TEST2_CAN_TRANSFER_ID    0x10000001 //SMALL ID 29th bits and 1st bit set to high
#define MAX_CAN_FRAME_DATA_LEN  8
#define MAX_NUM_MSG 100
#define COUNT_STARTS 0

CAN_FRAME outgoingframe;

uint16_t datas0;

unsigned long StartTime; 
unsigned long CurrentTime; 
unsigned long ElapsedTime; 

void setup(){
  
  Serial.begin(115200);
  
   // Initialize CAN0 and CAN1, baudrate is 250kb/s
   
  Can0.begin(CAN_BPS_250K);
  Can1.begin(CAN_BPS_250K);

  outgoingframe.id = TEST1_CAN_TRANSFER_ID;
  outgoingframe.length = MAX_CAN_FRAME_DATA_LEN;
  outgoingframe.extended = 1;
}

void loop(){

  int count=COUNT_STARTS;
  
  StartTime = micros();
  do{      
    outgoingframe.data.s0 = count;
    while(!CAN.sendFrame(outgoingframe)){}
    count++;
  }while(count<MAX_NUM_MSG);
  
  CurrentTime = micros();
  ElapsedTime = CurrentTime - StartTime;
  Serial.print("\nTransfer Time (in microsecond): ");
  Serial.print(ElapsedTime);
  Serial.print("\n");
  delay(1000);
  
}

