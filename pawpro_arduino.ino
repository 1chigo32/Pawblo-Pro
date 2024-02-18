#include <LiquidCrystal.h>

const int motor1pin1 = A0;
const int motor1pin2 = A1;
const int motor2pin1 = A2;
const int motor2pin2 = A3;
const int speedpin = 10;
const int alarmEn = 9;
const int reminderEn = 13;
const int trickEn = 6;


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

const int trigpin = 7;
const int echopin = 8;

float duration, distance = 0;
float distArray[5] = {0};
unsigned long distInd = 0;
unsigned long currentTime = 0;
unsigned long printLastTime = 0;
const unsigned long timePrintOffset = 200;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


float getDistance(){
    digitalWrite(trigpin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin, LOW);
    duration = pulseIn(echopin, HIGH);
    distArray[distInd] = duration * 0.0343 / 2;
    int sum = 0;
    for (int i = 0; i < 5; i++){
      sum = sum + distArray[i];
    }
    distance = sum/5;
    distInd = distInd + 1;
    distInd = distInd % 5;
    if (currentTime - printLastTime > timePrintOffset) {
      printLastTime = millis();
    }
    return distance;

}

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(speedpin, OUTPUT);
  pinMode(alarmEn, INPUT);
  pinMode(reminderEn, INPUT);
  pinMode(trickEn, INPUT);

  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  
  analogWrite(speedpin, 130);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Distance:       ");
  Serial.begin(9600);
}

void driveBack(){
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}


void brake(){
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}

void alarmMode(){

  lcd.setCursor(0,0);
  lcd.print("Distance:       ");
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  currentTime = millis();
  if (currentTime - printLastTime > timePrintOffset){
    getDistance();
    lcd.print(distance);
    lcd.print("            ");
    Serial.println(distance);
    if (distance < 15) {
      driveBack();
    } else {
      brake();
    }
  }
}

void reminderMode() {
  /*
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Schedule:");
  lcd.setCursor(0,1);
  lcd.print("9AM: School");
  delay(800);
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.print("4PM: Design Team");
  delay(800);
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.print("Today's chores:");
  lcd.print("Do laundry");
  delay(800);
  */
  lcd.setCursor(0,0);
  lcd.print("9AM: School      ");
  lcd.setCursor(0,1);
  lcd.print("4PM: Design Team");
  brake();
  
}

void trickMode(){
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  lcd.setCursor(0,0);
  lcd.print("               ");
  lcd.setCursor(0,1);
  lcd.print("               ");
  delay(2000);
}

void alarmOff(){
  //lcd.print("alarm mode off");
  lcd.clear();
  brake();
}

void loop() {
  // put your main code here, to run repeatedly:
  bool alarm = digitalRead(alarmEn);
  bool reminder = digitalRead(reminderEn);
  bool trick = digitalRead(trickEn);

  if (alarm) {
    alarmMode();
  } else if (reminder) {
    reminderMode();
  } else if (trick) {
    trickMode();
  } else {
    alarmOff();
  }
}
