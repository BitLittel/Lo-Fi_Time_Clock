byte speedLight = 1, postLight = 1;
byte pin_min = 4, pin_hours = 2;
byte sec_0 = 0, hors_0 = 0, hors_1 = 4, min_0 = 4, min_1 = 5;
byte out1 = 13, out2 = 12, out4 = 11, out8 = 10;
byte key1 = 9, key2 = 8, key3 = 7, key4 = 6;
bool hold_min = false, hold_hours = false;

unsigned long sec;

void show(int a[])
{
  setNumber(a[0]);
  digitalWrite(key1,HIGH);
  delay(speedLight);
  digitalWrite(key1,LOW);
  delay(postLight);
  
  setNumber(a[1]);
  digitalWrite(key2,HIGH);
  delay(speedLight);
  digitalWrite(key2,LOW);
  delay(postLight);

  setNumber(a[2]);
  digitalWrite(key3,HIGH);
  delay(speedLight);
  digitalWrite(key3,LOW);
  delay(postLight);

  setNumber(a[3]);
  digitalWrite(key4,HIGH);
  delay(speedLight);
  digitalWrite(key4,LOW);
  delay(postLight);
}
void setNumber(int num)
{
  switch (num)
  {
    case 0:
    digitalWrite (out1,LOW);
    digitalWrite (out2,LOW);
    digitalWrite (out4,LOW);
    digitalWrite (out8,LOW);
    break;
    case 1:
    digitalWrite (out1,HIGH);
    digitalWrite (out2,LOW);
    digitalWrite (out4,LOW);
    digitalWrite (out8,LOW);
    break;
    case 2:
    digitalWrite (out1,LOW);
    digitalWrite (out2,HIGH);
    digitalWrite (out4,LOW);
    digitalWrite (out8,LOW);
    break;
    case 3:
    digitalWrite (out1,HIGH);
    digitalWrite (out2,HIGH);
    digitalWrite (out4,LOW);
    digitalWrite (out8,LOW);
    break;
    case 4:
    digitalWrite (out1,LOW);
    digitalWrite (out2,LOW);
    digitalWrite (out4,HIGH);
    digitalWrite (out8,LOW);
    break;
    case 5:
    digitalWrite (out1,HIGH);
    digitalWrite (out2,LOW);
    digitalWrite (out4,HIGH);
    digitalWrite (out8,LOW);
    break;
    case 6:
    digitalWrite (out1,LOW);
    digitalWrite (out2,HIGH);
    digitalWrite (out4,HIGH);
    digitalWrite (out8,LOW);
    break;
    case 7:
    digitalWrite (out1,HIGH);
    digitalWrite (out2,HIGH);
    digitalWrite (out4,HIGH);
    digitalWrite (out8,LOW);
    break;
    case 8:
    digitalWrite (out1,LOW);
    digitalWrite (out2,LOW);
    digitalWrite (out4,LOW);
    digitalWrite (out8,HIGH);
    break;
    case 9:
    digitalWrite (out1,HIGH);
    digitalWrite (out2,LOW);
    digitalWrite (out4,LOW);
    digitalWrite (out8,HIGH);
    break;
  }
}

void setup() {
  TCCR2B = TCCR2B & 0b11111000 | 0x01;
  analogWrite(3, 150);
  
  pinMode(out1,OUTPUT);
  pinMode(out2,OUTPUT);
  pinMode(out4,OUTPUT);
  pinMode(out8,OUTPUT);

  pinMode(key1,OUTPUT);
  pinMode(key2,OUTPUT);
  pinMode(key3,OUTPUT);
  pinMode(key4,OUTPUT);
  // кнопки
  pinMode(pin_min, INPUT_PULLUP);
  pinMode(pin_hours, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int set_state_min = digitalRead(pin_min), a[3];
  int set_state_hours = digitalRead(pin_hours);
  unsigned long currentTime = millis();
  
  if ((currentTime-(sec*1000)) > 1000) {sec++; sec_0++;}
  
  if (set_state_min == LOW and hold_min == false) {
    min_1++;
    hold_min = true;
  } else if (set_state_min == HIGH and hold_min == true) {
    hold_min = false;}

  if (set_state_hours == LOW and hold_hours == false) {
    hors_1++;
    hold_hours = true;
  } else if (set_state_hours == HIGH and hold_hours == true) {
    hold_hours = false;}
  

  if (sec_0 >= 60) {
    sec_0 = 0;
    min_1++;
  }
  if (min_1 >= 10) {
    min_0++;
    min_1 = 0;
  }
  if (min_0 >= 6) {
    min_0 = 0;
    hors_1++;
  }
  if (hors_1 >= 10) {
    hors_1 = 0;
    hors_0++;
  }
  if (hors_0 >= 2 && hors_1 >= 4) {
    sec_0 = 0;
    min_1 = 0;
    min_0 = 0;
    hors_1 = 0;
    hors_0 = 0;
  }
  a[0] = hors_0;
  a[1] = hors_1;
  a[2] = min_0;
  a[3] = min_1;

  show(a);

}
