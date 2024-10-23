/*  Name: Tavina Chen
    Date: March 2023
    
    Description: This code will test for 6 different inputs, 5 buttons and 1 for the water detector.
    It will also display the timer on a 4-digit 7-segement display where the first two digits represent
    the hours and the last two represent the minutes. Two of the buttons control the the number of hours 
    and another 2 does the same but for minutes. The final button will toggle between customization mode 
    and timer mode. The user will not be able to edit the timer unless they are in customization mode
    and the timer will not run unless it is in timer mode. 

*/
//Lights & Sound
int lightsSoundPin = 10;

//Time Buttons
int hourMinusButtonPin = 2;
int hourMinus;
int hourPlusButtonPin = 13;
int hourPlus;
int minuteMinusButtonPin = 3;
int minuteMinus;
int minutePlusButtonPin = 11;
int minutePlus; 
int buttonPressDelay = 150; 

//Timer Variables
int hours = 0;
int minutes = 0;
int totalTime = 60; 
int countdown = 60;

//Toggle Button
int toggleButtonPin = 12; 
int buttonStateOld = 0;
int buttonStateNew;
int timeState = 0;
int stateChangeDelay = 5;

//4 Digit 7 Segment Display
int segA = A4, segB = A0, segC = 4, segD = 8, segE = 9, segF = A3, segG = 5;

int dig1 = A5, dig2 = A2, dig3 = A1, dig4 = 6;

int dispFlash = 5;

int disp1, disp2, disp3, disp4;

int ON = HIGH, OFF = LOW;

//Water Detection System
int waterDetectionPin = 7; 
int waterDetection;

void setup() {
  //Buttons
  pinMode(hourMinusButtonPin, INPUT);
  pinMode(hourPlusButtonPin, INPUT);
  pinMode(minuteMinusButtonPin, INPUT);
  pinMode(minuteMinusButtonPin, INPUT);
  
  pinMode(toggleButtonPin, INPUT);
  
  //Lights & Sound
  pinMode(lightsSoundPin, OUTPUT);
  
  //4 Digit 7-Segment Display
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(dig1, OUTPUT);
  pinMode(dig2, OUTPUT);
  pinMode(dig3, OUTPUT);
  pinMode(dig4, OUTPUT);
  
  //Water Detection System
  pinMode(waterDetectionPin, INPUT);
}

void loop() {
  //Display, Countdown, Alarm, Detection
  if (timeState == 0) { //countdown
    for (int j = countdown; j > 0; j--) {
      for(int i = 0; i < 2400; i++) {
        if (timeState == 0) {
          disp1 = countdown/600;
          disp2 = countdown/60%10;
          disp3 = countdown%60/10;
          disp4 = countdown%60%10;
          displayDigits(disp1, disp2, disp3, disp4);
          toggleButtons(); //detects for the buttons
          detectWater(); 
        }
      }
      countdown--;
    }
    if (countdown <= 0) { //Alarm goes off
      displayDigits(0, 0, 0, 0);
      toggleButtons();
      tone(lightsSoundPin, 392, 1000);
      delay(200);
      noTone(lightsSoundPin);
      delay(200);
      detectWater();
    }
    
  } else { //Customization mode 
    disp1 = totalTime/600;
    disp2 = totalTime/60%10;
    disp3 = totalTime%60/10;
    disp4 = totalTime%60%10;
    
    displayDigits(disp1, disp2, disp3, disp4);
    toggleButtons();
  }
}

void displayNumber(int number)
{
  if (number == 0){
    digitalWrite(segA, ON);
    digitalWrite(segB, ON);
    digitalWrite(segC, ON);
    digitalWrite(segD, ON);
    digitalWrite(segE, ON);
    digitalWrite(segF, ON);
    digitalWrite(segG, OFF);
    delay(dispFlash);
  } else
  if (number == 1) {
    digitalWrite(segA, OFF);
    digitalWrite(segB, ON);
    digitalWrite(segC, ON);
    digitalWrite(segD, OFF);
    digitalWrite(segE, OFF);
    digitalWrite(segF, OFF);
    digitalWrite(segG, OFF);
    delay(dispFlash);
  } else
  if (number == 2) {
    digitalWrite(segA, ON);
    digitalWrite(segB, ON);
    digitalWrite(segC, OFF);
    digitalWrite(segD, ON);
    digitalWrite(segE, ON);
    digitalWrite(segF, OFF);
    digitalWrite(segG, ON);
    delay(dispFlash);
  } else
  if (number == 3) {
    digitalWrite(segA, ON);
    digitalWrite(segB, ON);
    digitalWrite(segC, ON);
    digitalWrite(segD, ON);
    digitalWrite(segE, OFF);
    digitalWrite(segF, OFF);
    digitalWrite(segG, ON);
    delay(dispFlash);
  } else
  if (number == 4) {
    digitalWrite(segA, OFF);
    digitalWrite(segB, ON);
    digitalWrite(segC, ON);
    digitalWrite(segD, OFF);
    digitalWrite(segE, OFF);
    digitalWrite(segF, ON);
    digitalWrite(segG, ON);
    delay(dispFlash);
  } else
  if (number == 5) {
    digitalWrite(segA, ON);
    digitalWrite(segB, OFF);
    digitalWrite(segC, ON);
    digitalWrite(segD, ON);
    digitalWrite(segE, OFF);
    digitalWrite(segF, ON);
    digitalWrite(segG, ON);
    delay(dispFlash);
  } else
  if (number == 6) {
    digitalWrite(segA, ON);
    digitalWrite(segB, OFF);
    digitalWrite(segC, ON);
    digitalWrite(segD, ON);
    digitalWrite(segE, ON);
    digitalWrite(segF, ON);
    digitalWrite(segG, ON);
    delay(dispFlash);
  } else
  if (number == 7) {
    digitalWrite(segA, ON);
    digitalWrite(segB, ON);
    digitalWrite(segC, ON);
    digitalWrite(segD, OFF);
    digitalWrite(segE, OFF);
    digitalWrite(segF, OFF);
    digitalWrite(segG, OFF);
    delay(dispFlash);
  } else
  if (number == 8) {
    digitalWrite(segA, ON);
    digitalWrite(segB, ON);
    digitalWrite(segC, ON);
    digitalWrite(segD, ON);
    digitalWrite(segE, ON);
    digitalWrite(segF, ON);
    digitalWrite(segG, ON);
    delay(dispFlash);
  } else {
    digitalWrite(segA, ON);
    digitalWrite(segB, ON);
    digitalWrite(segC, ON);
    digitalWrite(segD, OFF);
    digitalWrite(segE, OFF);
    digitalWrite(segF, ON);
    digitalWrite(segG, ON);
    delay(dispFlash);
  }
}

void displayDigits(int disp1, int disp2, int disp3, int disp4) 
{
  //4 Digit 7 Segment Display
  
  //Digit 1
  digitalWrite(dig1, LOW);
  digitalWrite(dig2, HIGH);
  digitalWrite(dig3, HIGH);
  digitalWrite(dig4, HIGH);
  
  displayNumber(disp1);
  
  //Digit 2
  digitalWrite(dig1, HIGH);
  digitalWrite(dig2, LOW);
  digitalWrite(dig3, HIGH);
  digitalWrite(dig4, HIGH);
  
  displayNumber(disp2);
  
  //Digit 3
  digitalWrite(dig1, HIGH);
  digitalWrite(dig2, HIGH);
  digitalWrite(dig3, LOW);
  digitalWrite(dig4, HIGH);
  
  displayNumber(disp3);
  
  //Digit 4
  digitalWrite(dig1, HIGH);
  digitalWrite(dig2, HIGH);
  digitalWrite(dig3, HIGH);
  digitalWrite(dig4, LOW);
  
  displayNumber(disp4);
}

void toggleButtons()
{
  hourMinus = digitalRead(hourMinusButtonPin);
  hourPlus = digitalRead(hourPlusButtonPin);
  minuteMinus = digitalRead(minuteMinusButtonPin);
  minutePlus = digitalRead(minutePlusButtonPin);
  
  if (hourMinus == HIGH && timeState == 1 && totalTime >=60)
  {
    totalTime -= 60;
    delay(buttonPressDelay);
  }
  
  if(hourPlus == HIGH && timeState == 1)
  {
    totalTime += 60;
    delay(buttonPressDelay);
  }
  
  if (minuteMinus == HIGH && timeState == 1 && totalTime > 1)
  {
    totalTime -= 1;
    delay(buttonPressDelay);
  }
  
  if(minutePlus == HIGH && timeState == 1)
  {
    totalTime += 1;
    delay(buttonPressDelay);
  }
  buttonStateNew = digitalRead(toggleButtonPin);
  if (buttonStateOld == 0 && buttonStateNew == 1)
  {
    if (timeState == 0) {
      timeState=1; //Customization mode
    } else {
      countdown = totalTime;
      timeState=0; //Timer mode
    }
    tone(lightsSoundPin, 392, 200);
    delay(200);
    noTone(lightsSoundPin);
  }
  buttonStateOld=buttonStateNew;
  delay(stateChangeDelay);
}

void detectWater()
{
  waterDetection = digitalRead(waterDetectionPin);
      if (waterDetection == HIGH) {
        countdown = totalTime;
        delay(200);
      }
}
