int sensors[8] = {A0, A1, A2, A3, A4, A5, A6, A7};
int values[8];
bool sensorStates[8];
int contInter=0;
int Umbral = 750;
unsigned long previousMillis = 0;  // Almacena el último tiempo en que se actualizó contInter
const unsigned long interval = 2000;  // Intervalo de 2 segundos en milisegundos
// Variable microsuiche
//variable suiche


void setup() {
  Serial.begin(9600);
}

void loop() {
  readsensors();
  
}

void readsensors() {
  bool allBlack = true;
  for (int i = 0; i < 8; i++) {
    values[i] = analogRead(sensors[i]);
    sensorStates[i] = (values[i] > Umbral);

   
    Serial.print(sensorStates[i] ? 1 : 0);
    Serial.print(" ");  
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

      Serial.print("Interseccion: ");
      Serial.println(contInter);
    }
  }
}
