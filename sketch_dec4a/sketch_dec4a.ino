// Pin definitions for relays (7 horns connected to these pins)
const int relayPins[] = {2, 3, 4, 5, 6, 7, 8}; // Digital pins for 7 relays

// Melody sequence: {Relay Index, Duration in milliseconds}
const int melody[][2] = {
  {0, 200}, // Horn 1 (short note)
  {1, 200}, // Horn 2 (short note)
  {2, 400}, // Horn 3 (longer note)
  {3, 200}, // Horn 4 (short note)
  {4, 200}, // Horn 5 (short note)
  {5, 400}, // Horn 6 (longer note)
  {6, 200}, // Horn 7 (short note)
  {-1, 300}, // Pause (no relay active)
  {4, 200}, // Horn 5
  {3, 200}, // Horn 4
  {2, 400}, // Horn 3
  {0, 600}, // Horn 1 (emphasized note)
  {-1, 500}, // Pause
  {2, 200}, // Horn 3
  {1, 200}, // Horn 2
  {0, 300}, // Horn 1
  {4, 300}, // Horn 5
  {-1, 300}, // Pause
  {5, 300}, // Horn 6
  {6, 300}, // Horn 7
  {0, 600}, // Horn 1 (final note)
  {-1, 500}, // Pause before repeating
};

// Number of notes in the melody
const int melodyLength = sizeof(melody) / sizeof(melody[0]);

void setup() {
  // Initialize relay pins as OUTPUT and set them to OFF
  for (int i = 0; i < 7; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH); // Relays OFF initially (assuming active LOW)
  }
}

void loop() {
  // Play the melody
  for (int i = 0; i < melodyLength; i++) {
    int relayIndex = melody[i][0];
    int duration = melody[i][1];

    if (relayIndex != -1) {
      // Activate the relay
      digitalWrite(relayPins[relayIndex], LOW); // Relay ON (assuming active LOW)
    }

    delay(duration); // Wait for the note duration

    if (relayIndex != -1) {
      // Deactivate the relay
      digitalWrite(relayPins[relayIndex], HIGH); // Relay OFF
    }
  }

  // Pause before repeating the melody
  delay(2000); // 2-second pause between melody repetitions
}
