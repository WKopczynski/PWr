
// DEKLARACJA WYPROWADZEN STEROWNIKA A4988
//#define ENABLE 4
#define MS1 5
#define MS2 6
#define MS3 7
//#define RESET 8
//#define SLEEP 9
#define STEP 10
#define DIR 11


void setup() {
  //pinMode(ENABLE, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  //pinMode(RESET, OUTPUT);
  //pinMode(SLEEP, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
  //pinMode(STEP2,OUTPUT);
}


void loop() {
  digitalWrite(DIR, LOW);
  setMode(HIGH,LOW,LOW);
  moveStepper(400,1000,400);
  digitalWrite(DIR, HIGH);
  setMode(HIGH,LOW,LOW);
  moveStepper(400,1000,400);
  
  digitalWrite(DIR, LOW);
  setMode(HIGH,HIGH,LOW);
  moveStepper(400,1000,400);
  digitalWrite(DIR, HIGH);
  setMode(HIGH,HIGH,LOW);
  moveStepper(400,1000,400);
  
  digitalWrite(DIR, LOW);
  setMode(HIGH,HIGH,HIGH);
  moveStepper(400,1000,400);
  digitalWrite(DIR, HIGH);
  setMode(HIGH,HIGH,HIGH);
  moveStepper(400,1000,400);
}


bool setMode(bool ms1bool, bool ms2bool, bool ms3bool) {
  digitalWrite(MS1, ms1bool);
  digitalWrite(MS2, ms2bool);
  digitalWrite(MS3, ms3bool);
}


int moveStepper(int delayVal, int delayAcc, int steps) {
  for(int delayValAcc=delayAcc; delayValAcc > delayVal; delayValAcc -= 2){
    digitalWrite(STEP, HIGH);
    delayMicroseconds(delayValAcc);
    digitalWrite(STEP, LOW);
    delayMicroseconds(delayValAcc);
  }
  for(int i=0; i < steps; i++) {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(delayVal);
    digitalWrite(STEP, LOW);
    delayMicroseconds(delayVal);
  }
  for(int delayValAcc=delayVal; delayValAcc <= 1000; delayValAcc += 2){
    digitalWrite(STEP, HIGH);
    delayMicroseconds(delayValAcc);
    digitalWrite(STEP, LOW);
    delayMicroseconds(delayValAcc);
  }
}
