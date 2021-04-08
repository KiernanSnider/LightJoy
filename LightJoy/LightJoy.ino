/*Kiernan Snider 4/06/21
This is the complete version of LightJoy, an imitation LED game!
In this game, try to imitate the LED directions correctly! Pick from two gamemodes, endless or time trial!

Function block breakdown:
  setup -     Set all the pinmodes and run the startUp function
  startUp -   Prints serial monitor info, flashes LEDs, resets all state values, and starts the clock.
  loop -      Contains two States: inputState 0 and 1.
                inputState 0 generates a random number between 1 and 4, corresponding to an LED. Gives control to inputState 1.
                inputState 1 continually reads the joystick output and runs the input() function.
  input -     Checks what direction is pushed, then verifies if the LED random number matches. Gives control to scoreCheck or gameOver. 
  scoreCheck- Checks current score every time a correct input happens. Returns control back to inputState 0. Goes to winState 1 if 25 is reached and in time trial mode.
  gameOver -  Contains two States: winState 0 and 1.
                winState 0 happens automatically if an incorrect input happens. Tells current move and resets with startUp.
                winState 1 happens when score 25 is reached. Stops clock and computes your time. Resets with startUP.
  offLED -    sets all LEDs low
  onLED -     sets all LEDs high
  rotLED -    animates LEDs to spin around once very quickly
  blinkLED -  easy blinking function for startUp and gameOver
*/

#define RED 3
#define YEL 4
#define BLU 5
#define GRN 6

int   stickX = A0, stickY = A1, stick = A2;  // X, Y, press
bool  stickState, inputState = 0, winState = 0, gameState = 0;
int   r, score; 
float x, y, startT, endT, elapsed;
float HS = 14.47;

void setup() {
  pinMode(stickX, INPUT);
  pinMode(stickY, INPUT);
  pinMode(stick, INPUT_PULLUP); //internal pull up resistor active
  
  pinMode(RED, OUTPUT);
  pinMode(YEL, OUTPUT);
  pinMode(BLU, OUTPUT);
  pinMode(GRN, OUTPUT);
  
  Serial.begin(9600);  //serial monitor output
  
  startUp();
}

void startUp(){
//game variable reset
  score=0;
  inputState=0;
  gameState=0;
  winState = 0;
  elapsed = 0;
  
// Game startup clear screen and text prompts
  for(int i=0; i<16; i++){Serial.println(" ");}
  Serial.println("~~~~~~~LightJoy Complete v1.0~~~~~~~~");
  for(int i=0; i<3; i++){blinkLED();}
  Serial.println("      Please choose a gamemode:      ");
  Serial.println("< LEFT for Endless Mode");
  Serial.println("> RIGHT for Time Trial Mode");

// Initializing then reading joystick direction
  x = analogRead(stickX);
  y = analogRead(stickY);
  while(x > 450 && x < 600 ){
    delay(50);
    x = analogRead(stickX);
    y = analogRead(stickY);
  }

// Direction directions (hah)
  if(x > 600 ){
    gameState = 1;
    Serial.println("Get to 25 as fast as you can and beat the high score!");
  }
  else{
    Serial.println("Play for as long as you want...");
    Serial.println("as long as you don't have work to do!");
  }
  x = analogRead(stickX);
  y = analogRead(stickY);
  delay(2000);

// Game startup sequence
  for(int i=0; i<3; i++){rotLED();}
  blinkLED();
  Serial.println("               START!");
  Serial.println(" ");
  startT = millis();
}

void loop() {
// Random LED generator changes random seed every cycle
  if(inputState==0){
    delay(150);
    randomSeed(millis());
    r = random(1,5);
    
    if     (r==1){digitalWrite(GRN, HIGH);}
    else if(r==2){digitalWrite(RED, HIGH);}
    else if(r==3){digitalWrite(YEL, HIGH);}
    else if(r==4){digitalWrite(BLU, HIGH);}
    inputState=1;
  }

// Continual input check loop
  if(inputState==1){
    x = analogRead(stickX);
    y = analogRead(stickY);
    input();
    delay (100);
  }
}

void input(){
  if(y>=922){
    digitalWrite(GRN, HIGH);
    if(r==1){
      score++; offLED();scoreCheck();inputState=0;
    }
    else{gameOver();}
  }
  
  else if(x>=922){
    digitalWrite(RED, HIGH);
    if(r==2){
      score++; offLED();scoreCheck();inputState=0;
    }
    else{gameOver();}
  }
  
  else if(y<=200){
    digitalWrite(YEL, HIGH);
    if(r==3){
      score++; offLED();scoreCheck();inputState=0;
    }
    else{gameOver();}
  }
  
  else if(x<=200){
    digitalWrite(BLU, HIGH);
    if(r==4){
      score++; offLED();scoreCheck();inputState=0;
    }
    else{gameOver();}
  }
}

void scoreCheck(){
  if(score==10){Serial.println("That's 10, do it again!");}
  if (score==25 && gameState == 1){
    endT = millis();
    elapsed = (endT - startT)/1000.0;
    winState = 1;
    gameOver();
  }
  if(score==25 && gameState == 0){Serial.println("25, feelin alive!");}
  if(score==50){Serial.println("You're at 50, that's pretty nifty!");}
  if(score==100){Serial.println("A hund'erd, I was beginning to wonder!");}
  if(score==200){Serial.println("You should get back to work now.");}
}

void gameOver(){
// YOU LOST!
  if (winState == 0){
    for(int i=0; i<3; i++){blinkLED();}
    
    Serial.println(" ");
    Serial.print("You missed at move number ");
    Serial.print(score);
    Serial.print(". ");
  }

// YOU WON!
  if (winState == 1){
  // LED Win Animation 
    blinkLED();
    for(int i=0; i<3; i++){rotLED();}

  //Time calculation and prompt
    Serial.println(" ");
    Serial.println("That's 25, time up! Here is your time:");
    delay(2000);
    Serial.print(elapsed, 4);
    Serial.println(" seconds.");

  //High score check
    if (elapsed <= 13.07){Serial.println("You actually beat my personal best!! You may update the code with your time.");}
    else if (elapsed <= HS){Serial.println("A HIGH SCORE! Congratulations!");}
    else{Serial.print("Thanks for playing! ");}
  }

//Input to play again
  Serial.println("Press the stick in to play again!");
  stickState = digitalRead(stick);
  while(stickState == 1){
    delay(50);
    stickState = digitalRead(stick);
  }
  startUp();
}

// All f'ns below are types of LED animations
void offLED(){
  digitalWrite(GRN, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(BLU, LOW);
  digitalWrite(YEL, LOW);
}

void onLED(){
  digitalWrite(GRN, HIGH);
  digitalWrite(RED, HIGH);
  digitalWrite(BLU, HIGH);
  digitalWrite(YEL, HIGH);
}

void rotLED(){
  digitalWrite(GRN, HIGH);
  delay (75);
  digitalWrite(GRN, LOW);
  digitalWrite(RED, HIGH);
  delay (75);
  digitalWrite(RED, LOW);
  digitalWrite(YEL, HIGH);
  delay (75);
  digitalWrite(YEL, LOW);
  digitalWrite(BLU, HIGH);
  delay (75);
  digitalWrite(BLU, LOW);
}

void blinkLED(){
    onLED();
    delay (300);
    offLED();
    delay (100);
}
