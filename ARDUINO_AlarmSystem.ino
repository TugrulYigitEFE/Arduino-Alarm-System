#include <LiquidCrystal.h>
#include <Servo.h>


//set pin numbers 
const int ledPin1 = 13;
const int ledPin2 = 3;
const int buttonPin = 2;
const int buzzerPin = 12;
const int ldrPin = A0;
const int potPin = A1;

int buttonVal;

LiquidCrystal lcd_1(4, 5, 11, 10, 9, 8);

Servo myServo;
void setup () {

  lcd_1.begin(16, 2); // Set up the number of columns and rows on the LCD.

  myServo.attach(6); // servo pin 6

  Serial.begin(9600);
 
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ldrPin, INPUT);
}
 
void loop() {
 
  int ldrStatus = analogRead(ldrPin);  //read the state of the LDR value
 
  buttonVal = digitalRead(buttonPin);

  if(buttonVal == 0){
      
      digitalWrite(ledPin2, LOW);
      lcd_1.clear();
      lcd_1.setCursor(0, 0);
      lcd_1.print("SYSTEM ACTIVE");
      
      if (ldrStatus >= 400) {
   
      tone(buzzerPin, 100);
      digitalWrite(ledPin1, HIGH);
      delay(100);
   
      noTone(buzzerPin);
      digitalWrite(ledPin1, LOW);
      delay(100);
   
      
    }
    else {
   
      noTone(buzzerPin);
      digitalWrite(ledPin1, LOW);
   
    }

// POT //
    int potValue = analogRead(potPin);
    
    
    int angle = map(potValue, 0, 1023, 0, 180);
    
     myServo.write(angle);
     lcd_1.setCursor(1, 1);
     lcd_1.print(angle);
    delay(100);
 }
 
 else{
    
     lcd_1.setCursor(0, 0);
     lcd_1.print("SYSTEM INACTIVE");
     digitalWrite(ledPin2, HIGH);
  }
  
}
