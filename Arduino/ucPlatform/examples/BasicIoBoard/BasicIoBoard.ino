/*
   Basic IO Board Demo:
   Demo for the uc
   libraries used:
   LiquidCrystalIO install via Library Manager https://github.com/davetcc/LiquidCrystalIO/
   IOAbstraction installed with LiquidCrystalIO https://github.com/davetcc/IoAbstraction
   TaskManagerIO installed with LiquidCrystalIO https://github.com/davetcc/TaskManagerIO
   SimpleCollections installed with LiquidCrystalIO https://github.com/davetcc/SimpleCollections
   IRRemote install via Library Manager https://github.com/Arduino-IRremote/Arduino-IRremote
*/

#include <IRremote.hpp>
#include <Encoder.h>
#include <LiquidCrystalIO.h>
#include <IoAbstractionWire.h>
#include <Wire.h>
#include "pitches.h"

/* Pin Definitions */
const int IR_RECEIVE_PIN = 2;

const int GREEN_BTN_PIN = 3;
const int YELLOW_BTN_PIN = 4;
const int RED_BTN_PIN = 5;

const int GREEN_LED_PIN = 6;
const int YELLOW_LED_PIN = 7;
const int RED_LED_PIN = 8;

const int ENC_A_PIN = 9;
const int ENC_B_PIN = 10;

const int BUZZER_PIN = 11;

/* Constants */
const long interval = 100;    // interval at which to blink (milliseconds)

LiquidCrystalI2C_RS_EN(lcd, 0x27, false)
Encoder myEnc(ENC_A_PIN, ENC_B_PIN);

/* Variables */
int btnState = 0;
int lastBtnState = -1;

int ledState = 0;             // ledState used to set the LEDs

int potiVal = 0;
int lastPotiVal = -1;

unsigned long irVal;

long encPosition = 0;
long oldEncPosition  = -999;

unsigned long previousMillis = 0;        // will store last time LED was updated

void lcdSetup()
{
  Wire.begin();

  lcd.begin (16, 2);
  lcd.configureBacklightPin(3);
  lcd.backlight();
  lcd.home ();
}

void pinSetup()
{
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
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

void irRcvLoop() 
{
  if (IrReceiver.decode()) {
    irVal = IrReceiver.decodedIRData.decodedRawData;
    Serial.println(irVal, HEX); // Print "old" raw data
    IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
    IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
    lcd.setCursor(0, 1);
    lcd.print("I: ");
    lcd.print((irVal>>16), HEX);
    IrReceiver.resume(); // Enable receiving of the next value
  }
}

void btnLoop() 
{
  if (digitalRead(GREEN_BTN_PIN) == LOW) {
    btnState |= 0x01;
    tone(BUZZER_PIN, NOTE_C5, 125);
  }
  else
    btnState &= ~0x01;
  if (digitalRead(YELLOW_BTN_PIN) == LOW) {
    btnState |= 0x02;
    tone(BUZZER_PIN, NOTE_B4, 125);
  }
  else
    btnState &= ~0x02;
  if (digitalRead(RED_BTN_PIN) == LOW) {
    btnState |= 0x04;
    tone(BUZZER_PIN, NOTE_A4, 125);
  }
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

void potiLoop() 
{
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

void encLoop() 
{
  encPosition = myEnc.read();
  if (encPosition != oldEncPosition) {
    oldEncPosition = encPosition;
    Serial.println(encPosition);
    lcd.setCursor(8, 1);
    lcd.print("E:     ");
    lcd.setCursor(11, 1);
    lcd.print(encPosition, HEX);
  }
}

void setup()
{
  Serial.begin(115200);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver

  pinSetup();
  lcdSetup();
  analogWrite(11,128);
}

void loop() 
{
  ledLoop();
  irRcvLoop();
  btnLoop();
  potiLoop();
  encLoop();
}
