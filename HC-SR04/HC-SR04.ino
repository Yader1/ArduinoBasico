int Trig = 12;
int Echo = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  hc();
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
}
