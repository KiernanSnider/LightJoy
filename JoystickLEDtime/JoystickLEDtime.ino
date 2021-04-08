/*Kiernan Snider 4/01/21
This is the second gamemode of LightJoy, an imitation LED game!
In this gamemode, try to imitate the LED directions correctly 25 times as fast as you can!

Function block breakdown:
  setup -     Set all the pinmodes and run the startUp function
  startUp -   Prints serial monitor info, flashes LEDs, resets all state values, and starts the clock.
  loop -      Contains two States: inputState 0 and 1.
                inputState 0 generates a random number between 1 and 4, corresponding to an LED. Gives control to inputState 1.
                inputState 1 continually reads the joystick output and runs the input() function.
  input -     Checks what direction is pushed, then verifies if the LED random number matches. Gives control to scoreCheck or gameOver. 
  scoreCheck- Checks current score every time a correct input happens. Returns control back to inputState 0. Goes to winState 1 if 25 is reached.
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

int stickX = A0; // X
int stickY = A1; // Y
int stick = A2;   //press
bool stickState, inputState = 0, winState = 0;
float x, y;
int r, score; 
float startT, endT, elapsed;

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
  for(int i=0; i<12; i++){Serial.println(" ");}
  Serial.println("~~~~~LightJoy Time Trial v1.8~~~~~");
    blinkLED();
    blinkLED();
    delay(5000);
    
  score=0;
  inputState=0;
  winState = 0;
  elapsed = 0;
  Serial.println("Get to 25 as fast as you can! Press stick in to start!");
  
  stickState = digitalRead(stick);
  while(stickState == 1){
    delay(50);
    stickState = digitalRead(stick);
  }
 
  blinkLED();
  Serial.println("Go!");
  startT = millis();
}

void loop() {
  if(inputState==0){
    delay(150);
    randomSeed(millis());
    r = random(1,5);
    if(r==1){
      digitalWrite(GRN, HIGH);
    }
    else if(r==2){
      digitalWrite(RED, HIGH);
    }
    else if(r==3){
      digitalWrite(YEL, HIGH);
    }
    else if(r==4){
      digitalWrite(BLU, HIGH);
    }
  inputState=1;
  }
  
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
      score++;
      offLED();
      scoreCheck();
      inputState=0;
    }
    else{
      gameOver();
    }
  }
  
  else if(x>=922){
    digitalWrite(RED, HIGH);
    if(r==2){
      score++;
      offLED();
      scoreCheck();
      inputState=0;
    }
    else{
      gameOver();
    }
  }
  
  else if(y<=200){
    digitalWrite(YEL, HIGH);
    if(r==3){
      score++;
      offLED();
      scoreCheck();
      inputState=0;
    }
    else{
      gameOver();
    }
  }
  
  else if(x<=200){
    digitalWrite(BLU, HIGH);
    if(r==4){
      score++;
      offLED();
      scoreCheck();
      inputState=0;
    }
    else{
      gameOver();
    }
  }
}

void scoreCheck(){
  if(score==10){Serial.println("10 in a row!");}
  if(score==25){
    endT = millis();
    elapsed = (endT - startT)/1000.0;
    winState = 1;
    gameOver();
  }
}

void gameOver(){

  if (winState == 0){
    for(int i=0; i<3; i++){
      blinkLED();
    }
    Serial.println(" ");
    Serial.print("You missed at move number ");
    Serial.print(score);
    Serial.print(". ");
  }
  
  if (winState == 1){
    blinkLED();
    for(int i=0; i<3; i++){
      rotLED();
    }
    Serial.println(" ");
    Serial.println("That's 25, time up! Here is your time:");
    delay(2000);
    Serial.print(elapsed, 4);
    Serial.println(" seconds.");
    delay(2000);
    Serial.print("Thanks for playing! ");
  }
  
  Serial.println("Press the stick in to play again!");
  stickState = digitalRead(stick);
  while(stickState == 1){
    delay(50);
    stickState = digitalRead(stick);
  }
  startUp();
}

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
  delay (50);
  digitalWrite(GRN, LOW);
  digitalWrite(RED, HIGH);
  delay (50);
  digitalWrite(RED, LOW);
  digitalWrite(YEL, HIGH);
  delay (50);
  digitalWrite(YEL, LOW);
  digitalWrite(BLU, HIGH);
  delay (50);
  digitalWrite(BLU, LOW);
}

void blinkLED(){
    onLED();
    delay (300);
    offLED();
    delay (100);
}
