/****************************************************
 * File         : toddlerBox.ino
 * Description  : Simple program for a toddler to play with...buttons and things. I don't know what it is yet.  Let's see.
 * Author       : Rowland Marshall
 * 
 * Versions     :
 *    0.01a | 2022-01-06 16:22:19 - piano branch - ref https://learn.sparkfun.com/tutorials/sik-keyboard-instrument/all
 *    0.01  | 2022-01-06 14:49:26 - initial file
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

// Constants
const int SENSOR_PIN = 0;   // Analog input pin for soft pot
const int BUZZER_PIN = 9;   // PWM digital output pin for buzzer
const int DURATION = 10;    // Time (ms) to play a note

void setup()  
{
  // init LCD to 2 lines of 16 char and clear
  lcd.begin(16, 2);
  lcd.clear();

  lcd.print("tddlrBx v0.01a");

   // Create a new characters:
  lcd.createChar(0, Heart);
  lcd.createChar(1, EmptyHeart);

  // Set the buzzer pin as an output
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop()
{
    /* 2022-01-06 16:30:52 commenting out to test original piano file
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
    */
  int sensorValue;
  char note = 0;
  int freq;

  // Read the value (0 - 1023) from the ADC
  sensorValue = analogRead(SENSOR_PIN);

  // Map the key pressed to a note
  note = findNote(sensorValue);

  // If it's a note, play it!
  if ( note != 0 ) {
    freq = getFrequency(note);
    tone(BUZZER_PIN, freq, DURATION);
    delay(DURATION);
  }
}

// Given an ADC value (0 - 1023), map it to a note
char findNote(int val)
{

  // Return the note based on the key pressed
  if ( (val > 10) && (val <= 160) )
  {
    return 'c';
  }
  if ( (val > 160) && (val <= 250) )
  {
    return 'd';
  }
  if ( (val > 250) && (val <= 350) )
  {
    return 'e';
  }
  if ( (val > 350) && (val <= 450) )
  {
    return 'f';
  }
  if ( (val > 450) && (val <= 560) )
  {
    return 'g';
  }
  if ( (val > 560) && (val <= 690) )
  {
    return 'a';
  }
  if ( (val > 690) && (val <= 850) )
  {
    return 'b';
  }
  if ( (val > 850) && (val <= 1023) )
  {
    return 'C';
  }

  // Return 0 to show that no key was pressed
  return 0;
}

// Translate a note (a, b, c, d, e, f, g) to its frequency
int getFrequency(char note) 
{
  int i;
  const int numNotes = 8;  // number of notes we're storing

  // Arrays containing our notes and frequencies
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};

  // Step though the notes
  for (i = 0; i < numNotes; i++)  // Step through the notes
  {

    // If it matches a note in our list, return the frequency
    if (names[i] == note)
    {
      return(frequencies[i]);
    }
  }

  // If we looked through everything and didn't find a note,
  // return 0, as we still need to return something.
  return(0);
}
