// DEKLARACJA WYPROWADZEN STEROWNIKA DRV8834
//#define ENABLE 4
#define M0 5
#define M1 6
#define STEP 10
#define DIR 11
#define SNAP1 2

// DEKLARACJA STAŁYCH
//#define delayVal 400

volatile byte snap1State = LOW;

void setup() {
  //pinMode(ENABLE, OUTPUT);
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(SNAP1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SNAP1), snapBTN1, CHANGE);  //LOW, RISING, FALLING, CHANGE
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
}

bool setMode(bool m0bool, bool m1bool) {
  digitalWrite(M0, m0bool);
  digitalWrite(M1, m1bool);
}

int moveStepperSmooth(int delayVal, int delayAcc, int steps) {
  for(int delayValAcc=delayAcc; delayValAcc > delayVal && snap1State == LOW; delayValAcc -= 1){
    digitalWrite(STEP, HIGH);
    delayMicroseconds(delayValAcc);
    digitalWrite(STEP, LOW);
    delayMicroseconds(delayValAcc);
  }
  for(int i=0; i < steps && snap1State == LOW; i++) {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(delayVal);
    digitalWrite(STEP, LOW);
    delayMicroseconds(delayVal);
  }
  for(int delayValAcc=delayVal; delayValAcc <= 1000 && snap1State == LOW; delayValAcc += 1){
    digitalWrite(STEP, HIGH);
    delayMicroseconds(delayValAcc);
    digitalWrite(STEP, LOW);
    delayMicroseconds(delayValAcc);
  }
}

void snapBTN1(){
  snap1State = digitalRead(SNAP1);
}
