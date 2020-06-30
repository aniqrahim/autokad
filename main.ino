#define SS_PIN 4  //D2
#define RST_PIN 5 //D1

#include <SPI.h>
#include <MFRC522.h>

MFRC522 mfrc522(SS_PIN, RST_PIN);   // create MFRC522 instance.
int statuss = 0;
int out = 0;
void setup() 
{
  Serial.begin(9600);   // initiate a serial communication
  SPI.begin();      // initiate  SPI bus
  mfrc522.PCD_Init();   // initiate MFRC522
}
void loop() 
{
  // look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  // show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  
  if (content.substring(1) == "7D C5 C3 DB") // card #1 uid
  {
    Serial.println(" [ACCESS GRANTED] ");
    delay(1000);
    Serial.println(" welcome olio. ");
    delay(1000);
    Serial.println(" have a good day! ");
    Serial.println();
    statuss = 1;
  }

  else if (content.substring(1) == "42 10 DB 0D") // card #2 uid
  {
    Serial.println(" [ACCESS GRANTED] ");
    delay(1000);
    Serial.println(" welcome sam. ");
    delay(1000);
    Serial.println(" have a good day! ");
    Serial.println();
    statuss = 1;
  }
  
  else   {
    Serial.println(" [ACCESS DENIED] ");
    delay(1000);
    Serial.println(" your card doesn't have permission. ");
    delay(1000);
    Serial.println(" if you believe this is an error, contact admin. ");
    Serial.println();
  }
} 
