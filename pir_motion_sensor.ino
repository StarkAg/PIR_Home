/*
 * PIR Motion Sensor with Stadium Wave LED Effect
 * 
 * This sketch detects motion using a PIR sensor (HC-SR501) and
 * creates a stadium wave effect with 3 LEDs that turn on sequentially
 * and then turn off with a visible delay.
 * 
 * Hardware Connections:
 * - PIR VCC -> 5V
 * - PIR GND -> GND
 * - PIR OUT -> Digital Pin 2
 * - LED 1 + -> Digital Pin 8 (through 220Ω resistor)
 * - LED 2 + -> Digital Pin 9 (through 220Ω resistor)
 * - LED 3 + -> Digital Pin 10 (through 220Ω resistor)
 * - All LED - -> GND
 */

// Pin definitions
const int PIR_PIN = 2;           // PIR sensor output pin
const int LED_PINS[] = {8, 9, 10}; // LED pins for stadium wave
const int NUM_LEDS = 3;          // Number of LEDs

// Timing configuration
const unsigned long WAVE_ON_DELAY = 200;    // Delay between each LED turning on (ms)
const unsigned long ALL_ON_DURATION = 3000; // Time all LEDs stay on (ms)
const unsigned long WAVE_OFF_DELAY = 300;   // Delay between each LED turning off (ms)

// State machine states
enum WaveState {
  IDLE,           // Waiting for motion
  WAVE_ON,        // LEDs turning on sequentially
  ALL_ON,         // All LEDs on
  WAVE_OFF        // LEDs turning off sequentially
};

// State variables
WaveState currentState = IDLE;
unsigned long stateStartTime = 0;
int currentLedIndex = 0;
bool motionDetected = false;
bool lastPirState = LOW;

// Function forward declarations
void startWaveOn();
void handleWaveOn();
void handleAllOn();
void handleWaveOff();

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  Serial.println("PIR Motion Sensor with Stadium Wave - Initialized");
  
  // Configure pins
  pinMode(PIR_PIN, INPUT);
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);  // Initialize all LEDs to OFF
  }
  
  // Wait for PIR sensor to stabilize (HC-SR501 needs ~30-60 seconds)
  Serial.println("Calibrating PIR sensor... Please wait 30-60 seconds.");
  delay(30000);  // Wait 30 seconds for initial calibration
  Serial.println("Calibration complete. Ready to detect motion!");
  Serial.println("Wave effect: LEDs will turn on in sequence (8->9->10)");
  Serial.println("Then turn off in sequence with visible delay.");
}

void loop() {
  // Read PIR sensor state
  int pirValue = digitalRead(PIR_PIN);
  
  // Detect motion (rising edge)
  if (pirValue == HIGH && lastPirState == LOW) {
    motionDetected = true;
    Serial.println("Motion detected! Starting stadium wave...");
    startWaveOn();
  }
  
  lastPirState = pirValue;
  
  // State machine
  switch (currentState) {
    case IDLE:
      // Do nothing, waiting for motion
      break;
      
    case WAVE_ON:
      handleWaveOn();
      break;
      
    case ALL_ON:
      handleAllOn();
      break;
      
    case WAVE_OFF:
      handleWaveOff();
      break;
  }
  
  // Small delay to prevent excessive CPU usage
  delay(10);
}

void startWaveOn() {
  currentState = WAVE_ON;
  stateStartTime = millis();
  currentLedIndex = 0;
  // Turn on first LED immediately
  digitalWrite(LED_PINS[0], HIGH);
  Serial.println("LED 8 ON");
}

void handleWaveOn() {
  unsigned long elapsed = millis() - stateStartTime;
  int expectedLed = elapsed / WAVE_ON_DELAY;
  
  // Turn on next LED if enough time has passed
  if (expectedLed > currentLedIndex && expectedLed < NUM_LEDS) {
    currentLedIndex = expectedLed;
    digitalWrite(LED_PINS[currentLedIndex], HIGH);
    Serial.println("LED " + String(LED_PINS[currentLedIndex]) + " ON");
  }
  
  // Check if all LEDs are on
  if (expectedLed >= NUM_LEDS - 1) {
    // Ensure all LEDs are on
    for (int i = 0; i < NUM_LEDS; i++) {
      digitalWrite(LED_PINS[i], HIGH);
    }
    // Transition to ALL_ON state
    currentState = ALL_ON;
    stateStartTime = millis();
    Serial.println("All LEDs ON - Stadium wave complete!");
  }
}

void handleAllOn() {
  unsigned long elapsed = millis() - stateStartTime;
  
  // After all LEDs have been on for the duration, start turning off
  if (elapsed >= ALL_ON_DURATION) {
    currentState = WAVE_OFF;
    stateStartTime = millis();
    currentLedIndex = 0;
    // Turn off first LED immediately
    digitalWrite(LED_PINS[0], LOW);
    Serial.println("LED 8 OFF - Starting wave off");
  }
}

void handleWaveOff() {
  unsigned long elapsed = millis() - stateStartTime;
  int expectedLed = elapsed / WAVE_OFF_DELAY;
  
  // Turn off next LED if enough time has passed
  if (expectedLed > currentLedIndex && expectedLed < NUM_LEDS) {
    currentLedIndex = expectedLed;
    digitalWrite(LED_PINS[currentLedIndex], LOW);
    Serial.println("LED " + String(LED_PINS[currentLedIndex]) + " OFF");
  }
  
  // Check if all LEDs are off
  if (expectedLed >= NUM_LEDS - 1) {
    // Ensure all LEDs are off
    for (int i = 0; i < NUM_LEDS; i++) {
      digitalWrite(LED_PINS[i], LOW);
    }
    // Transition back to IDLE state
    currentState = IDLE;
    motionDetected = false;
    Serial.println("All LEDs OFF - Ready for next motion detection");
  }
}

