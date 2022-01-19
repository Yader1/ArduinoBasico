/*------------------------------------------------
 * myDFPlayer.begin(DFPlayerSerial)
 * myDFPlayer.volume(volume); 0-30
 * myDFPlayer.play(); 
 * myDFPlayer.play(5);  Reproduce el archivo 0005
 * myDFPlayer.next();
 * myDFPlayer.previous();
 * myDFPlayer.pause();
 * myDFPlayer.start();
 * myDFPlayer.randomAll();
 * myDFPlayer.enableLoop();
 * myDFPlayer.disableLoop();
 ----------------------------------------------------*/
#include <SoftwareSerial.h>
#include "Arduino.h" 
#include "DFRobotDFPlayerMini.h"
SoftwareSerial BT(2,3); // 10 RX, 11 TX
SoftwareSerial DFPlayerSerial(10,11); //8 RX, 9 TX

DFRobotDFPlayerMini myDFPlayer;                               

//Variables
byte LedE = 3;
char DataBluetooth;

void setup() {
  Serial.begin(115200);
  BT.begin(9600);
  Serial.println("");
  Serial.println("Iniciando Control Bluetooth");
  
  //Pines de salida
  pinMode(LedE, OUTPUT);
  digitalWrite(LedE, LOW);
}

void loop() {
  //Si hay datos disponibles en el modulo bluetooth HC-05
  if (BT.available()){
    DataBluetooth = BT.read();
    Serial.print(DataBluetooth);
    
    if(DataBluetooth == 'A'){
      reproducir(1);
      digitalWrite(LedE, HIGH);
      Serial.println("\nFin de la ejecucion");
    }
    if(DataBluetooth == 'B'){
      reproducir(2);
      digitalWrite(LedE, HIGH);
      Serial.println("\nEnd IF");
    }
   }
}

void validarCard(){
   DFPlayerSerial.begin(9600);
   if (!myDFPlayer.begin(DFPlayerSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }else{
    Serial.println(F("\nDFPlayer Mini Conectado.\n"));
  }
}

void reproducir(int r){
  validarCard();
  myDFPlayer.volume(30);   //De 0 a 30
  myDFPlayer.play(r);
  delay(10);
  Serial.println("Reproduciendo");
}
