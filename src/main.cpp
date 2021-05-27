#include <Arduino.h>

const int pinVBAT = A0; // Pin entrada Voltaje Bateria
const int pinDL1 =  4;// Pin salida led Este pin no es PWM
const int pinDL2 =  5;// Pin salida led
const int pinSensor = 3;//Pin salida sensor
const int pinDS1 = 6;//Pin pulsador 1
const int pinDS2 = 7;//Pin pulsador 2

unsigned long previousMillis = 0;        // Auxiliar para calculo de tiempo

// constants won't change:
const long interval = 3000;           // Intervalo de tiempo de ejecucion (milliseconds) (3s requerimiento)
void batteryStatus(){
    int value;
    float volt;

    value = analogRead(pinVBAT);
    volt = value * 5.0 / 1023.0;
    Serial.print("Voltaje batería: ");
    Serial.println(volt);
}

void ledIlumination(){
    String ledStatus = "";
    String led = "";
    int ciclo = 0;

    if (Serial.available() >= 1){
    ledStatus= Serial.readString();
    Serial.println("Obtenido: " + ledStatus);
    led = ledStatus.substring(0,ledStatus.indexOf(","));
    Serial.println("LED: " + led);
    ciclo = (int)ledStatus.substring(ledStatus.indexOf(",")+1,ledStatus.length()).toInt();
    Serial.print("Ciclo: ");Serial.println(ciclo);
    if(led == "l1"){
      Serial.println("Es igual a l1");
      analogWrite(pinDL1, ciclo * 255 /100);
      }
    else if(led == "l2"){
      Serial.println("Es igual a l2");
      analogWrite(pinDL2, ciclo * 255 /100);
    }
    else{  
      Serial.println("No se ingreso una opcion de led correcta");
    }
    
    }
}

void sensorBtn(){
  if (digitalRead(pinDS1) == LOW && digitalRead(pinDS2) == LOW) {
    digitalWrite(pinSensor, HIGH);  
  } 
  else{
    digitalWrite(pinSensor, LOW); 
  }
}

void setup() {
  TCCR2B = TCCR2B & B11111000 | B00000010;    // TIM2 (Pin3 & Pin11) divisor = 8  PWM frecuencia = 3921.16 Hz

  pinMode(pinDL1, OUTPUT);
  pinMode(pinDL2, OUTPUT);
  pinMode(pinSensor, OUTPUT);

  pinMode(pinDS1, INPUT);
  pinMode(pinDS2, INPUT);
  pinMode(pinSensor, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    /*
    condición para actualizar despues de cierto intervalo de tiempo
    */
    batteryStatus();
  }
  ledIlumination();
  sensorBtn();
  delay(500); //
}