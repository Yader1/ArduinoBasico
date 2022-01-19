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
SoftwareSerial BT(2,3); // 2 RX, 3 TX
SoftwareSerial DFPlayerSerial(10,11); //10 RX, 11 TX

DFRobotDFPlayerMini myDFPlayer;                               

//Variables
byte LedE = 4;
char DataBluetooth;

void setup() {
  //Pines de salida
  pinMode(LedE, OUTPUT);
  digitalWrite(LedE, LOW);
  
  Serial.begin(115200);
  DFPlayerSerial.begin(9600);
  
   if (!myDFPlayer.begin(DFPlayerSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Error inicializando modulo mp3"));
    Serial.println(F("1.Porfavor revisa las conexiones!"));
    Serial.println(F("2.Porfavor inserta memoria microSD!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }else{
    Serial.println(F("Inicialización correcta DFPlayer."));
    BT.begin(9600);
    Serial.println("Inicialización correcta Bluetooth");
    delay(1000);
    digitalWrite(LedE, HIGH);
  }
}

void loop() {
  //Si hay datos disponibles en el modulo bluetooth HC-05
  if (BT.available()){
    DataBluetooth = BT.read();
    Serial.print(DataBluetooth);
    
    if(DataBluetooth == 'A'){
      reproducir(1);
      Serial.println("Fin de la ejecucion");
    }
    if(DataBluetooth == 'B'){
      reproducir(2); 
      Serial.println("Fin de la ejecucion");
    }
   }
}
void reproducir(int r){
  myDFPlayer.volume(30);   //De 0 a 30
  myDFPlayer.play(r);
  delay(10);
  Serial.println("\nReproduciendo");
}
