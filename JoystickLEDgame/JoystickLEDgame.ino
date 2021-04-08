//Kiernan Snider 3/31/21
//This program 

#define RED 3
#define YEL 4
#define BLU 5
#define GRN 6

int stickX = A0; // X
int stickY = A1; // Y
int stick = A2;   //press
bool inputState = 0;
float x, y;
int r, score;

void setup() {
  pinMode(stickX, INPUT);
  pinMode(stickY, INPUT);
  pinMode(stick, INPUT);
  digitalWrite(stick, HIGH); //internal pull up resistor active
  
  pinMode(RED, OUTPUT);
  pinMode(YEL, OUTPUT);
  pinMode(BLU, OUTPUT);
  pinMode(GRN, OUTPUT);
  
  Serial.begin(9600);  //serial monitor output
  Serial.println("Lightjoy v1.3 INITIALIZING...");
  onLED();
    delay (100);
  offLED();
    delay(100);
  onLED();
    delay (800);
  offLED();
  Serial.println("Starting now!");
}

void loop() {
  
  if(inputState==1){
    x = analogRead(stickX);
    y = analogRead(stickY);
  
//    Serial.print("X: "); 
//    Serial.print(x, 4); 
//    Serial.print(" | Y: ");
//    Serial.println(y, 4);

    input();
    delay (100);
  }

  while(inputState==0){
    delay(200);
    randomSeed(millis());
    r = random(1,5);
    if(r==1){
      Serial.println("GREEN");
      digitalWrite(GRN, HIGH);
    }
    else if(r==2){
      Serial.println("RED");
      digitalWrite(RED, HIGH);
    }
    else if(r==3){
      Serial.println("YELLOW");
      digitalWrite(YEL, HIGH);
    }
    else if(r==4){
      Serial.println("BLUE");
      digitalWrite(BLU, HIGH);
    }
  inputState=1;
  }
}

void input(){
  if(y>=922){
    digitalWrite(GRN, HIGH);
    if(r==1){
      score++;
      scoreCheck();
      offLED();
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
      scoreCheck();
      offLED();
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
      scoreCheck();
      offLED();
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
      scoreCheck();
      offLED();
      inputState=0;
    }
    else{
      gameOver();
    }
  }
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

void scoreCheck(){
  if(score==10){Serial.println("10 in a row, nice!");}
  if(score==25){Serial.println("That's 25, I commend you!");}
  if(score==50){Serial.println("Holy moly, you're at 50!");}
  if(score==100){Serial.println("100! you're on fire!");}
  if(score==500){Serial.println("That's 500...you might need to get back to work.");}
}

void gameOver(){
  onLED();
    delay (800);
  offLED();
  
  Serial.print("You got ");
  Serial.print(score);
  Serial.println("! Please wait to play again.");
  delay(10000);
  
  score=0;
  for(int i; i<12; i++){Serial.println(" ");}
  Serial.println("Starting in 5 seconds...");
  delay(5000);
  inputState=0;
  Serial.println("Go!");
  
}
