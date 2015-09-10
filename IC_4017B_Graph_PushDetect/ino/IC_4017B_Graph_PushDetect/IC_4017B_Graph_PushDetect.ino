/*
 * Simple LED Bar graph control using a 4017 counter and a pushbutton
 * The 4017 is used to save pins on the arduino.
 * written by Fabian Moro´n Zirfas
 * based on work by Leonel Machava
 * http://codentronix.com
 * http://codentronix.com/2011/06/05/arduino-led-bar-graph-driven-by-a-4017-counter/
 * http://codentronix.com/2011/06/05/arduino-led-bar-graph-with-a-4017-counter-and-potentiometer/
 * This code is release under the "MIT License" available at
 * http://www.opensource.org/licenses/mit-license.php
 *
 * and the Arduino Button Example 
 * http://arduino.cc/en/Tutorial/Button
 * created 2005
 * by DojoDave <http://www.0j0.org>
 * modified 30 Aug 2011
 * by Tom Igoe
 * and the ButtonStageChange tutorial
 *  also by Tom Igoe
 * http://arduino.cc/en/Tutorial/ButtonStateChange
 *
 * CD4017B Datasheet
 * http://www.ti.com/lit/ds/symlink/cd4017b.pdf
 *
 * Pin Functions CD4017B
 * 
 * PIN 16 - V DC
 * PIN 15 - RESET
 * PIN 14 - CLOCK
 * PIN 13 - CLOCK INHIBIT (STOP COUNTING) not used need to be GND
 * PIN 12 - CARRY OUT (INDICATE DECIMAL) not used need to be GND
 * PIN 11 - 9
 * PIN 10 - 4
 * PIN 09 - 8
 * PIN 08 - GND
 * PIN 07 - 3
 * PIN 06 - 7
 * PIN 05 - 6
 * PIN 04 - 2
 * PIN 03 - 0
 * PIN 02 - 1
 * PIN 01 - 5
 */
int clockPin = 2; // this pulses the clock
int buttonPin = 8; // this is for the pushbutton
int buttonState = 0;// variable for reading the pushbutton status
int counter = 0;
int lastButtonState = 0;
int resetpin = 3;

void setup() {
Serial.begin(9600);
  pinMode(clockPin,OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(resetpin, OUTPUT);
  reset();
}

void loop() {
  /**
  * Read the state of the button
  */
  int barvalue = counter % 10;
  for(int i = 0; i < barvalue;i++){
    clock();
  }
  reset();
  
  buttonState = digitalRead(buttonPin);
  
  if(buttonState != lastButtonState){
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
    if (buttonState == HIGH) {     

      digitalWrite(clockPin,HIGH);
      counter++;
      Serial.println("on");
      Serial.print("number of button pushes:  ");
      Serial.println(counter);

    } else {
     // button is not pressed
      Serial.println("off");     
    digitalWrite(clockPin,LOW);
    }
  }
  lastButtonState = buttonState;
}

/*
 * Sends a clock pulse to the counter making it advance.
 */
void clock() {
  digitalWrite(clockPin,HIGH);
  delay(1);
  digitalWrite(clockPin,LOW);
}
 
 
/*
 * Resets the counter making it start counting from zero.
 */
void reset() {
  digitalWrite(resetpin,HIGH);
  delay(1);
  digitalWrite(resetpin,LOW);
}

