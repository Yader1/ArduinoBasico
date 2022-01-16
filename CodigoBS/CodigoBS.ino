#include <SoftwareSerial.h>
SoftwareSerial BT(10,11); // 10 RX, 11 TX

//Variables
byte LedE = 3;

char DataBluetooth = ' ';

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  Serial.println("");
  Serial.println("Iniciando Control...");

  //
  pinMode(LedE, OUTPUT);

  //
  digitalWrite(LedE, LOW);
}

void loop() {
  // Si hay datos disponibles en el modulo bluetooth HC-05
  if (BT.available()){
    DataBluetooth = BT.read();
    Serial.print(DataBluetooth);

    if(DataBluetooth == 'A'){
      digitalWrite(LedE, HIGH);
    }
   }
      
}
