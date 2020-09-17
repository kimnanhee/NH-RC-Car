int IR1, IR2;
int motor_L = 8;
int motor_R = 9;

void setup() 
{
  Serial.begin(9600);
  pinMode(8, INPUT); // sensor
  pinMode(9, INPUT);
  pinMode(motor_L, OUTPUT); // motor
  pinMode(motor_R, OUTPUT);
}

void loop() 
{
  IR1 = digitalRead(1); // sensing
  IR2 = digitalRead(2);

  if(IR1 == HIGH && IR2 == HIGH) {
    digitalWrite(motor_L, 1);
    digitalWrite(motor_R, 1);
  }
  else if(IR1 == HIGH && IR2 == LOW) {
    digitalWrite(motor_L, 1);
    digitalWrite(motor_R, 0);
  }
  else if(IR1 == LOW && IR2 == HIGH) {
    digitalWrite(motor_L, 0);
    digitalWrite(motor_R, 1);
  }
  else {
    digitalWrite(motor_L, 0);
    digitalWrite(motor_R, 0);
  }

  delay(10);
}
