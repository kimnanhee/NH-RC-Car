int onoff_1 = 3, dir_1 = 4, pwm_1 = 5;
int onoff_2 = 8, dir_2 = 9, pwm_2 = 10;
int IR1, IR2;

int RC_speed = 100;
int state = 0;
// 0-stop
// 1-front
// 2-back
// 3-left
// 4-right

void setup()
{
  pinMode(onoff_1, OUTPUT);
  pinMode(dir_1, OUTPUT);
  pinMode(pwm_1, OUTPUT);
  pinMode(onoff_2, OUTPUT);
  pinMode(dir_2, OUTPUT);
  pinMode(pwm_2, OUTPUT);
  
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  
  Serial.begin(9600);
}

void loop()
{
  IR1 = digitalRead(6); // sensing
  IR2 = digitalRead(7);

  if(IR1 == HIGH && IR2 == HIGH) state=0; // 길 인식 x - stop
  else if(IR1 == HIGH && IR2 == LOW) state=3; // 오른쪽에 길이 있을 때 - right
  else if(IR1 == LOW && IR2 == HIGH) state=4; // 왼쪽에 길이 있을 때 - left
  else if(IR1 == LOW && IR2 == LOW) state=1; // 앞에 길이 있을 때 - front

  digitalWrite(onoff_1, LOW); // enable
  digitalWrite(onoff_2, LOW);
  if (state == 2) // back
  {
    digitalWrite(dir_1, LOW);
    digitalWrite(dir_2, LOW);
  }
  else
  {
    digitalWrite(dir_1, HIGH);
    digitalWrite(dir_2, HIGH);
  }
  if (state == 0)
  {
    analogWrite(pwm_1, 0);
    analogWrite(pwm_2, 0);
  }
  else if (state == 3)
  {
    analogWrite(pwm_1, 0);
    analogWrite(pwm_2, 75);
    delay(100);
  }
  else if (state == 4)
  {
    analogWrite(pwm_1, 75);
    analogWrite(pwm_2, 0);
    delay(100);
  }
  else
  {
    analogWrite(pwm_1, RC_speed);
    analogWrite(pwm_2, RC_speed);
  }
  delay(50);
}
