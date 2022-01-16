#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8); // 10 y 11 para el Arduino Mega. Configura el puerto   serie para el SIM900. TX RX

//Pantalla LCD
LiquidCrystal_I2C lcd(0x27,16,2); // Primeramente escaniamos la direcion de la pantalla LCD. En mi caso es 0x27
                                  // Para saber cual es la dirrecion de la pantalla ejecute Scanner_12C.ino el cual se esncuentra en esta carpeta

//IOT-GA6-B
  char phone_no[]="50584138210"; 

//HC-SR04
  int Trig = 12;
  int Echo = 13;

//TONE
    #define  c3    7634
    #define  d3    6803
    #define  e3    6061
    #define  f3    5714
    #define  g3    5102
    #define  a3    4545
    #define  b3    4049
    #define  c4    3816    // 261 Hz
    #define  d4    3401    // 294 Hz
    #define  e4    3030    // 329 Hz
    #define  f4    2865    // 349 Hz
    #define  g4    2551    // 392 Hz
    #define  a4    2272    // 440 Hz
    #define  a4s   2146
    #define  b4    2028    // 493 Hz
    #define  c5    1912    // 523 Hz
    #define  d5    1706
    #define  d5s   1608
    #define  e5    1517    // 659 Hz
    #define  f5    1433    // 698 Hz
    #define  g5    1276
    #define  a5    1136
    #define  a5s   1073
    #define  b5    1012
    #define  c6    955
    
    #define  R     0      // Define a special note, ‘R’, to represent a rest
    
    // Melody 1: Star Wars Imperial March
    
    int melody1[] = {  a4, R,  a4, R,  a4, R,  f4, R, c5, R,  a4, R,  f4, R, c5, R, a4, R,  e5, R,  e5, R,  e5, R,  f5, R, c5, R,  g5, R,  f5, R,  c5, R, a4, R};
    int beats1[]  = {  50, 20, 50, 20, 50, 20, 40, 5, 20, 5,  60, 10, 40, 5, 20, 5, 60, 80, 50, 20, 50, 20, 50, 20, 40, 5, 20, 5,  60, 10, 40, 5,  20, 5, 60, 40};
    
    // Melody 2: Star Wars Theme
    int melody2[] = {  f4,  f4, f4,  a4s,   f5,  d5s,  d5,  c5, a5s, f5, d5s,  d5,  c5, a5s, f5, d5s, d5, d5s,   c5};
    int beats2[]  = {  21,  21, 21,  128,  128,   21,  21,  21, 128, 64,  21,  21,  21, 128, 64,  21, 21,  21, 128 };
    
    int MAX_COUNT = sizeof(melody1) / 2;
    long tempo = 10000;
    int pause = 1000;
    int rest_count = 50;
    int toneM = 0;
    int beat = 0;
    long duration  = 0;
    int potVal = 0;
    int speakerOut = 6;

  void setup()
   {
      //LCD
      lcd.init(); //Inicialisamos el LCD
      lcd.backlight(); //Encendemos la reto iluminacion
      
      //IOT-GA6-B
      delay (5000);  //Nos damos un tiempo para encender el GPRS y la alimentación de la tarjeta
      SIM900.begin(115200);  //Configura velocidad del puerto serie para el SIM900
      Serial.begin(115200);  //Configura velocidad del puerto serie del Arduino
      Serial.println("Encendido");
      lcd.setCursor(0,0); //Primero la columna y luego la fila
      lcd.print("Encendido"); // Mensaje que se mostrara por el LCD
      delay (1000);
      delay(5000);  //Tiempo para que encuentre una RED

      //HC-SR04
      pinMode(Trig, OUTPUT);
      pinMode(Echo, INPUT);

      //TONE
      pinMode(speakerOut, OUTPUT);
   }

   void llamar()
   {
      Serial.println("Realizando llamada...");
      SIM900.println("AT");
      SIM900.print("ATD+"); //Dial the phone number using ATD command
      SIM900.print(phone_no);
      SIM900.println(";"); // Semicolon is a must at the end
      delay(25000);
      SIM900.println("ATH"); // After a delay of 5 secs Hang the call
      Serial.println("Llamada finalizada");     
   }

   void mensaje_sms()
   {
      Serial.println("Enviando SMS...");
      lcd.setCursor(0,1); //Primero la columna y luego la fila
      lcd.print("Enviando SMS..."); // Mensaje que se mostrara por el LCD
      
      SIM900.println("AT+CMGF=1\r\n");
      delay(1000);
      SIM900.write("AT+CMGS=\"+50584138210\"\r\n");
      SIM900.write("Wey, Se llevan tu tanque de gas xD");
      delay(1000);

      SIM900.write((char)26);
      delay(5000);
      lcd.clear(); //Lo utilizamos para limpiar la pantalla
      delay(2000);
      lcd.setCursor(0,1); //Primero la columna y luego la fila
      lcd.print("SMS enviado"); // Mensaje que se mostrara por el LCD
      Serial.println("SMS enviado");
   }

   void hc(){
      long duracion;
      long distancia;
    
      digitalWrite(Trig, LOW);
      delayMicroseconds(4);
      digitalWrite(Trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(Trig,LOW);
    
      duracion = pulseIn(Echo, HIGH);
      duracion = duracion/2;
    
      distancia = duracion/29;
    
      Serial.println(distancia);
      delay(50);

      if(distancia <= 20){
        mensaje_sms();
        llamar();  //Realiza la llamada

        //TONE
        // Melody1
        for (int i=0; i<MAX_COUNT; i++) {
          toneM = melody1[i];
          beat = beats1[i];
          duration = beat * tempo;
          playTone();
          delayMicroseconds(pause);
        }
        // Melody2
        MAX_COUNT = sizeof(melody2) / 2;
        for (int i = 0; i < MAX_COUNT; i++) {
          toneM = melody2[i];
          beat = beats2[i];
          duration = beat * tempo;
          playTone();
          delayMicroseconds(pause);
        }
      }
    }

    //TONE
    void playTone() {
      long elapsed_time = 0;
      
      if (toneM > 0) {
        while (elapsed_time < duration) {
          digitalWrite(speakerOut,HIGH);
          delayMicroseconds(toneM / 2);
          digitalWrite(speakerOut, LOW);
          delayMicroseconds(toneM / 2);
          elapsed_time += (toneM);
        }
      }else {
        for (int j = 0; j < rest_count; j++) {
          delayMicroseconds(duration);
        }
      } 
    }

   void loop()
   {
      hc();
      //mensaje_sms();
      //llamar();  //Realiza la llamada
   }
