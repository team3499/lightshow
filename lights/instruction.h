#ifndef INSTRUCTION_H
#define INSTRUCTION_H


class Instruction {
  Instruction(){
    // PIN 10
    pinMode(10, INPUT);
    mode = 0;
  }
  ~Instruction();
  
  int step(){
    
    float duration = 0.0;
    
    for(int i = 0; i < 5; i++){
      duration += pulseIn(10, HIGH);
    }
    
    Serial.println(duration);
    
    return mode;
  }
  
private:
  int mode;
};



#endif // #ifndef INSTRUCTION_H
