/*
  FUNCTIONALITY/SCOPE 
- Take user input for time
- Count down until button is hit to switch to black/white
- Tell the user via the LCD screen if a time out occurs
- Play noise with buzzer when time out occurs 
*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int buttonPin = 9;    
int buttonPin2 =7;
int buzzerPin = 6;        
  int lastButtonState = LOW;   
  int whiteTime = 0;
  int blackTime = 0;
  double blackLastCheck = millis();
  bool isWhiteTurn = true;
  bool gameStarted = false; // initializing harware

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0); // ensure it prints in the right spot
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

}
void loop() {
  toggle(); //switches between white button and black button
  count(); //counts down both black and white side of clock
  }
void userTime(){
  if (whiteTime == 0) { //set time for both players
 	 Serial.println("Type time in seconds");
    delay(100);
  		if (Serial.available() > 0) {
          	delay(100);
   			whiteTime = Serial.read();
          	blackTime = whiteTime;
          	gameStarted = true;
        }
  }
}
void toggle(){ //toggles between white and black
   int buttonState = digitalRead(buttonPin);
   int buttonState2 = digitalRead(buttonPin2);
  if (buttonState == HIGH) {
    isWhiteTurn = false;}
  if (buttonState2 == HIGH) {
    isWhiteTurn = true;}
}
void count() {
  userTime();
  	if (isWhiteTurn == true){//sets turn to white
  		long countdowntime_seconds = whiteTime - (millis() / 1000);
   			if (countdowntime_seconds >= 0) {
   				 long countdown_hour = countdowntime_seconds / 3600;
                  long countdown_minute = ((countdowntime_seconds / 60)%60);
                  long countdown_sec = countdowntime_seconds % 60;
                  lcd.setCursor(4, 1);
                  lcd.print("W:");
                        if (countdown_hour < 10) {
                          lcd.print("0"); //code referenced from https://mechatrofice.com/arduino/arduino-countdown-lcd-display-in-hhmmss-format
                        }// does the math to put the user input into hours/minutes seconds.
                        lcd.print(countdown_hour);
                        lcd.print(":");
                        if (countdown_minute < 10) {
                          lcd.print("0");
                        }
              lcd.print(countdown_minute);
              lcd.print(":");
              if (countdown_sec < 10) {
                lcd.print("0");
              }
             lcd.print(countdown_sec);
             if (gameStarted == true && whiteTime ==0) {
               gameOverSequence();}
             whiteTime = whiteTime;
         }
        }
  }
  if (isWhiteTurn == false){ // sets turn to black
    gameOverSequence();
   long countdowntime_seconds = blackTime - (millis() / 1000);
     if (countdowntime_seconds >= 0) {
      long countdown_hour = countdowntime_seconds / 3600;
      long countdown_minute = ((countdowntime_seconds / 60)%60);
      long countdown_sec = countdowntime_seconds % 60;
      lcd.setCursor(4, 0);
       lcd.print("B:");
        if (countdown_hour < 10) {
          lcd.print("0");
        }
        lcd.print(countdown_hour);
        lcd.print(":");
        if (countdown_minute < 10) {
          lcd.print("0");
        }
        lcd.print(countdown_minute);
        lcd.print(":");
        if (countdown_sec < 10) {
          lcd.print("0");
        }
         if (gameStarted == true) {
           gameOverSequence();}
         lcd.print(countdown_sec);
         blackTime = blackTime;
       }
    }
}
void gameOverSequence(){ // declares winner/plays buzzer
  lcd.clear();
  if (isWhiteTurn == false){
    lcd.print("WHITE WINS");}
  if (isWhiteTurn == true){
    lcd.print("BLACK WINS");}
  tone(buzzerPin, 1000); 
  delay(1000);        
  noTone(buzzerPin);    
  delay(1000);        
}
    