//******************************************************************* 
//
//      Created for N.E.M.O (NeverLAN Electronic Motion Operative)
//      Written By Zane Durkin
//      For Use on Arduino Due board.
//      created 10/25/2014
//      last edited 9/5/2016
//      
//*******************************************************************

// possible reviews
//
// change Engine stall pins to intrupt pins.
// change Encoder pins to inturrupt pins.


// Direction is 0 or 1 (low or high)
// D = direction  C = current sensing  L = left   R = right  PWM = pulse width modulation(speed) E = Encoder

// Right front will use 24, 26,54,62     26 is pwm    
const int RFD     = 23;   //direction
const int RFS     = 2;    //speed pwm2
const int RFC     = 54;   //engine stall reciver A0
const int RFE     = 25;   //Encoder reader 
// pins: direction, speed, stall, Encoder
//int RF[]= {23, 2, 54, 25};

// Right Back will use 25, 27, 55,63    27 is pwm    
const int RBD     = 27;    //direction
const int RBS     = 3;     //speed pwm3
const int RBC     = 56;    //engine stall reciever A2
const int RBE     = 29;    //Encoder reader 
// pins: direction, speed, stall, Encoder
//int RB[] = {27, 3, 56, 29};

// Left Front will use 32, 34, 56, 64    34 is pwm
const int LFD     = 22;    //direction
const int LFS     = 4;     //speed pwm4
const int LFC     = 55;    //engine stall reciever A1
const int LFE     = 24;    //Encoder reader 
// pins: direction, speed, stall, Encoder
//int LF[] = {22, 4, 55, 24};

// Left Back will use 33, 35, 57, 65    35 is pwm
const int LBD     = 26;    //direction
const int LBS     = 5;     //speed pwm5
const int LBC     = 57;    //engine stall reciever A3
const int LBE     = 28;    //Encoder reader 
// pins: direction, speed, stall, Encoder
//int LB[] = {26, 5, 57, 28};

int done                = 0;     // a variable for the encoders
const int spin          = 5000;  // how long motors should run to spin the robot 90 degrees (like a top)
//const int encoder_count = 2600;  // how many counts the montor should spin to go one foot (2600 is close to 1 foot)
const int encoder_count = 9500;  // how many counts the montor should spin to go one meter (9500 is close to 1 meter)
const int slide_count = 10000;   // how many counts the montor should spin to go one meter while sliding (1000 is close to 1 meter)



void setup() {
  pinMode (RFD, OUTPUT);
  pinMode (RBD, OUTPUT);
  pinMode (LFD, OUTPUT);
  pinMode (LBD, OUTPUT);
  
//  attachInterrupt(RFC, checkFront, HIGH);
//  attachInterrupt(RBC, checkBack, HIGH);
//  attachInterrupt(LFC, checkFront, HIGH);
//  attachInterrupt(LBC, checkBack, HIGH);
  
  pinMode (RFE, INPUT);
  pinMode (RBE, INPUT);
  pinMode (LFE, INPUT);
  pinMode (LBE, INPUT);
  
}

void loop() {
  analogWrite(RFS, 0);
  analogWrite(RBS, 0);
  analogWrite(LFS, 0);
  analogWrite(LBS, 0);
  delay(5000);
  //forward(1, 255);
  //delay(3000);
  //reverse(1, 255);
  //delay(5000);
  spinCCW(1, 255);
  delay(1000);
  //right(1, 255);
  //delay(5000);
  //left(1, 255);
  delay(3000);
  spinCW(1, 255);
  

  
  // write NEMO
//  forward(4,255);
//  delay(500);
//  diagBR(5,255);
//  delay(500);
//  forward(4, 255);
//  delay(1000);
//  //finished with the N
//  right(1, 255);
//  delay(500);
//  //moving over for the E
//  right(2, 255);
//  left(2, 255);
//  delay(500);
//  reverse(2, 255);
//  delay(500);
//  right(1, 255);
//  left(1,255);
//  delay(500);
//  reverse(2, 255);
//  delay(500);
//  right(2, 255);
//  left(2, 255);
//  delay(1000);
//  //done with the E
//  right(3, 255);
//  delay(500);
//  //starting the M
//  forward(4, 255);
//  delay(500);
//  diagBR(5, 255);
//  delay(500);
//  diagFR(5, 255);
//  delay(500);
//  reverse(4, 255);
//  delay(10000);
//  //done with the M
//  right(1, 255);
//  delay(500);
//  //start with the O
//  right(1, 255);
//  diagFR(1, 255);
//  forward(1, 255);
//  diagFL(1, 255);
//  left(1, 255);
//  diagBL(1, 255);
//  reverse(1, 255);
//  diagBR(1, 255);
//  right(1, 255);
//  delay(1000);
//  //done with the O
  
  
  //delay to allow people to pick up the robot, so it doesn't start the loop again.
  delay(5000);
}


//function to walk forward until encoder reaches a certain amount
//64 is the number of counts per shaft-rotation. one rotation is about 1/100 foot 
//should possibly use attachInterrupt(pin, ISR, mode)
//walk is based off front right wheel, use walkLF for other wheels




//int Walk(int count=6400){
//  done = 0;
//  attachInterrupt(RFE, add, HIGH);
//  while(done < count){
//  
//  }
//  detachInterrupt(RFE);
//}
//int WalkLF (int count=6400){
//  done= 0;
//  attachInterrupt(LFE, add,HIGH);
//  while(done < count){
//  
//  }
//  detachInterrupt(LFE);
//}
//void add (){done++;}


//set count equal to default if no variable is given
void walk (int count=encoder_count){
  int done = 0;
  while(done < count){
    //check for a PWM pulse; when on, start timer; when off, return how long the pulse was high; is pulse was on high longer than 10 microsecounds, continue
    if (pulseIn(RFE, HIGH)>10){
      done ++;
    }
  }
}

void walkLF (int count=6400){
  int done = 0;
  while(done < count){
    if (pulseIn(LFE, HIGH)>10){
      done ++;
    }
  }
}

void checkFront(){
  //set all wheels to go backward
  digitalWrite(RFD, LOW);
  digitalWrite(RBD, LOW);
  digitalWrite(LFD, LOW);
  digitalWrite(LBD, LOW);
  //go backward at half speed
  analogWrite(RFS, 127);
  analogWrite(RBS, 127);
  analogWrite(LFS, 127);
  analogWrite(LBS, 127);
  //walk back for half a foot
  walk((int)encoder_count/2);
  //stop wheels
  analogWrite(RFS, 0);
  analogWrite(RBS, 0);
  analogWrite(LFS, 0);
  analogWrite(LBS, 0);
}

void checkBack(){
  //set all wheels to go forward
  digitalWrite(RFD, HIGH);
  digitalWrite(RBD, HIGH);
  digitalWrite(LFD, HIGH);
  digitalWrite(LBD, HIGH);
  //go backward at half speed
  analogWrite(RFS, 127);
  analogWrite(RBS, 127);
  analogWrite(LFS, 127);
  analogWrite(LBS, 127);
  //walk back for half a foot
  delay(500);
  //stop wheels
  analogWrite(RFS, 0);
  analogWrite(RBS, 0);
  analogWrite(LFS, 0);
  analogWrite(LBS, 0);
}

//straight forward
void forward (int distance, int spd){
  //set all wheels to go forward
  digitalWrite(RFD, HIGH);
  digitalWrite(RBD, HIGH);
  digitalWrite(LFD, HIGH);
  digitalWrite(LBD, HIGH);
  //while it still has distance to go and the wheels are not stalled, go forward. 
  while (distance > 0 && (analogRead(RFC) < 511 && analogRead(RBC) < 511 && analogRead(LFC) < 511 && analogRead(LBC) < 511)){    
    //give all wheels speed that was assigned 
    analogWrite(RFS, spd);
    analogWrite(RBS, spd);
    analogWrite(LFS, spd);
    analogWrite(LBS, spd);
    //walk until encoder input reaches 6400
    walk();
    //subtract a foot from the distance
    distance --;
  }
  //turn off the wheels
  analogWrite(RFS, 0);
  analogWrite(RBS, 0);
  analogWrite(LFS, 0);
  analogWrite(LBS, 0);
}

//straight Back
void reverse (int distance, int spd){
  digitalWrite(RFD, LOW);
  digitalWrite(RBD, LOW);
  digitalWrite(LFD, LOW);
  digitalWrite(LBD, LOW);
  //while it still has distance to go and the wheels are not stalled, go backward. 
  while (distance > 0 && (analogRead(RFC) < 511 && analogRead(RBC) < 511 && analogRead(LFC) < 511 && analogRead(LBC) < 511)){
    //give all wheels speed that was assigned
    analogWrite(RFS, spd);
    analogWrite(RBS, spd);
    analogWrite(LFS, spd);
    analogWrite(LBS, spd);
    walk();
    //subtract a foot from the distance
    distance --;
  } 
  //turn off the wheels
  analogWrite(RFS, 0);
  analogWrite(RBS, 0);
  analogWrite(LFS, 0);
  analogWrite(LBS, 0);
}

//moving left 
void left (int distance, int spd){
  digitalWrite(RFD, HIGH);
  digitalWrite(RBD, LOW);
  digitalWrite(LFD, LOW);
  digitalWrite(LBD, HIGH);
  //while it still has distance to go and the wheels are not stalled, do something. 
  while (distance > 0 && (analogRead(RFC) < 511 && analogRead(RBC) < 511 && analogRead(LFC) < 511 && analogRead(LBC) < 511)){
    //give all wheels speed that was assigned
    analogWrite(RFS, spd);
    analogWrite(RBS, spd);
    analogWrite(LFS, spd);
    analogWrite(LBS, spd);
    //delay()should be changed to read encoder output
    walk(slide_count);
    //subtract a foot from the distance
    distance --;
  }
  //turn off the wheels
  analogWrite(RFS, 0);
  analogWrite(RBS, 0);
  analogWrite(LFS, 0);
  analogWrite(LBS, 0);
}

//moving right
void right(int distance, int spd){
  digitalWrite(RFD, LOW);
  digitalWrite(RBD, HIGH);
  digitalWrite(LFD, HIGH);
  digitalWrite(LBD, LOW);
  //while it still has distance to go and the wheels are not stalled, do something. 
  while (distance > 0 && (analogRead(RFC) < 511 && analogRead(RBC) < 511 && analogRead(LFC) < 511 && analogRead(LBC) < 511)){
    //give all wheels speed that was assigned
    analogWrite(RFS, spd);
    analogWrite(RBS, spd);
    analogWrite(LFS, spd);
    analogWrite(LBS, spd);
    //delay()should be changed to read encoder output
    walk(slide_count);
    //subtract a foot from the distance
    distance --;
  }
  //turn off the wheels
  analogWrite(RFS, 0);
  analogWrite(RBS, 0);
  analogWrite(LFS, 0);
  analogWrite(LBS, 0);
}

//spining clockwise
void spinCW (int distance, int spd){
  digitalWrite(RFD, LOW);
  digitalWrite(RBD, LOW);
  digitalWrite(LFD, HIGH);
  digitalWrite(LBD, HIGH);
  //while it still has distance to go and the wheels are not stalled, do something. 
   while (distance > 0 && (analogRead(RFC) < 511 && analogRead(RBC) < 511 && analogRead(LFC) < 511 && analogRead(LBC) < 511)){
    //give all wheels speed that was assigned
    analogWrite(RFS, spd);
    analogWrite(RBS, spd);
    analogWrite(LFS, spd);
    analogWrite(LBS, spd);
    walk(spin);
    //subtract a foot from the distance
    distance --;
  }
  //turn off the wheels
  analogWrite(RFS, 0);
  analogWrite(RBS, 0);
  analogWrite(LFS, 0);
  analogWrite(LBS, 0);
}

//spinning counter-clock wise
void spinCCW(int distance, int spd){
  digitalWrite(RFD, HIGH);
  digitalWrite(RBD, HIGH);
  digitalWrite(LFD, LOW);
  digitalWrite(LBD, LOW);
  //while it still has distance to go and the wheels are not stalled, do something. 
   while (distance > 0 && (analogRead(RFC) < 511 && analogRead(RBC) < 511 && analogRead(LFC) < 511 && analogRead(LBC) < 511)){
    //give all wheels speed that was assigned
    analogWrite(RFS, spd);
    analogWrite(RBS, spd);
    analogWrite(LFS, spd);
    analogWrite(LBS, spd);
    walk(spin);
    //subtract a foot from the distance
    distance --;
  }
  //turn off the wheels
  analogWrite(RFS, 0);
  analogWrite(RBS, 0);
  analogWrite(LFS, 0);
  analogWrite(LBS, 0);
}

//drive diagonal forward and right
void diagFR (int distance, int spd){
  digitalWrite(RFD, HIGH);
  digitalWrite(RBD, HIGH);
  digitalWrite(LFD, HIGH);
  digitalWrite(LBD, HIGH);
  while(distance > 0 && (analogRead(RFC) < 511 && analogRead(RBC) < 511 && analogRead(LFC) < 511 && analogRead(LBC) < 511)){
    analogWrite(RFS, 0);
    analogWrite(RBS, spd);
    analogWrite(LFS, spd);
    analogWrite(LBS, 0);
    walk();
    distance --;
    
  }
  analogWrite(RFS, 0);
  analogWrite(RBS, 0);
  analogWrite(LFS, 0);
  analogWrite(LBS, 0);
}

//drive diagonal Forward and left
void diagFL (int distance, int spd){
  digitalWrite(RFD, HIGH);
  digitalWrite(RBD, HIGH);
  digitalWrite(LFD, HIGH);
  digitalWrite(LBD, HIGH);
  while(distance > 0 && (analogRead(RFC) < 511 && analogRead(RBC) < 511 && analogRead(LFC) < 511 && analogRead(LBC) < 511)){
    analogWrite(RFS, spd);
    analogWrite(RBS, 0);
    analogWrite(LFS, 0);
    analogWrite(LBS, spd);
    walk();
    distance --;
  }
  analogWrite(RFS, 0);
  analogWrite(RBS, 0);
  analogWrite(LFS, 0);
  analogWrite(LBS, 0);
}

//drive diagonal backward and right
void diagBR (int distance, int spd){
  digitalWrite(RFD, LOW);
  digitalWrite(RBD, LOW);
  digitalWrite(LFD, LOW);
  digitalWrite(LBD, LOW);
  while(distance > 0 && (analogRead(RFC) < 511 && analogRead(RBC) < 511 && analogRead(LFC) < 511 && analogRead(LBC) < 511)){
    analogWrite(RFS, 0);
    analogWrite(RBS, spd);
    analogWrite(LFS, spd);
    analogWrite(LBS, 0);
    walk();
    distance --;
  }
  analogWrite(RFS, 0);
  analogWrite(RBS, 0);
  analogWrite(LFS, 0);
  analogWrite(LBS, 0);
}

//drive diagonal backward and left
void diagBL (int distance, int spd){
  digitalWrite(RFD, LOW);
  digitalWrite(RBD, LOW);
  digitalWrite(LFD, LOW);
  digitalWrite(LBD, LOW);
  while(distance > 0 && (analogRead(RFC) < 511 && analogRead(RBC) < 511 && analogRead(LFC) < 511 && analogRead(LBC) < 511)){
    analogWrite(RFS, spd);
    analogWrite(RBS, 0);
    analogWrite(LFS, 0);
    analogWrite(LBS, spd);
    walk();
    distance --;
  }
  analogWrite(RFS, 0);
  analogWrite(RBS, 0);
  analogWrite(LFS, 0);
  analogWrite(LBS, 0);
}
