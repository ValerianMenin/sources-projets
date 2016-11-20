#define LED_GREEN 3 //  
#define LED_BLUE 5 //  
#define LED_RED 6 //  
#define POTENTIO 0 //
#define PUSH 2 //

int i =0;
int button = 0;
int selected_led = -1;
int pressCount = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  analogWrite(LED_GREEN, 0); 
  analogWrite(LED_BLUE, 0);
  analogWrite(LED_RED, 0);
  pinMode(POTENTIO, OUTPUT);
  pinMode(PUSH, INPUT);
  Serial.println("Initialisation");
}

// the loop function runs over and over again forever
void loop() {
  // read the state of the pushbutton value:
  button = digitalRead(PUSH);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (button == HIGH) {
    pressCount++;
    delay(300);
  }
  
  if(pressCount%3 == 0){
    selected_led = 3;
  }
  
  if(pressCount%3 == 1){
    selected_led = 5;
  }
  
  if(pressCount%3 == 2){
    selected_led = 6;
  }
    
  
  i = analogRead(POTENTIO);
  analogWrite(selected_led, i / 4);   // turn the LED on (HIGH is the voltage level)


}
