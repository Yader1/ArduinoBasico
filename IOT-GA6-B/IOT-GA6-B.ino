#include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8); // 10 y 11 para el Arduino Mega. Configura el puerto   serie para el SIM900. TX RX

char phone_no[]="50586377856"; 

void setup()
   {
      delay (5000);  //Nos damos un tiempo para encender el GPRS y la alimentación de la tarjeta
      SIM900.begin(115200);  //Configura velocidad del puerto serie para el SIM900
      Serial.begin(115200);  //Configura velocidad del puerto serie del Arduino
      Serial.println("OK");
      delay (1000);
      delay(5000);  //Tiempo para que encuentre una RED
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
      SIM900.println("AT+CMGF=1\r\n");
      delay(1000);
      SIM900.write("AT+CMGS=\"+50586377856\"\r\n");
      SIM900.write("...");
      delay(1000);

      SIM900.write((char)26);
      delay(5000);

      Serial.println("SMS enviado");
   }

   void loop()
   {
      mensaje_sms();
      llamar();  //Realiza la llamada
      while (1);
   }
