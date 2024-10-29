int sensors[8] = {A7, A6, A5, A4, A3, A2, A1, A0};

int values[8];
bool sensorStates[8];
int contInter=0;
int Umbral = 750;
unsigned long previousMillis = 0;  // Almacena el último tiempo en que se actualizó contInter
const unsigned long interval = 2000;  // Intervalo de 2 segundos en milisegundos
// Variable microsuiche
//variable suiche


int ain1 = 7;
int ain2 = 6;
int ena = 8;
int bin1 = 0;
int bin2 = 0;
int enb = 0;

int P = 0;

void setup() {
  Serial.begin(9600);
}

void loop(){
  readsensors();
  calP();
}

void readsensors() {
  bool allBlack = true;
  
  for (int i = 0; i < 8; i++) {
    values[i] = analogRead(sensors[i]);
    sensorStates[i] = (values[i] > Umbral);

   
    //Serial.print(sensorStates[i] ? 1 : 0);
    //Serial.print(" ");  
    if (!sensorStates[i]) {
      allBlack = false;
    }
  }
  Serial.println();
  if (allBlack) {
    unsigned long currentMillis = millis();  // Obtiene el tiempo actual en milisegundos

    // Si han pasado al menos 2 segundos desde la última vez que se incrementó contInter
    if (currentMillis - previousMillis >= interval) {
      contInter++;
      previousMillis = currentMillis;  // Actualiza el tiempo del último incremento

    }
  }
}

void move(int motor, int speed, int direction){

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }


  if(motor == 1){
    digitalWrite(ain1, inPin1);
    digitalWrite(ain2, inPin2);
    analogWrite(ena, speed);
  }
  else{
    digitalWrite(bin1, inPin1);
    digitalWrite(bin2, inPin2);
    analogWrite(enb, speed);
  }

}

void conditions(){
  if(!sensorStates[0]&&!sensorStates[1]&&!sensorStates[2]&&sensorStates[3]&&sensorStates[4]&&!sensorStates[5]&&!sensorStates[6]&&!sensorStates[7]){
      Serial.println("Adelante");
  } 
  else if(sensorStates[1] || sensorStates[2]){
      Serial.println("Giro Izquierda");
  }
  else if(sensorStates[5] || sensorStates[6]){
      Serial.println("Giro Derecha");
  }
  else if(sensorStates[0]){
      Serial.println("Giro Izquierda Brusco");
  }
  else if(sensorStates[7]){
      Serial.println("Giro Derecha Brusco");
  }
  delay(500);
}

void calP() {
  
  int positions[8] = {-3500, -2500, -1500, -500, 500, 1500, 2500, 3500};

  int sum = 0; 
  int count = 0;  

  for (int i = 0; i < 8; i++) {
    if (sensorStates[i]) {  
      sum += positions[i];
      count++;
    }
  }

  
  if (count > 0) {
    P = sum / count;
  } else {
    P = 0; 
  }

  // Mostrar el valor de P para verificación
  Serial.print("Posición P: ");
  Serial.println(P);
}
