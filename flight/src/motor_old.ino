const int dirPin = D7;
const int stepPin = D6;
const int MS1 = D5;
const int MS2 = D4;
const int MS3 = D3;
const int stepsPerRevolution = 5000;


void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);

}

void loop() {
  digitalWrite(dirPin, HIGH); //high is clockwise
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(MS3, LOW);

  Serial.println("Start deployment");
  for (int x = 0; x < stepsPerRevolution; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1500);
  }
  delay(1000); 
  

  digitalWrite(dirPin, LOW);

  Serial.println("Start retraction");
  for (int x = 0; x < stepsPerRevolution; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1500);
  }
  delay(1000);  
}
