#include <ESP32Servo.h>
#include <Keypad.h>

const int PASSWORD_LENGTH = 4;

const char USER_A_PASSWORD[PASSWORD_LENGTH + 1] = "A123";
const char USER_B_PASSWORD[PASSWORD_LENGTH + 1] = "B456";
const char USER_C_PASSWORD[PASSWORD_LENGTH + 1] = "C789";

Servo lockServo;
const int SERVO_PIN = 15;

// Keypad
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {13, 12, 14 ,27};
byte colPins[COLS] = {26, 25, 33, 32}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int position = 0;
bool userIdentified = false;
const char* currentPassword = nullptr;

const char* getUserPassword(char firstChar) {
  switch (firstChar) {
    case 'A': return USER_A_PASSWORD;
    case 'B': return USER_B_PASSWORD;
    case 'C': return USER_C_PASSWORD;
    default:  return nullptr;
  }
}

void lock(bool locked) {
  lockServo.write(locked ? 0 : 90);
  Serial.println(locked ? "Locked" : "Unlocked");
}

void setup() {
  Serial.begin(9600);
  lockServo.attach(SERVO_PIN);
  lock(true);
}

void loop() {
  char key = keypad.getKey();
  if (!key) return;

  Serial.print("Key: ");
  Serial.println(key);

  // Reset condition
  if (key == '*' || key == '#') {
    position = 0;
    userIdentified = false;
    lock(true);
    Serial.println("Reset by special key");
    return;
  }

  if (!userIdentified) {
    currentPassword = getUserPassword(key);
    if (currentPassword) {
      userIdentified = true;
      position = 1; // Start checking from second character
      Serial.println("User identified. Enter rest of password:");
    } else {
      Serial.println("Unknown user. Try again.");
      position = 0;
    }
    return;
  }

  if (key == currentPassword[position]) {
    position++;
    if (position == PASSWORD_LENGTH) {
      lock(false);
      Serial.println("Access granted. Door unlocked.");
      position = 0;
      userIdentified = false;
    }
  } else {
    Serial.println("Wrong key. Resetting...");
    position = 0;
    userIdentified = false;
  }
}
