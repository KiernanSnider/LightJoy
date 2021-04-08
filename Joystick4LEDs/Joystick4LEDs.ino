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
}

void loop() {
  x = analogRead(stickX);
  y = analogRead(stickY);
  
  Serial.print("X: "); 
  Serial.print(x, 4); 
  Serial.print(" | Y: ");
  Serial.println(y, 4);

  input();

  delay (50);
  digitalWrite(GRN, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(BLU, LOW);
  digitalWrite(YEL, LOW);
}

void input(){
  if(x>=922){
    digitalWrite(RED, HIGH);
  }

  else if(x<=200){
    digitalWrite(BLU, HIGH);
  }

  else if(y>=922){
    digitalWrite(GRN, HIGH);
  }


  else if(y<=200){
    digitalWrite(YEL, HIGH);
  }
}
