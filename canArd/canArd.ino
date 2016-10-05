// demo: CAN-BUS Shield, receive data with check mode
// send data coming to fast, such as less than 10ms, you can use this way
// loovee, 2014-6-13


#include <SPI.h>
#include "mcp_can.h"


// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;
const int LED=8;
boolean ledON=1;
unsigned long time;
MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin
int cnt = 0;

void setup()
{
  
    Serial.begin(9600);
    pinMode(LED,OUTPUT);
    Serial.print("Hello");
    while (CAN_OK != CAN.begin(CAN_500KBPS))              // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(100);
    }
    Serial.println("CAN BUS Shield init ok!");
}


void loop()
{
    unsigned char len = 0;
    unsigned char buf[8];

    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        unsigned char canId = CAN.getCanId();
        if(canId == 2 * 16 + 5)
        {
            if(cnt == 10) {
              time = millis();
            Serial.println("-----------------------------");
            Serial.print("get data from ID: ");
            Serial.print(canId, HEX);
            Serial.print("   Time: ");
            Serial.println(time);
            for(int i = 0; i<len; i++)    // print the data
            {
                Serial.print(buf[i], HEX);
                Serial.print("\t");
            }
            Serial.println();
            cnt = 0;
            }
            cnt ++;
        }
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
