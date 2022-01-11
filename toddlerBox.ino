/****************************************************
 * File         : toddlerBox.ino
 * Description  : Simple program for a toddler to play with...buttons and things. I don't know what it is yet.  Let's see.
 * Author       : Rowland Marshall
 * 
 * Versions     :
 *    1.00  | 2022-01-11 00:00:32 - First version of the puzzlebox complete.  A simple 'match the colour' game, resulting in flashing lights & a small tune
 *    0.01b | 2022-01-10 15:13:04 - lightquiz branch - building a simple game where a light is presented to the user and they have to push the corresponding coloured button.
 *    0.01a | 2022-01-06 16:22:19 - piano branch - ref https://learn.sparkfun.com/tutorials/sik-keyboard-instrument/all
 *    0.01  | 2022-01-06 14:49:26 - initial file
 ****************************************************/

// Constants
// buzzer song for victory note (song )
const int buzzerPin = 5;    // connect the buzzer to pin 5

//buttons
const int BUTTON_WHITE = 0;
const int BUTTON_RED = 1;
const int BUTTON_YELLOW = 2;
const int BUTTON_GREEN = 3;
const int BUTTON_BLUE = 4;

//button states as an array
int buttonStates[] = {0, 0, 0, 0, 0};

// RGB LED
const int MULTI_RED_PIN = 13;
const int MULTI_GREEN_PIN = 12;
const int MULTI_BLUE_PIN = 11;

// Button LEDs
const int LED_WHITE_PIN = 6;
const int LED_RED_PIN = 7;
const int LED_YELLOW_PIN = 8;
const int LED_GREEN_PIN = 9;
const int LED_BLUE_PIN = 10;

void setup()  
{
  // intialize pins
  pinMode(BUTTON_WHITE, INPUT);
  pinMode(BUTTON_RED, INPUT);
  pinMode(BUTTON_YELLOW, INPUT);
  pinMode(BUTTON_GREEN, INPUT);
  pinMode(BUTTON_BLUE, INPUT);

  pinMode(MULTI_RED_PIN, OUTPUT);
  pinMode(MULTI_GREEN_PIN, OUTPUT);
  pinMode(MULTI_BLUE_PIN, OUTPUT);

  pinMode(LED_WHITE_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_YELLOW_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);

  pinMode(buzzerPin, OUTPUT); //buzzer pin for song

  //randomize the random with the randomness
  randomSeed(analogRead(0));
}

void loop()
{
  // initialise multicolour LED intensity
  int colourIntensity[3] = {0,0,0}; 

  // initialise a game run
  int colourArray[] = {0,0,0,0,0};  // array of colour choices
  bool correctAnswer = false; // flag for a correct selection

  // pick a game colour
  int colourPick = random(0,5);  // pick a random colour (upper bound is exclusive)
  colourArray[colourPick] = 1; // set a bit in the array so we can do easy compares later

  // set the RGB LED to the game colour
  colourSet(colourPick, colourIntensity);
  analogWrite(MULTI_RED_PIN, colourIntensity[0]);
  analogWrite(MULTI_GREEN_PIN, colourIntensity[1]);
  analogWrite(MULTI_BLUE_PIN, colourIntensity[2]);

  // wait for inputs from the user until they give a correct answer
  while (correctAnswer == false) {
    // read in the button states
    buttonStates[BUTTON_WHITE] = 1 - digitalRead(BUTTON_WHITE);
    buttonStates[BUTTON_RED]  = 1 - digitalRead(BUTTON_RED);
    buttonStates[BUTTON_YELLOW]  = 1 - digitalRead(BUTTON_YELLOW);
    buttonStates[BUTTON_GREEN]  = 1 - digitalRead(BUTTON_GREEN);
    buttonStates[BUTTON_BLUE]  = 1 - digitalRead(BUTTON_BLUE);

    // turn on the corresponding LEDs
    digitalWrite(LED_WHITE_PIN, buttonStates[BUTTON_WHITE]);
    digitalWrite(LED_RED_PIN, buttonStates[BUTTON_RED]);
    digitalWrite(LED_YELLOW_PIN, buttonStates[BUTTON_YELLOW]);
    digitalWrite(LED_GREEN_PIN, buttonStates[BUTTON_GREEN]);
    digitalWrite(LED_BLUE_PIN, buttonStates[BUTTON_BLUE]);

    // see if the correct button (colour) was selected.  If yes, celebrate and reset the game
    if (array_cmp(buttonStates, colourArray, sizeof buttonStates / sizeof buttonStates[0], sizeof colourArray / sizeof colourArray[0]))
    {
      winCelebration();  // correct answer - celebrate!
      correctAnswer = true; // force reset of the game
    }
  }
}

/******************************************************************
 * void colourSet(int colour, int (& colourArray) [3] )
 * 
 * A 'quick' (?) way to have an index of colours.  currently using 
 * cases...It would be better with arrays or lookups I guess.  I 
 * kinda also realized just as I'd finished that I could have used 
 * digitalwrites to solve the same problem as I'm using fixed 
 * colours...but eh.
/*****************************************************************/
void colourSet(int colour, int (& colourArray) [3] )
{
  switch (colour) {
    case 0: //white
      colourArray[0] = 255;
      colourArray[1] = 255;
      colourArray[2] = 255;
      break;
    case 1: //red
      colourArray[0] = 255;
      colourArray[1] = 0;
      colourArray[2] = 0;
      break;
    case 2: //yellow
      colourArray[0] = 255;
      colourArray[1] = 255;
      colourArray[2] = 0;
      break;
    case 3: //green
      colourArray[0] = 0;
      colourArray[1] = 255;
      colourArray[2] = 0;
      break;
    case 4: //blue
      colourArray[0] = 0;
      colourArray[1] = 0;
      colourArray[2] = 200;
      break;
    default: //nothing (black)
      colourArray[0] = 0;
      colourArray[1] = 0;
      colourArray[2] = 0;
      break;
  }
}

/******************************************************************
 * boolean array_cmp(int *a, int *b, int len_a, int len_b){
 * 
 * Compare two arrays
 * 
 * Sauce: https://forum.arduino.cc/t/comparing-two-arrays/5211/2
/*****************************************************************/
boolean array_cmp(int *a, int *b, int len_a, int len_b){
      int n;

      // if their lengths are different, return false
      if (len_a != len_b) return false;

      // test each element to be the same. if not, return false
      for (n=0;n<len_a;n++) if (a[n]!=b[n]) return false;

      //ok, if we have not returned yet, they are equal :)
      return true;
}

/******************************************************************
 * void winCelebration()
 * 
 * Plays songs and flashes the lights for a victory dance!
 * 
 * Modified from sauce: https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v33/experiment-11-using-a-piezo-buzzer 
/*****************************************************************/
void winCelebration()
{
  const int songLength = 19;  // sets the number of notes of the song

  // Notes is an array of text characters corresponding to the notes
  // in your song. A space represents a rest (no tone)

  // with thanks to John Towner Williams
  char notes[songLength] = {
    'd', 'd', 'd', 'g', 'D', 'C', 'b', 'a', 'G', 'D', 'C', 'b', 'a', 'G', 'D', 'C', 'b', 'C', 'a'}; 

  // beats[] is an array of values for each note. A "1" represents a quarter-note, 
  // "2" a half-note, and "4" a quarter-note.
  // Don't forget that the rests (spaces) need a length as well.

  int beats[songLength] = {
    1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 1, 1, 3, 3, 1, 1, 1, 3};

  int tempo = 120;  // The tempo is how fast to play the song (beats per second).
  int i, duration; //

  for (i = 0; i < songLength; i++) // for loop is used to index through the arrays
  {
    duration = beats[i] * tempo;  // length of note/rest in ms

    if (notes[i] == ' ')          // is this a rest? 
      delay(duration);            // then pause for a moment
    else                          // otherwise, play the note
    {
      tone(buzzerPin, frequency(notes[i]), duration);
      delay(duration);            // wait for tone to finish
    }
    delay(tempo/10);              // brief pause between notes
  }

  // victory lights!  I'm too lazy to integrate them in parallel with the song
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(LED_WHITE_PIN, HIGH);
    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(LED_YELLOW_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, HIGH);
    digitalWrite(LED_BLUE_PIN, HIGH);
    delay(200);
    digitalWrite(LED_WHITE_PIN, LOW);
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_YELLOW_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_BLUE_PIN, LOW);
    delay(200);
  }
}

/******************************************************************
 * int frequency(char note) 
 * 
 * Get the frequency, Kenneth.
 * 
 * Modified from sauce: https://learn.sparkfun.com/tutorials/sik-experiment-guide-for-arduino---v33/experiment-11-using-a-piezo-buzzer 
/*****************************************************************/
int frequency(char note) 
{
  int i;
  const int numNotes = 12;  // number of notes we're storing
  char names[numNotes] = { 
    'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'D', 'E', 'F', 'G'   };
  int frequencies[numNotes] = {
    262, 294, 330, 349, 392, 440, 494, 523, 587, 659, 698, 784   };

  // Now we'll search through the letters in the array, and if
  // we find it, we'll return the frequency for that note.

  for (i = 0; i < numNotes; i++)  // Step through the notes
  {
    if (names[i] == note)         // Is this the one?
    {
      return(frequencies[i]);     // Yes! Return the frequency and exit function.
    }
  }
  return(0);  // We looked through everything and didn't find it,
  // but we still need to return a value, so return 0.
}