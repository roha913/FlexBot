
#include <Arduino.h>
#include <stdbool.h>
#define F_CPU 20000000L


void control(bool A, bool B, int act){//control motors
  int true_act = ((PIND & (1 << PD5)) > 0);//to read the IR sensor. 1 if positive, 0 otherwise
  if((act == 2) || (true_act == act)){
    if(A){
      PORTD |= (1 << PD2);//turn motor on
    }else{
      PORTD &= ~(1 << PD2);//turn motor off
    }
    if(B){
      PORTD |= (1 << PD3);//turn motor on
    }else{
      PORTD &= ~(1 << PD3);//turn motor off
    }

    delay(5000);
  }else{//if not activated, stop the motors
    PORTD &= ~(1 << PD2);//turn motor off
    PORTD &= ~(1 << PD3);//turn motor off
    delay(5000);
  }
}


//1 is output, 0 is input
//DATASHEET: https://docs.arduino.cc/resources/datasheets/A000005-datasheet.pdf
void setup(){

  //pinModes
  DDRD |= ((1 << PD2) | (1 << PD3));//mask for D2, D3 being output
  DDRD &= ~(1 << PD5);//mask for D5 being input
  DDRD |= (1 << PD6); DDRD |= (1 << PD7); DDRB |= (1 << PB0); //mask for D6, D7, D8 being output. We will use D6 as ground for the motor driver, and 
  //D7 and D8 for the inputs to the motor driver(since we don't control motor direction in the code, we can just set these to low).
  PORTD &= ~(1 << PD6); PORTD &= ~(1 << PD7); PORTB &= ~(1 << PB0);

  char* code = "2ab";
  int L = 3;//number of characters in code
  int activation = -1;//if activation = 2, then do it regardless of the IR sensor. If 0 or 1, do it when the IR sensor matches
  bool motorA = false; bool motorB = false; 
  //code processing
  for(int i = 0; i < L; i++){
    switch(*(code + i)){
      case 'a':
        motorA = true;
        break;
      case 'b':
        motorB = true;
        break;
      case '2':
        if(activation != -1){
          control(motorA, motorB, activation);
        }
        activation = 2; 
        motorA = false; motorB = false;
        break;
      case '1':
        if(activation != -1){
          control(motorA, motorB, activation);
        }
        activation = 1; 
        motorA = false; motorB = false;
        break;
      case '0':
        if(activation != -1){
          control(motorA, motorB, activation);
        }
        activation = 0; 
        motorA = false; motorB = false;
        break;
    }
  }
  if(activation != -1)
  {
    control(motorA, motorB, activation);
  }
  activation = -1; 
  motorA = false; motorB = false; 
}


void loop(){
  setup(); //for debugging purposes
}

