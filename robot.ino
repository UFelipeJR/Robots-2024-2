int sensor0 = A0;
int sensor1 = A1;
int sensor2 = A2;
int sensor3 = A3;
int sensor4 = A4;
int sensor5 = A5;
int sensor6 = A6;
int sensor7 = A7;

int values[8];
int SensorCount = 8;
int minL = 750;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensor0,INPUT);
  pinMode(sensor1,INPUT);
  pinMode(sensor2,INPUT);
  pinMode(sensor3,INPUT);
  pinMode(sensor4,INPUT);
  pinMode(sensor5,INPUT);
  pinMode(sensor6,INPUT);
  pinMode(sensor7,INPUT);
  Serial.begin(9600);

}

void loop() {
  readsensors();
  printValues();
}

void printValues()
{

  for (int i = 0; i < SensorCount; i++) {
    Serial.print(values[i]);
    Serial.print("   \t");
  }
  Serial.println();

  delay(500);

}

void readsensors(){
  
  values[0] = analogRead(sensor0);
  values[1] = analogRead(sensor1);
  values[2] = analogRead(sensor2);
  values[3] = analogRead(sensor3);
  values[4] = analogRead(sensor4);
  values[5] = analogRead(sensor5);
  values[6] = analogRead(sensor6);
  values[7] = analogRead(sensor7);
  
  
}

void detectLine(){
  for (int i = 0; i < SensorCount; i++) {
    if(values[i] > minL){
      Serial.print("En línea");
      Serial.print(" \t");
    }
    else{
      Serial.print("No línea");
      Serial.print(" \t");
    }
  }
  Serial.println();

  delay(500);
  
}
