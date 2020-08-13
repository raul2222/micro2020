#define DEBUG 0
void(* resetFunc) (void) = 0; //declare reset function @ address 0
void setPhase(unsigned char ph);
void advancePhase(char dir);

const unsigned char AHPin = 12;
const unsigned char ALPin = 6;
const unsigned char BHPin = 11;
const unsigned char BLPin = 5;
const unsigned char CHPin = 10;
const unsigned char CLPin = 4;
const unsigned char delayPin = A0;

char currentPhase = 0;
char motorDirection = 1;
unsigned long previousDelay = 0;

const unsigned char phaseStates[6]{
  B011000,
  B010010,
  B000110,
  B100100,
  B100001,
  B001001
};

void setPhase(unsigned char ph){
  unsigned char phase = phaseStates[ph];
  //Serial.println(ph);
  digitalWrite(AHPin, (phase & B100000) >> 5);

#if DEBUG
  delay (2000);
  Serial.print("ph: ");
  Serial.println(ph);
  Serial.print("phase: ");
  Serial.println(phase, BIN);
  Serial.print("(phase & B100000): ");
  Serial.println((phase & B100000), BIN);
  Serial.print("(phase & B100000): >> 5");
  unsigned char res = (phase & B100000) >> 5;
  Serial.println(res, BIN);
  Serial.print("bool: ");
  bool resbool = (phase & B100000) >> 5;
  Serial.println(resbool);
  delay (2000);
#endif
  
  digitalWrite(ALPin, (phase & B010000) >> 4);
  digitalWrite(BHPin, (phase & B001000) >> 3);
  digitalWrite(BLPin, (phase & B000100) >> 2);
  digitalWrite(CHPin, (phase & B000010) >> 1);
  digitalWrite(CLPin, phase & B000001);

#if DEBUG
  Serial.println("");
  Serial.println("Resultado final: ");


  bool resbool1 = (phase & B100000) >> 5;
  bool resbool2 = (phase & B010000) >> 4;
  bool resbool3 = (phase & B001000) >> 3;
  bool resbool4 = (phase & B000100) >> 2;
  bool resbool5 = (phase & B000010) >> 1;
  bool resbool6 = phase & B000001;

  Serial.print("AHPin: ");
  Serial.println(resbool1);
  Serial.print("ALPin: ");
  Serial.println(resbool2);
  Serial.print("BHPin: ");
  Serial.println(resbool3);
  Serial.print("BLPin: ");
  Serial.println(resbool4);
  Serial.print("CHPin: ");
  Serial.println(resbool5);
  Serial.print("CLPin: ");
  Serial.println(resbool6);
  delay (5000);
#endif
  
}

void advancePhase(char dir){
  currentPhase += dir;
  if(currentPhase > 5){
    currentPhase = 0;
  }else if(currentPhase < 0){
    currentPhase = 5;
  }
}

void setup(){
#if DEBUG
  Serial.begin(9600);
  delay(1000);
  Serial.println("Iniciando");
#endif
  pinMode(AHPin, OUTPUT);
  pinMode(ALPin, OUTPUT);
  pinMode(BHPin, OUTPUT);
  pinMode(BLPin, OUTPUT);
  pinMode(CHPin, OUTPUT);
  pinMode(CLPin, OUTPUT);
  pinMode(delayPin, INPUT);
}

void loop(){
    long delay = map(analogRead(delayPin), 0, 1024, 0, 140000);
    if(micros() - previousDelay <= delay) {
      return; 
    }else{
      previousDelay += delay;
      advancePhase(motorDirection);
      setPhase(currentPhase);
      
    }
  
    
}
