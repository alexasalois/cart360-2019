int ledPin = 1;

// sensors
int KEY = 2;
int KEYTWO = 3;
int SOUNDKEY = 5;

// initial state
int moodPoints = 10;

// colour LEDs
int redPin = 10;
int greenPin = 9;
int bluePin = 8;

// game state
boolean touchState = false;

// setting up timer
unsigned int timer = 0;

//
 
void setup(){
  Serial.begin(9600);

// just to check if sensors work
  pinMode(ledPin, OUTPUT);

// sensors 
  pinMode(KEY, INPUT);
  pinMode(KEYTWO, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(SOUNDKEY, INPUT);

// colour leds
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 
}

// add mood point for petting cat
  void moodPointControl() {
    ++moodPoints;
  }

  void moodPointControlNegative() {
    --moodPoints;
  }

// LOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOP 
void loop(){
   
 // check number of points and follow info
 Serial.println(moodPoints);
 
  // "space out" the state of the timer, so when you pet it it doesn't go up like crazy
  if (millis() - timer > 1000){
    touchState =false;
  }

  // if the plushie is not getting pet every 10 seconds, lose a point, then restart timer
  if (millis() - timer > 10000 && touchState == false && moodPoints > 1) {
    delay(100);
    timer = millis();
    moodPoints = moodPoints -1;     
   }

  // every 10 seconds in general, reset timer
  if(millis() - timer > 10000){
    //Serial.println();
    timer = millis();
    delay(100);
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// if you give him enough attention, becomes happy
    if (moodPoints > 15) {
      happyPlushie();
    }

    // if he's neutral, remain blue
    else if (moodPoints < 16 && moodPoints > 5) {
      neutralPlushie();
    }

    // if no attention, becomes angry
    else if (moodPoints < 6) {
      angryPlushie();
    }

    else if (moodPoints = 1) {
      gameOver();
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////

// set up the colours of the LED
  void changeColour(int red, int green, int blue) {
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);  
  }

// setting up the game over state
  void gameOver() {
    digitalWrite(ledPin, LOW);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////

// 
  void happyPlushie(){
    changeColour(0,255,0); 
    // what happens when you touch the sensor (pet the cat), if he HASNT been pet "recently" (too close to previous time)
   if (digitalRead(KEY)==HIGH && touchState==false) { 
     timer = millis();
     digitalWrite(ledPin, HIGH);
     touchState = true;
     moodPointControl();
     delay(200);
    } 
   else {
     digitalWrite(ledPin, LOW);
    }

   // CAPACITIVE SENSOR #2
   // what happens when you touch the sensor (pet the cat), if he HASNT been pet "recently" (too close to previous time)
   if (digitalRead(KEYTWO)==HIGH && touchState==false) { 
     timer = millis();
     digitalWrite(ledPin, HIGH);
     touchState = true;
     moodPointControl();
     delay(200);
    } 
   else {
     digitalWrite(ledPin, LOW);
    }
  }

  void neutralPlushie(){
    changeColour (0,0,255);
    // what happens when you touch the sensor (pet the cat), if he HASNT been pet "recently" (too close to previous time)
   if (digitalRead(KEY)==HIGH && touchState==false) { 
     timer = millis();
     digitalWrite(ledPin, HIGH);
     touchState = true;
     moodPointControl();
     delay(200);
    } 
   else {
     digitalWrite(ledPin, LOW);
    }

   // CAPACITIVE SENSOR #2
   // what happens when you touch the sensor (pet the cat), if he HASNT been pet "recently" (too close to previous time)
   if (digitalRead(KEYTWO)==HIGH && touchState==false) { 
     timer = millis();
     digitalWrite(ledPin, HIGH);
     touchState = true;
     moodPointControlNegative();
     delay(200);
    } 
   else {
     digitalWrite(ledPin, LOW);
    }
  }

  void angryPlushie(){
    changeColour (255,0,0);
    // angry, doesn't want to get touched
   if (digitalRead(KEY)==HIGH && touchState==false) { 
     timer = millis();
     digitalWrite(ledPin, HIGH);
     touchState = true;
     moodPointControlNegative();
     delay(200);
    } 
   else {
     digitalWrite(ledPin, LOW);
    }

   // CAPACITIVE SENSOR #2
   // angry, doesn't want to get touched pt.2
   if (digitalRead(KEYTWO)==HIGH && touchState==false) { 
     timer = millis();
     digitalWrite(ledPin, HIGH);
     touchState = true;
     moodPointControlNegative();
     delay(200);
    } 
   else {
     digitalWrite(ledPin, LOW);
    }

   // Sound detector: doesn't want to get touched, needs auditory comfort as well
    int sensorValue = analogRead(SOUNDKEY);
    Serial.println(sensorValue);

   // since the average "quiet" classroom is about 50 value, and peaks to 500 while whispering directly into the mic, estimated 100
   // to be a good threshold for someone talking "normally" to the plushie, w/o necessarily screaming at it
   if (sensorValue > 100) {
     moodPointControl(); 
    }
  }
