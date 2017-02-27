/*
 * By Trinit@ 
 * Févier 2017
 * 
 *  BlueCar -> Pilotage voiture télécommandée via bluetooth
 * 
 */

#include <SoftwareSerial.h>  //Software Serial Port 

// Attention Rx et Tx sur la carte ne permettent pas le téléversement !
#define RxD 5
#define TxD 6

//moteur 1
#define Pin1Moteur1 13  // pin de commande moteur 1
#define Pin2Moteur1 12   // pin de commande moteur 1
#define PinPMoteur1 11  // pin PWM moteur 1
//moteur 2
#define Pin1Moteur2 8   // pin de commande moteur 2
#define Pin2Moteur2 7   // pin de commande moteur 2
#define PinPMoteur2 10  // pin PWM moteur 2


SoftwareSerial btModule( RxD,TxD ); 

void setup() {

  Serial.begin( 115200 ); 
  while(!Serial);
  Serial.println("Wait for command !"); 
  
  // Configuration du bluetooth 
  btModule.begin( 57600 ); //Module bluetooth par défaut 9600, N, 8, 1

  pinMode( Pin1Moteur1, OUTPUT);
  pinMode( Pin2Moteur1, OUTPUT);
  pinMode( PinPMoteur1, OUTPUT);
  pinMode( Pin1Moteur2, OUTPUT);
  pinMode( Pin2Moteur2, OUTPUT);
  pinMode( PinPMoteur2, OUTPUT);
  
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
      } else if( commande == "0x01" ){
        Serial.println("Go Go !");
        
        actionMoteur(1,1,100); 
        //delay(2000); 
        
      } else if( commande == "0x11" ){  // Stop
        
        Serial.println("Stop Now !");
        actionMoteur( 1, 0, 0 ); //arrêt moteur 1
        actionMoteur( 2, 0, 0 ); //arrêt moteur 2
  
      } else if( commande == "0x10" ){  // Stop
        
        Serial.println("Go back !");

        actionMoteur( 1, -1, 100 ); 
  
      } else if( commande == "0x1000" ){  // gauche
        
        Serial.println("Gauche !");

        actionMoteur( 2, -1, 100 ); 
        
  
      } else if( commande == "0x1001" ){  // droite
        
        Serial.println("Droite !");

        actionMoteur( 2, 1, 100 ); 
        
      }

    } else {
      Serial.print( "Ko\n" );
    }

  } 

  
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

void actionMoteur(int moteur,int sens,int pourcentage){
  int pin1,etat1,pin2,etat2,pinP,puissance; //variable de la fonction
  //test numéro du moteur
  if ( moteur == 1){
    pin1 = Pin1Moteur1;
    pin2 = Pin2Moteur1;
    pinP = PinPMoteur1;
  } else {
    pin1 = Pin1Moteur2;
    pin2 = Pin2Moteur2;
    pinP = PinPMoteur2;
  }
  //test sens du moteur 1,-1 (sens contrainre) ou tout autre valeur (stoppe le moteur)
  if (sens==1){
    etat1=1;
    etat2=0;
  }
  else if (sens==-1){
    etat1=0;
    etat2=1;
  } else {
    etat1=0;
    etat2=0;
  }
  
  puissance = map( pourcentage, 0, 100, 0, 255 );
  analogWrite( pinP, puissance );
  digitalWrite( pin1, etat1 );
  digitalWrite( pin2, etat2 );
  //affichage sur le moniteur série (facultatif)
  Serial.print("Moteur : " );
  Serial.print( moteur );
  if (sens==-1 || sens==1){
    Serial.print(" sens : ");
    Serial.print(sens);
  } else {
    Serial.print(" ! stop ! ");
  }
  Serial.print(" puissance : ");
  Serial.println(pourcentage);
}
 
