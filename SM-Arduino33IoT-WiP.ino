// PARAMETRY ŚRUBY
#define SKOK_GWINTU 
#define SREDNICA_GWINTU 
#define DLUGOSC_ROBOCZA 

// DRV8825 - WYPROWADZENIA
#define ENABLE 
#define M0 
#define M1 
#define M2 
#define RESET 
#define SLEEP 
#define STEP 
#define DIR 

#define SNAP_LEFT 
#define SNAP_RIGHT 
#define BUZZER 

// SETUP
void setup() {
  Serial.begin(9600);
  //Serial.setTimeout(0);
  //while (!Serial) {;}
  Serial.println("Connected.");
  
  pinMode(ENABLE , INPUT);
  pinMode(M0 , INPUT);
  pinMode(M1 , INPUT);
  pinMode(M2 , INPUT);
  pinMode(RESET , INPUT);
  pinMode(SLEEP , INPUT);
  pinMode(STEP , INPUT);
  pinMode(DIR , INPUT);
  pinMode(SNAP_LEFT , INPUT_PULLUP);
  pinMode(SNAP_RIGHT , INPUT_PULLUP);
  pinMode(BUZZER , OUTPUT);

  attachInterrupt(digitalPinToInterrupt(SNAP_LEFT), <FUNCTION>, HIGH);
  attachInterrupt(digitalPinToInterrupt(SNAP_RIGHT), <FUNCTION>, HIGH);
  // attachInterrupt - możliwe opcje: HIGH, LOW, RISING, FALLING, CHANGE

  autoHome();
}

// ZMIENNE GLOBALNE
int DELAY_VAL = 400;
int DELAY_ACC = 1000;
int DELAY_STEP = 2000;
const unsigned long serialDelay = 1000000;  // odbiór danych co 1 sekundę

//////////////// MAIN
void loop() {
  if(Serial.available() > 0){
    
    readSerialData();
    loopStartTime = micros();
    setStepMode();
    setDir(readDir);
    moveStepperMotor();
    loopCurrentTime = micros();
    delayMicroseconds(serialDelay - (loopCurrentTime - loopStartTime));
  }
}

// READ SERIAL DATA
void readSerialData() {
  String serialData = Serial.readString();  // Odczyt ciągu znaków

  // Rozbicie danych
  String readCommand = serialData.substring(0,2);
  String readDir = serialData.substring(2,4);
  String readSteps = serialData.substring(4,7);

  // Konwersja danych
  int steps = readSteps.toInt();
}

// SET STEP MODE
void setStepMode() {    // bool | https://www.pololu.com/product/2133
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
  digitalWrite(M@, LOW);
}

// SET DIR
String setDir(String dirRead) {
  if(dirRead == "L") {
    digitalWrite(DIR, HIGH);
  } else if(dirRead == "R") {
    digitalWrite(DIR, LOW);
  }
}

// MOVE STEPPER MOTOR
int moveStepperMotor(int DELAYVAL, int DELAYACC, int DELAY_STEP) {
  // stepsStart=1/6steps | stepsMid=2/3steps | stepsEnd=1/6steps //
  for(int delayValAcc=DELAY_ACC; delayValAcc > DELAY_VAL && snapLeftState == LOW && snapRightState == LOW; delayValAcc -= 1){
    digitalWrite(STEP, HIGH);
    delayMicroseconds(DELAY_VAL);
    digitalWrite(STEP, LOW);
    delayMicroseconds(DELAY_VAL);
  }

  for(int i=0; i < stepsMid && snapLeftState == LOW && snapRightState == LOW; i++) {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(DELAY_VAL);
    digitalWrite(STEP, LOW);
    delayMicroseconds(DELAY_VAL);
  }

  for(int delayValAcc=DELAY_VAL; delayValAcc <= 1000 && snapLeftState == LOW && snapRightState == LOW; delayValAcc += 1) {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(DELAY_VAL);
    digitalWrite(STEP, LOW);
    delayMicroseconds(DELAY_VAL);
  }
}

// AUTO HOME
void autoHome() {
  while(snapLeftState == LOW) {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(DELAY_VAL);
    digitalWrite(STEP, LOW);
    delayMicroseconds(DELAY_VAL);
  }
}
