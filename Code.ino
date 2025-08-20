
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#define pir 3
#define echo 9
#define trigger 8
#define servo 2
#define buzzer 10

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;

void setup() 
{
  pinMode(pir, INPUT);
  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(buzzer, OUTPUT);
  myservo.attach(servo);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Pet Feeder Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  int motion = digitalRead(pir);

  if (motion == HIGH) {
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);

    long duration = pulseIn(echo, HIGH);
    int distance = duration * 0.034 / 2;

    if (distance <= 15)
     {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Welcome");
      delay(2000);

      myservo.write(180);

      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);

      delay(2000);  

      myservo.write(0);   

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Thank you");
      delay(2000);
      lcd.clear();
    } 
    else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Too Far");
      lcd.setCursor(0, 1);
      lcd.print("Come Closer");
      delay(2000);
      lcd.clear();
    }
  } 
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Standby");
    lcd.setCursor(0, 1);
    lcd.print("Waiting");
    delay(500);
  }
}
