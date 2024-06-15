//Second arduino module works as a Output pod, controlling LEDs and LCDs displaying estimated time.

#include <Wire.h>
#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int led1 = 7;  // EV1 LED1 < 2 meters
const int led2 = 8;  // EV1 LED2 < 1 meter
const int led3 = 9;  // EV2 LED3 < 2 meters
const int led4 = 10;  // EV2 LED4 < 1 meter
const int led5 = A1;  // EV2 LED5 < 1 meter (UL3)

int waitTime1 = 0;
int waitTime2 = 0;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  
  Wire.begin(8); // Join I2C bus with address #8
  Wire.onReceive(receiveEvent); // Register event

  lcd.begin(16, 2);
}

void loop() {
  controlLEDs();
  displayInfo();
  delay(1000);
}

void receiveEvent(int howMany) {
  waitTime1 = Wire.read();
  waitTime2 = Wire.read();
}


// LED is turned on if line is longer than each meter, and only on eLED is turned on at each time.

void controlLEDs() {
  if (waitTime1 > 0) {
    digitalWrite(led1, HIGH);
    if (waitTime1 == 120) {
      digitalWrite(led2, HIGH);
    } else {
      digitalWrite(led2, LOW);
    }
  } else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }

  if (waitTime2 > 0) {
    digitalWrite(led3, HIGH);
    if (waitTime2 >= 45) {
      digitalWrite(led4, HIGH);
    } else {
      digitalWrite(led4, LOW);
    }
    if (waitTime2 >= 90) {
      digitalWrite(led5, HIGH);
    } else {
      digitalWrite(led5, LOW);
    }
  } else {
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }
}


//display for time estimation of EV waiting, and shows optimal EV to ride.
void displayInfo() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("EV1 Wait:");
  lcd.print(waitTime1);
  lcd.print("s");

  lcd.setCursor(0, 1);
  lcd.print("EV2 Wait:");
  lcd.print(waitTime2);
  lcd.print("s");

  if (waitTime1 > 0 && waitTime2 > 0) {
    if (waitTime1 < waitTime2 || (waitTime1 < 100 && waitTime2 < 100)) {
      lcd.setCursor(0, 1);
      lcd.print("Use EV2 for fl 9");
    } else {
      lcd.setCursor(0, 1);
      lcd.print("Use EV1 for fl 9");
    }
  } else if (waitTime1 > 0) {
    lcd.setCursor(0, 1);
    lcd.print("Use EV1 for fl 9");
  } else if (waitTime2 > 0) {
    lcd.setCursor(0, 1);
    lcd.print("Use EV2 for fl 9");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Use ev2 for fl 9");
  }
}