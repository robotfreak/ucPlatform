/*
 * Basic IO Board Demo:
 * Demo for the uc
 * libraries used:
 * LiquidCrystalIO install via Library Manager https://github.com/davetcc/LiquidCrystalIO/
 * IOAbstarction installed with LiquidCrystalIO https://github.com/davetcc/IoAbstraction
 * IRRemote install via Library Manager https://github.com/Arduino-IRremote/Arduino-IRremote
 */
 
#include <IRremote.hpp>
#include <LiquidCrystalIO.h>
#include <IoAbstractionWire.h>
#include <Wire.h> 

LiquidCrystalI2C_RS_EN(lcd, 0x27, false)

const int IR_RECEIVE_PIN = 2;

const int GREEN_BTN_PIN = 3;
const int YELLOW_BTN_PIN = 4;
const int RED_BTN_PIN = 5;

int btnState = 0;
int lastBtnState = -1;

const int GREEN_LED_PIN = 6;
const int YELLOW_LED_PIN = 7;
const int RED_LED_PIN = 8;

// Variables will change:
int ledState = 0;             // ledState used to set the LEDs

int potiVal = 0;
int lastPotiVal = -1;

unsigned long irVal;

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 100;           // interval at which to blink (milliseconds)


void setup()
{
  Serial.begin(115200);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver

  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  Wire.begin();
  lcd.begin (16, 2); // Muss in jedem Falle sein um Zeilen/Spalten zu deklarieren
  lcd.configureBacklightPin(3);
  lcd.backlight();
  lcd.home ();
  lcd.print("Hello World");
}


void ledLoop()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    ledState++;

    if (ledState & 0x01) {
      digitalWrite(GREEN_LED_PIN, HIGH);
    }
    else {
      digitalWrite(GREEN_LED_PIN, LOW);
    }
    if (ledState & 0x02) {
      digitalWrite(YELLOW_LED_PIN, HIGH);
    }
    else {
      digitalWrite(YELLOW_LED_PIN, LOW);
    }
    if (ledState & 0x04) {
      digitalWrite(RED_LED_PIN, HIGH);
    }
    else {
      digitalWrite(RED_LED_PIN, LOW);
    }
  }
}

void irRcvLoop() {
  if (IrReceiver.decode()) {
    irVal = IrReceiver.decodedIRData.decodedRawData;
    Serial.println(irVal, HEX); // Print "old" raw data
    IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
    IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
    lcd.setCursor(0, 1);
    lcd.print("IR: ");
    lcd.print(irVal, HEX);
    IrReceiver.resume(); // Enable receiving of the next value
  }

}

void btnLoop() {
  if (digitalRead(GREEN_BTN_PIN) == LOW)
    btnState |= 0x01;
  else
    btnState &= ~0x01;
  if (digitalRead(YELLOW_BTN_PIN) == LOW)
    btnState |= 0x02;
  else
    btnState &= ~0x02;
  if (digitalRead(RED_BTN_PIN) == LOW)
    btnState |= 0x04;
  else
    btnState &= ~0x04;
  if (btnState != lastBtnState) {
    Serial.print("Btn: ");    lcd.setCursor(0, 0);

    Serial.println(btnState);
    lcd.setCursor(8, 0);
    lcd.print("B: ");
    lcd.print(btnState, HEX);
    lastBtnState = btnState;
  }
}

void potiLoop() {
  potiVal = analogRead(A0) / 4;
  if (potiVal != lastPotiVal) {
    Serial.print("Poti: ");
    Serial.println(potiVal, HEX);
    lcd.setCursor(0, 0);
    lcd.print("P:      ");
    lcd.setCursor(3, 0);
    lcd.print(potiVal, HEX);
    lastPotiVal = potiVal;
  }
}

void loop() {

  ledLoop();
  irRcvLoop();
  btnLoop();
  potiLoop();
}
