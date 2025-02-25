#include <Arduino.h>

void control(bool A, bool B, bool C, int act){//control motors
  int true_act = digitalRead(5);//to read the IR sensor. 1 if positive, 0 otherwise
  if((act == 2) || (true_act == act)){
    if(A){
      digitalWrite(2, HIGH);//turn motor on
      Serial.print("A");
    }else{
      digitalWrite(2, LOW);//turn motor off
      Serial.print("a");
    }
    if(B){
      digitalWrite(3, HIGH);//turn motor on
      Serial.print("B");
    }else{
      digitalWrite(3, LOW);//turn motor off
      Serial.print("b");
    }
    if(C){
      digitalWrite(4, HIGH);//turn motor on
      Serial.print("C");
    }else{
      digitalWrite(4, LOW);//turn motor off
      Serial.print("c");
    }
    delay(5000);
    Serial.println("");
  }
}


void setup(){
  Serial.begin(57600);
  delay(100);
  Serial.println("Starting setup()");
  //pinModes
  pinMode(2, OUTPUT); pinMode(3, OUTPUT); pinMode(4, OUTPUT);//for D2, D3, D4 being output
  pinMode(5, INPUT);//for D5 being input
  pinMode(6, OUTPUT); pinMode(7, OUTPUT); pinMode(8, OUTPUT);
  digitalWrite(6, LOW); digitalWrite(7, LOW); digitalWrite(8, LOW);

  char* code = "2abc";
  int L = 4;//number of characters in code
  int activation = -1;//if activation = 2, then do it regardless of the IR sensor. If 0 or 1, do it when the IR sensor matches
  bool motorA = false; bool motorB = false; bool motorC = false;
  //code processing
  Serial.println("Processing student code");
  for(int i = 0; i < L; i++){
    Serial.print("Character ");
    Serial.print(" is ");
    Serial.print(" is: ");
    Serial.println(*(code + i));
    switch(*(code + i)){
      case 'a':
        motorA = true;
        break;
      case 'b':
        motorB = true;
        break;
      case 'c':
        motorC = true;
        break;
      case '2':
        if(activation != -1){
          control(motorA, motorB, motorC, activation);
        }
        activation = 2; 
        motorA = false; motorB = false; motorC = false;
        break;
      case '1':
        if(activation != -1){
          control(motorA, motorB, motorC, activation);
        }
        activation = 1; 
        motorA = false; motorB = false; motorC = false;
        break;
      case '0':
        if(activation != -1){
          control(motorA, motorB, motorC, activation);
        }
        activation = 0; 
        motorA = false; motorB = false; motorC = false;
        break;
    }
  }
  if(activation != -1){
    control(motorA, motorB, motorC, activation);
  }
  activation = -1; 
  motorA = false; motorB = false; motorC = false;
}
void loop(){
  setup(); //for debugging purposes
}