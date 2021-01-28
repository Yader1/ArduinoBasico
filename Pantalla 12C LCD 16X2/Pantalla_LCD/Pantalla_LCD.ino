#include <LiquidCrystal_I2C.h> //Anadimos la libreria LiquidCrystal_I2C

LiquidCrystal_I2C lcd(0x27,16,2); // Primeramente escaniamos la direcion de la pantalla LCD. En mi caso es 0x27
                                  // Para saber cual es la dirrecion de la pantalla ejecute Scanner_12C.ino el cual se esncuentra en esta carpeta

void setup() {
  // put your setup code here, to run once:
    lcd.init(); //Inicialisamos el LCD
    lcd.backlight(); //Encendemos la reto iluminacion
    // lcd.clear(); Lo utilizamos para limpiar la pantalla
    lcd.setCursor(0,0); //Primero la columna y luego la fila
    lcd.print("Hola"); // Mensaje que se mostrara por el LCD
    lcd.setCursor(0,1);
    lcd.print("Mundo :]");

}

void loop() {
  // put your main code here, to run repeatedly:

}
