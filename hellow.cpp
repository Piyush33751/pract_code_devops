#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include<dht.h>
// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);
dht DHT;

// Pin definitions
#define IR1Pin A0
#define IR2Pin A1   
#define DHT11_PIN A5
#define motorPin_IN2 6
#define motorPin_IN1 9
#define motorPin_IN4 3
#define motorPin_IN3 5
#define TrigPin1 11
#define EchoPin1 10
#define TrigPin2 8
#define EchoPin2 7
#define buzzer A3
#define C8 1000
#define DHT11_PIN A2

// Function prototypes
void forward(void);
void tilt_left(void);
void tilt_right(void);
void backwards(void);
void brake(void);
int getDistance(int EchoPin, int TrigPin);
void op2(void);
void ultrasound(void);
void playTone(int, int);
void humidity_detector(void);
void Decelerate_Forward(void);
void endof(void);
int countA;
int countB;

void setup() {
  // Motor pin setup
  pinMode(motorPin_IN2, OUTPUT);
  pinMode(motorPin_IN1, OUTPUT);
  pinMode(motorPin_IN4, OUTPUT);
  pinMode(motorPin_IN3, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  PCICR |= B00000100; // Enable interrupts
  PCMSK2 |= B00010100;

  // Ultrasonic sensor pin setup
  pinMode(TrigPin1, OUTPUT);
  pinMode(EchoPin1, INPUT);
  pinMode(TrigPin2, OUTPUT);
  pinMode(EchoPin2, INPUT);
  pinMode(buzzer, OUTPUT);

  // LCD setup
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(1000);
  lcd.clear();

  // Serial monitor setup
  Serial.begin(9600);
  lcd.print("Starting System");
  delay(4000);
}

void loop() {
  // Variables for IR sensor readings and distance
  int IR1_Val = analogRead(IR1Pin);
  int IR2_Val = analogRead(IR2Pin);
  int Distance1 = getDistance(EchoPin1, TrigPin1);
  int Distance2 = getDistance(EchoPin2, TrigPin2);

if (!digitalRead(4) && digitalRead(2)==1)
 {
  delay(1000);
  lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("end of Ops");
 }

else if (!digitalRead(2) && digitalRead(4)==1)
 { 
  delay(1000);
  lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Start of Ops");
 
  // Logic for IR sensors 
 while(Distance2>20 && Distance1>20)
  {
  if (IR1_Val < 300 && IR2_Val < 300) {  // Both sensors on white
    forward();
  } else if (IR1_Val > 300) { // IR1 detects black
    tilt_left();
  } else if (IR2_Val > 300) { // IR2 detects black
    tilt_right();
  }
  IR1_Val = analogRead(IR1Pin);
  IR2_Val = analogRead(IR2Pin);
  Distance1 = getDistance(EchoPin1,TrigPin1);//calling for front ultrasound
  Distance2 = getDistance(EchoPin2,TrigPin2);
  }
  brake();
  ultrasound();
  delay(1000);
  humidity_detector();
  delay(2000);
 }
 
else if(!digitalRead(4) && !digitalRead(2))
 {
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Start of Ops 2");
  Distance1 = getDistance(EchoPin1, TrigPin1);
  Distance2 = getDistance(EchoPin2, TrigPin2);
  while(Distance2>10 && Distance1>10)
  {
    Distance1 = getDistance(EchoPin1, TrigPin1);
    Distance2 = getDistance(EchoPin2, TrigPin2);
    forward();
  }
  while(Distance1<10)
  {
  Decelerate_Forward();
  Distance1 = getDistance(EchoPin1, TrigPin1);
  Distance2 = getDistance(EchoPin2, TrigPin2);
  ultrasound();
  delay(1000);
  humidity_detector();
  delay(2000);
 }
  
  while(Distance2<10)
  {
  backwards();
  delay(2000);
  brake();
  Distance1 = getDistance(EchoPin1, TrigPin1);
  Distance2 = getDistance(EchoPin2, TrigPin2);
  ultrasound();
  delay(1000);
  humidity_detector();
  delay(2000);
   }
  
 
  delay(2000);
  
 }

  delay(50);
}

// Function for forward motion
void forward() {
  analogWrite(motorPin_IN2, 70);
  digitalWrite(motorPin_IN1, 0);
  digitalWrite(motorPin_IN4, LOW);
  analogWrite(motorPin_IN3, 90);
  delay(10);
}

// Function for left tilt
  void tilt_left() {
    analogWrite(motorPin_IN2,0);
    analogWrite(motorPin_IN1, LOW);
    analogWrite(motorPin_IN4, LOW);
    analogWrite(motorPin_IN3, 100);
    delay(10);
  }

  // Function for right tilt
  void tilt_right() {
    analogWrite(motorPin_IN2, 100);
    digitalWrite(motorPin_IN1, LOW);
    digitalWrite(motorPin_IN4, LOW);
    analogWrite(motorPin_IN3, LOW);
    delay(10);
  }

// Function for backward motion
void backwards() {
  digitalWrite(motorPin_IN2, LOW);
  analogWrite(motorPin_IN1, 95);
  analogWrite(motorPin_IN4, 100);
  digitalWrite(motorPin_IN3, LOW);
}
void brake(){
  digitalWrite(motorPin_IN2, HIGH);
  digitalWrite(motorPin_IN1, HIGH);
  digitalWrite(motorPin_IN4, HIGH);
  digitalWrite(motorPin_IN3, HIGH);

}

// Function to calculate distance using ultrasonic sensor
int getDistance(int EchoPin, int TrigPin)
{
  int distance;
  long pulseDuration;
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin,LOW);

  pulseDuration = pulseIn(EchoPin, HIGH);
  distance = pulseDuration / 58 ;
  return distance;
}

ISR (PCINT2_vect) {
if (!digitalRead(2))
countA++;
else if (!digitalRead(4))
countB++;
}
void ultrasound(void)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Object detected");
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print("BRAKING");
    delay(2000);
    playTone(C8,1000);
    //new delay added
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Clear Trash -");
    lcd.setCursor(0,1);
    lcd.print("out of the way");
    
}
void playTone(int frequency, int duration) {
  int period = 1000000 / frequency; // Calculate the period in microseconds
  int halfPeriod = period / 2;     // Half period for HIGH and LOW
  long cycles = duration * 1000L / period; // Total number of cycles for the duration

  for (long i = 0; i < cycles; i++) {
    digitalWrite(buzzer, HIGH); // Generate HIGH signal
    delayMicroseconds(halfPeriod);
    digitalWrite(buzzer, LOW); // Generate LOW signal
    delayMicroseconds(halfPeriod);
  }
}
void humidity_detector(void)
{
  int chk = DHT.read11(DHT11_PIN);
  lcd.clear();
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("Temp = ");
  lcd.setCursor(7,0);
  lcd.print(DHT.temperature);
  lcd.setCursor(0,1);
  lcd.print("Humid = ");
  lcd.setCursor(8,1);
  lcd.print(DHT.humidity);
  delay(1000);
}
void Decelerate_Forward() {
    Serial.println("Decelerating: 100 to 0 speed forward");

    for (int i = 100; i >= 0; i--)  // Start at speed 100 and reduce to 0
    { 
        digitalWrite(motorPin_IN1, LOW);
        analogWrite(motorPin_IN2, i);
        digitalWrite(motorPin_IN4, LOW);
        analogWrite(motorPin_IN3, i);
        delay(20);  // Adjust delay for smooth deceleration
    }

    Serial.println("Deceleration complete");
}
void endof(){
delay(1000);
  brake();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("End of Ops");//cut all operationas
  delay(6000);
}

