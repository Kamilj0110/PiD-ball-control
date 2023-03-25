
#include <Servo.h>
#include <SharpIR.h>
#include <Wire.h>
#define IR A0
#define model 1080

///////////////////////Inputs/outputs///////////////////////


SharpIR SharpIR(IR,model);
Servo myservo;  
///////////////////////////////////////////////////////


////////////////////////Variables///////////////////////
int Read = 0;
float distance = 0.0;
float elapsedTime, time, timePrev;
float distance_previous_error, distance_error;
int period =50;  
///////////////////////////////////////////////////////


///////////////////PID constants///////////////////////
float kp=2.4; 
float ki=0.02; 
float kd=430; 
float distance_setpoint = 20;           
float PID_p, PID_i, PID_d, PID_total;
int dis;
///////////////////////////////////////////////////////



void setup() {

  Serial.begin(9600);  
  myservo.attach(9); 
  myservo.write(90); 

  
  
  time = millis();
}

void loop() {
  if (millis() > time+period)
  {
    time = millis();    
    distance = SharpIR.distance(); 
    Serial.println(distance);  
    distance_error = distance_setpoint - distance;   
    PID_p = kp * distance_error;
    float dist_diference = distance_error - distance_previous_error;     
    PID_d = kd*((distance_error - distance_previous_error)/period);
      
    if(-5 < distance_error && distance_error < 5)
    {
      PID_i = PID_i + (ki * distance_error);
    }
    else
    {
      PID_i = 0;
    }
  
    PID_total = PID_p + PID_i + PID_d;  
    PID_total = map(PID_total, -150, 150, 0, 179);
  
    if(PID_total < 0){PID_total = 0;}
    if(PID_total > 150) {PID_total = 178; } 
    myservo.write(PID_total);  
    distance_previous_error = distance_error;
  }
}








