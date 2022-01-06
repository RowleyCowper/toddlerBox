/****************************************************
 * File         : toddlerBox.ino
 * Description  : Simple program for a toddler to play with...buttons and things. I don't know what it is yet.  Let's see.
 * Author       : Rowland Marshall
 * 
 * Versions     :
 *    0.01 | 2022-01-06 14:49:26 - initial file
 ****************************************************/

// Load the LiquidCrystal library, which will give us commands to interface to the LCD:
#include <LiquidCrystal.h>

// Initialize the library with the pins we're using. See http://arduino.cc/en/Reference/LiquidCrystal
LiquidCrystal lcd(12,11,5,4,3,2);

// Make custom characters:
byte Heart[] = { // Byte 0
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

byte EmptyHeart[] = { // Byte 1
  B00000,
  B01010,
  B10101,
  B10001,
  B01010,
  B00100,
  B00000,
  B00000
};

void setup()
{
  // init LCD to 2 lines of 16 char and clear
  lcd.begin(16, 2);
  lcd.clear();

  lcd.print("toddlerBox v0.01");

   // Create a new characters:
  lcd.createChar(0, Heart);
  lcd.createChar(1, EmptyHeart);
}

void loop()
{
    // Flashing heart to start as "Hello World"
    lcd.setCursor(15,1);
    lcd.write(byte(0)); // print 
    
    // delay 1000ms = 1sec 
    delay(1000);

    // Flashing heart to start as "Hello World"
    lcd.setCursor(15,1);
    lcd.write(byte(1)); // print 
    
    // delay 1000ms = 1sec 
    delay(1000);
}