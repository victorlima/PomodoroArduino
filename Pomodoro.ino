#include <LiquidCrystal.h>
#include <Time.h>  
#include <Timer.h>

#define POMODORO_TIME 2700000 // 45 minutos of work...

// initialize the library with the numbers of the interface pins
int buttonPin = 5;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
Timer t;
int state = 0, timer = -1;
int secs = 0;

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Time to Work...");
  Serial.begin(9600); 

  // setup button in pin 2
  pinMode(buttonPin, INPUT); 

  t.after( POMODORO_TIME, pomodoroIsUp );
  int timer = t.every( 1000, syncTime );
  
  state = 1;
}

void syncTime( ) {  
  secs++;
  setTime(secs);
  digitalClockDisplay();  
}

void togglePomodoro( ) {
  if( state == 1 ) {
    state = 0;
    lcd.setCursor(0,0);
    lcd.print("STOPPED!!!      ");
  } else if( state == 0 ) {
    lcd.setCursor(0,0);
    lcd.print("Time to Work...");
    state = 1;
  }
}

void pomodoroIsUp( ) {
  lcd.setCursor(0,0);
  lcd.print("POMODORO!!!    ");
}

void loop() {    
  int buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {     
    togglePomodoro();
  } 

  if( state == 1 )
    t.update();
}

void digitalClockDisplay() {
  lcd.setCursor(0,1);
  lcd.print(hour());
  printDigits(minute());
  printDigits(second());
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  lcd.print(":");
  if(digits < 10)
    lcd.print('0');
  lcd.print(digits);
}
