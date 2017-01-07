/*
 * By Trinit@ 
 * Janvier 2017
 * 
 *  Test d'un module HC-06 pour la réception de commande extérieur !
 * 
 */

#include <SoftwareSerial.h>  //Software Serial Port 

// Attention Rx et Tx sur la carte ne permettent pas le téléversement !
#define RxD 5
#define TxD 6

SoftwareSerial btModule(RxD,TxD); 

void setup() {

  Serial.begin( 115200 ); 
  while(!Serial);
  Serial.println("Wait for command !"); 
  
  // Configuration du bluetooth 
  btModule.begin( 57600 ); //Module bluetooth par défaut 9600, N, 8, 1

  //***** For configure
  //btModule.print("AT");  //test 1
  //btModule.print("AT+VERSION");  //Demande le N° de version
  //btModule.print("AT+BAUD7");  //change speed -> 5700
  
  //Serial.print( "\n" );
  //delay(1000);
  //***** For configure
}

void loop() {
  //digitalWrite(13, HIGH);   // LED 13 ON
  //delay(100);             
  //digitalWrite(13, LOW);    // Off
  
  char recvChar; 
  if (btModule.available()) { 

    Serial.print( "--->>>>>> Command receipt : " );
    
    String commande = btModule.readStringUntil( "\r\n" ); 

    if( commande.length() > 0 ){
      Serial.println( commande );
      btModule.println( "Receipt ok" );
      if( commande == "666" ){
        Serial.println( "get commande 666 OK");
      }

    } else {
      Serial.print( "Ko\n" );
    }

  } 

  // --- sendTxtToBT_forTest();
}


//
// Just testing send Text by Bluetooth
// Use to valid speed and connecting
// 
void sendTxtToBT_forTest(){
  int counter = 0;
  unsigned long time;

  
  Serial.print("Test module HC-06 bluetooth ");
  Serial.print(++counter);
  Serial.print(" " );
  time = millis();
  
  Serial.println(time);
  btModule.println(time);
  
  delay(1000);  //Un envoi de données par seconde
}

 
