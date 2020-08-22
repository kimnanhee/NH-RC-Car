#include <IRremote.h>

int RECV_pin = 11;
IRrecv irrecv(RECV_pin);
decode_results results;

int onoff_1 = 3, dir_1 = 4, pwm_1 = 5;
int onoff_2 = 8, dir_2 = 9, pwm_2 = 10;

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

  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop()
{
  if (irrecv.decode(&results))
  {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  if (results.value == 0xFFE01F) { // - 
    RC_speed -= 10; 
    delay(100);
  }
  else if (results.value == 0xFFA857) { // +
    RC_speed += 10;
    delay(100);
  }
  else if (results.value == 0xFF38C7) state = 0; // 5 - stop
  else if (results.value == 0xFF18E7) state = 1; // 2 - front
  else if (results.value == 0xFF4AB5) state = 2; // 8 - back
  else if (results.value == 0xFF10EF) state = 3; // 4 - left
  else if (results.value == 0xFF5AA5) state = 4; // 6 - right

  if (RC_speed > 255) RC_speed = 255;
  else if (RC_speed < 50) RC_speed = 50;

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
    analogWrite(pwm_2, 50);
    delay(500);
    state = 1;
  }
  else if (state == 4)
  {
    analogWrite(pwm_1, 50);
    analogWrite(pwm_2, 0);
    delay(500);
    state = 1;
  }
  else
  {
    analogWrite(pwm_1, RC_speed);
    analogWrite(pwm_2, RC_speed);
  }
  Serial.print("speed-");
  Serial.println(RC_speed);
  delay(10);
}
