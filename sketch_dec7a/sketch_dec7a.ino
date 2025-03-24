#define NOTE_C4  261
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440

// Pin Definitions
const int buzzerPin = 9;
const int ledPins[] = {2, 3, 4, 5, 6, 7};
const int NUM_LEDS = 6;
const int melodyButtonPin = 10;  // Button to change melodies
const int hornButtonPin = 11;    // Button to play selected melody

// Predefined Melodies (limited to six notes)
int melody1[] = { NOTE_C4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4 };
int durations1[] = { 256, 297, 247, 204, 160, 141, 167, 146, 146, 176, 146, 121, 91, 137, 85, 130, 129, 119, 147, 132, 149, 114, 115, 132 };

int melody2[] = { NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4 };
int durations2[] = { 300, 300, 300, 300, 300, 300 };

int melody3[] = { NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_F4, NOTE_E4 };
int durations3[] = { 300, 300, 300, 300, 300, 300 };

// Melody selection variables
int currentMelodyIndex = 0;

// Function to play a sequential song
void playSong(int melody[], int durations[], int length) {
  for (int i = 0; i < length; i++) {
    digitalWrite(ledPins[i % NUM_LEDS], HIGH);
    tone(buzzerPin, melody[i], durations[i]);
    delay(durations[i]);
    digitalWrite(ledPins[i % NUM_LEDS], LOW);
    noTone(buzzerPin);
    delay(100);  // Pause between notes
  }
}

void setup() {
  // Initialize buzzer pin
  pinMode(buzzerPin, OUTPUT);
  
  // Initialize LED pins
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  // Initialize button pins
  pinMode(melodyButtonPin, INPUT_PULLUP);
  pinMode(hornButtonPin, INPUT_PULLUP);
}

void loop() {
  // Check melody change button
  if (digitalRead(melodyButtonPin) == LOW) {
    delay(50); // Debounce delay
    currentMelodyIndex = (currentMelodyIndex + 1) % 3; // Cycle through melodies
    while (digitalRead(melodyButtonPin) == LOW); // Wait for button release
  }
  
  // Check play melody button
  if (digitalRead(hornButtonPin) == LOW) {
    delay(50); // Debounce delay
    switch (currentMelodyIndex) {
      case 0:
        playSong(melody1, durations1, sizeof(melody1) / sizeof(melody1[0]));
        break;
      case 1:
        playSong(melody2, durations2, sizeof(melody2) / sizeof(melody2[0]));
        break;
      case 2:
        playSong(melody3, durations3, sizeof(melody3) / sizeof(melody3[0]));
        break;
    }
    while (digitalRead(hornButtonPin) == LOW); // Wait for button release
  }
}
