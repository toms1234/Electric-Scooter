#include <Servo.h>
Servo esc;

#define throttlePin A0

#define MIN_READ_VALUE 178
#define MAX_READ_VALUE 880
#define MAX_SPEED_DIFF 10
#define MAX_SETPOINT 700
#define MAX_PWM 180

float throttleValue, throttleSafe, speed_diff, acceleration, setpoint, pwmCalc;

void setup() {
  pinMode(throttlePin, INPUT);
  esc.attach(8);
}

void loop() {  
  throttleValue = analogRead(throttlePin);
  if ((throttleValue > (MIN_READ_VALUE - 60)) && (throttleValue < (MAX_READ_VALUE + 20)))
  {    
    setpoint = throttleValue - 176;
    if (abs(setpoint) < 4) {
      setpoint = 0;
    } else if (abs(setpoint) > 695) {
      setpoint = 695;
    }

    throttleSafe = (setpoint * MAX_PWM)/MAX_SETPOINT;
    speed_diff = setpoint - pwmCalc;

    if (speed_diff > 2) {
      acceleration += 2;
      delay(50);
    }
    if (speed_diff < -2) {
      acceleration -= 2;
    }
    if (acceleration > 178) {
      acceleration = 178;
    }
    if (acceleration < 0) {
      acceleration = 0;
    }
    
    pwmCalc = (acceleration * MAX_SETPOINT)/MAX_PWM;
    esc.write(acceleration);
  }
  else if (throttleValue < (MIN_READ_VALUE - 80))
  {
    esc.write(0);
  }
  else if (throttleValue > (MAX_READ_VALUE + 40))
  {
    esc.write(0);
  }
  
}
