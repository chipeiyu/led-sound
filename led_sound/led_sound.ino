void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

#include <LedControl.h> const int DIN_PIN = 12;
// Data In pin of the LED matrix const int CS_PIN = 11;
// Chip Select pin of the LED matrix const int CLK_PIN = 10; 
// Clock pin of the LED matrix LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);
const int buttonPin = 2; 
const int potPin = A0; 
const int buzzerPin = 9;
int buttonState = 0; 
int lastButtonState = 0; 
int displayIndex = 0; 
const byte A[8] = {B00111100, B01000010, B01000010, B01111110, B01000010, B01000010, B01000010, B01000010}; const byte B[8] = {B01111100, B01000010, B01000010, B01111100, B01000010, B01000010, B01000010, B01111100}; const byte C[8] = {B00111110, B01000000, B01000000, B01000000, B01000000, B01000000, B01000000, B00111110}; 
const byte *letters[] = {A, B, C}; 
void setup() 
{ pinMode(buttonPin, INPUT);
pinMode(potPin, INPUT);
pinMode(buzzerPin, OUTPUT);
lc.shutdown(0, false);
// Wake up the LED matrix lc.setIntensity(0, 8); 
// Set brightness level (0 is min, 15 is max) lc.clearDisplay(0); 
// Clear the display Serial.begin(9600);
} 
void loop(){ 
  buttonState = digitalRead(buttonPin); 
  if (buttonState != lastButtonState) 
  { if (buttonState == HIGH) { displayIndex = (displayIndex + 1) % 3; 
  displayLetter(letters[displayIndex]); 
  } 
  delay(50);
  // Debounce delay } lastButtonState = buttonState; int potValue = analogRead(potPin); playTune(potValue); 
  }
  
  void displayLetter(const byte letter[8])
  { for (int i = 0; i < 8; i++) { lc.setRow(0, i, letter[i]); } }
  void playTune(int potValue) { int frequency = map(potValue, 0, 1023, 100, 1000);
  tone(buzzerPin, frequency, 100); delay(100); 
  noTone(buzzerPin); }
}
