#include <LiquidCrystal.h>

// Initialize LCD display
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

// Pin assignments
const int led1Pin = 5;  // LED 1 connected to digital pin 5
const int led2Pin = 6;  // LED 2 connected to digital pin 6

// Timing variables
unsigned long previousMillis = 0;  // Stores the last time LEDs were updated
unsigned long flashMillis = 0;     // Stores the time for flashing LEDs
const long interval = 500;         // Interval at which to blink (milliseconds)
const long flashInterval = 200;    // Interval for flashing (milliseconds)

// LED default states
bool led1State = LOW;             // LED 1 state (on or off)
bool led2State = HIGH; // LED 2 state (on or off)

// Counters and control variables
bool isFlashing = false;
int alternateCount = 0;  // Counts how many times LEDs have alternated



void setup() {
  // Initialize the LED pins as outputs
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  
  // Set LEDs off to start
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);

  // Initialize the LCD display
  lcd.begin(16, 2);
  lcd.print("Happy Halloween!");
}


void loop() {
  // Get the current time
  unsigned long currentMillis = millis();
  
  // Check if we are in flashing mode
  if (isFlashing) {
    flashLEDs(led1Pin, led2Pin, currentMillis);
  } 
  else {
    // Regular LED alternation
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      
      // Toggle LEDs
      toggleLED(led1Pin, led1State, currentMillis);
      toggleLED(led2Pin, led2State, currentMillis);
      
      // Increment the alternate count
      alternateCount++;
      
      if (alternateCount == 40){
        startFlashing();  // Start flashing sequence

        alternateCount = 0;  // Reset the alternate counter        
      }
    }
  }
}

// Function to toggle an LED state
void toggleLED(int ledPin, bool &ledState, unsigned long currentMillis) {
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
  DisplayLCD(currentMillis);
}


// Function to flash LEDs 5 times
void flashLEDs(int led1Pin, int led2Pin, unsigned long currentMillis) {
  if (currentMillis - flashMillis >= flashInterval) {
    flashMillis = currentMillis;
    
    // Toggle the states of both LEDs
    toggleLED(led1Pin, led1State, currentMillis);
    toggleLED(led2Pin, led2State, currentMillis);

  }
}


// Function to start flashing sequence
void startFlashing() {  
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  
  delay(500);

  for (int counter = 0; counter < 10; counter++) {
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, LOW);
    delay(250);
    digitalWrite(led1Pin, HIGH);
    digitalWrite(led2Pin, HIGH);
    delay(250);
  }
  
  delay(1000);

  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);

  delay(250);
}

// Function to scroll "Happy Hallowee!"
void DisplayLCD(unsigned long currentMillis) {
  if (currentMillis - flashMillis >= flashInterval) {
    flashMillis = currentMillis;

    lcd.scrollDisplayLeft();
  } 
}