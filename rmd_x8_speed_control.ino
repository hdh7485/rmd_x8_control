// CAN Send Example
//

#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];                        // Array to store serial string
#define CAN0_INT 2                              // Set INT to pin 2

MCP_CAN CAN0(10);     // Set CS to pin 10

void setup()
{
  Serial.begin(115200);

  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if (CAN0.begin(MCP_ANY, CAN_1000KBPS, MCP_16MHZ) == CAN_OK) Serial.println("MCP2515 Initialized Successfully!");
  else Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted
}

void loop()
{
  byte data[8] = {0xA2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  for (long speed = 0; speed < 100000; speed += 100) {
    data[4] = speed & 0xFF;
    data[5] = (speed >> 8) & 0xFF;
    data[6] = (speed >> 16) & 0xFF;
    data[7] = (speed >> 24) & 0xFF;

    // send data:  ID = 0x100, Standard CAN Frame, Data length = 8 bytes, 'data' = array of data bytes to send
    byte sndStat = CAN0.sendMsgBuf(0x141, 0, 8, data);
    if (sndStat == CAN_OK) {
      Serial.println("Message Sent Successfully!");
    } else {
      Serial.println("Error Sending Message...");
      Serial.println(sndStat);
    }
    Serial.println(speed);
    Serial.println(data[4]);
    Serial.println(data[5]);
    Serial.println(data[6]);
    Serial.println(data[7]);
    //    if (!digitalRead(CAN0_INT))                        // If CAN0_INT pin is low, read receive buffer
    //    {
    //      CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
    //
    //      if ((rxId & 0x80000000) == 0x80000000)    // Determine if ID is standard (11 bits) or extended (29 bits)
    //        sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    //      else
    //        sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);
    //
    //      Serial.print(msgString);
    //
    //      if ((rxId & 0x40000000) == 0x40000000) {  // Determine if message is a remote request frame.
    //        sprintf(msgString, " REMOTE REQUEST FRAME");
    //        Serial.print(msgString);
    //      } else {
    //        for (byte i = 0; i < len; i++) {
    //          sprintf(msgString, " 0x%.2X", rxBuf[i]);
    //          Serial.print(msgString);
    //        }
    //      }
    //
    //      Serial.println();
    //    }
    delay(1);   // send data per 100ms
  }
  for (long speed = 100000; speed >= 0; speed -= 100) {
    data[4] = speed & 0xFF;
    data[5] = (speed >> 8) & 0xFF;
    data[6] = (speed >> 16) & 0xFF;
    data[7] = (speed >> 24) & 0xFF;
    // send data:  ID = 0x100, Standard CAN Frame, Data length = 8 bytes, 'data' = array of data bytes to send
    byte sndStat = CAN0.sendMsgBuf(0x141, 0, 8, data);
    if (sndStat == CAN_OK) {
      Serial.println("Message Sent Successfully!");
    } else {
      Serial.println("Error Sending Message...");
      Serial.println(sndStat);
    }
    Serial.println(speed);
    Serial.println(data[4]);
    Serial.println(data[5]);
    Serial.println(data[6]);
    Serial.println(data[7]);
    //    if (!digitalRead(CAN0_INT))                        // If CAN0_INT pin is low, read receive buffer
    //    {
    //      CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
    //
    //      if ((rxId & 0x80000000) == 0x80000000)    // Determine if ID is standard (11 bits) or extended (29 bits)
    //        sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
    //      else
    //        sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);
    //
    //      Serial.print(msgString);
    //
    //      if ((rxId & 0x40000000) == 0x40000000) {  // Determine if message is a remote request frame.
    //        sprintf(msgString, " REMOTE REQUEST FRAME");
    //        Serial.print(msgString);
    //      } else {
    //        for (byte i = 0; i < len; i++) {
    //          sprintf(msgString, " 0x%.2X", rxBuf[i]);
    //          Serial.print(msgString);
    //        }
    //      }
    //
    //      Serial.println();
    //    }
    delay(1);   // send data per 100ms
  }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
