// DEKLARACJA WYPROWADZEN STEROWNIKA DRV8834
//#define ENABLE 4
#define M0 5
#define M1 6
#define STEP 10
#define DIR 11

// DEKLARACJA STAŁYCH
//#define delayVal 400

void setup() {
  //pinMode(ENABLE, OUTPUT);
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
}

// ZMIENNE GLOBALNE
int delVal = 400;
int delAcc = 1000;
int stVal = 2000;

void loop() {  
  digitalWrite(DIR, LOW);
  setMode(HIGH,LOW);
  moveStepperSmooth(delVal,delAcc,stVal*2);
  digitalWrite(DIR, HIGH);
  setMode(HIGH,LOW);
  moveStepperSmooth(delVal,delAcc,stVal*2);
  
  digitalWrite(DIR, LOW);
  setMode(LOW,HIGH);
  moveStepperSmooth(delVal,delAcc,stVal*4);
  digitalWrite(DIR, HIGH);
  setMode(LOW,HIGH);
  moveStepperSmooth(delVal,delAcc,stVal*4);
  
  digitalWrite(DIR, LOW);
  setMode(HIGH,HIGH);
  moveStepperSmooth(delVal,delAcc,stVal*8);
  digitalWrite(DIR, HIGH);
  setMode(HIGH,HIGH);
  moveStepperSmooth(delVal,delAcc,stVal*8);

  //
  delay(2000);
  digitalWrite(DIR, LOW);
  setMode(HIGH,LOW);
  moveStepper(delVal,delAcc,stVal);
  digitalWrite(DIR, HIGH);
  setMode(HIGH,LOW);
  moveStepper(delVal,delAcc,stVal);
  delay(2000);  
  
  digitalWrite(DIR, LOW);
  setMode(LOW,HIGH);
  moveStepper(delVal,delAcc,stVal*2);
  digitalWrite(DIR, HIGH);
  setMode(LOW,HIGH);
  moveStepper(delVal,delAcc,stVal*2);
  delay(2000);
  
  digitalWrite(DIR, LOW);
  setMode(HIGH,HIGH);
  moveStepper(delVal,delAcc,stVal*4);
  digitalWrite(DIR, HIGH);
  setMode(HIGH,HIGH);
  moveStepper(delVal,delAcc,stVal*4);
  delay(5000);
}

bool setMode(bool m0bool, bool m1bool) {
  digitalWrite(M0, m0bool);
  digitalWrite(M1, m1bool);
}

int moveStepper(int delayVal, int delayAcc, int steps) {
  for(int i=0; i < steps; i++) {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(delayVal);
    digitalWrite(STEP, LOW);
    delayMicroseconds(delayVal);
  }
}

int moveStepperSmooth(int delayVal, int delayAcc, int steps) {
  for(int delayValAcc=delayAcc; delayValAcc > delayVal; delayValAcc -= 1){
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
  for(int delayValAcc=delayVal; delayValAcc <= 1000; delayValAcc += 1){
    digitalWrite(STEP, HIGH);
    delayMicroseconds(delayValAcc);
    digitalWrite(STEP, LOW);
    delayMicroseconds(delayValAcc);
  }
}
