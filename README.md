# Electric-Scooter
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
### TO-DO List
- [x] STAY UP TO DATE WITH THE COSTS OF THIS PROJECT
- [x] Add mathematics program output image (mathematics.jpg)
- [x] Add the Inventor Assembly as an image (design.gif & design.stl)
- [ ] Add an image of the mechanical part finished (mechanical.jpg)
- [ ] Add images of implemented safety (emergency stop & wiring in waterproof box = safety1.jpg & safety2.jpg)
- [ ] Add top speed in km/h and mph
- [ ] Add cost price
- [ ] Add logs (August 2018 up to ???)
- [ ] Add a complete image (final.jpg)
- [ ] Add a video demonstration (youtube video)
- [ ] Remove this list (everything in between the slashes)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
![final.jpg](https://github.com/rubenvanopstal/Electric-Scooter/blob/master/README_IMGS/final.jpg)

Top speed: ??? km/h ≈ ??? mph. [Video demonstration](http://www.youtube.com/watch?v=).


## The Idea
A design and practical implementation of a three-phase brushless DC (BLDC) motor control system for an electric scooter. 

My goal is to create an electric scooter that is powerful enough to pull me up hills while still keeping my own (and of course other road users) safety in mind. In this project I will address several possibilities to make the scooter safer.

The choices I made about the parts are discussed and compared with other possibilities.

The problems I faced during this project and how I fixed these problems are also discussed and explained. I also made a cost price of my scooter and compared it to current market offers of electric scooters.


## The Process
### 1. Risks
Some of the risks I thought of:
* Motor cannot be stopped
* Insufficient braking capacity
* Mass inertia
* Possible danger of understeer
* Too fast/estimation problem due to environment
* Too fast/estimation problem due to driver
* Not being able to warn other road users
* Accelerate too fast/decelerate too slowly
* Poor lighting
* Controller defective (throttle)
* Fall hazard due to driving with one hand
* Fall hazard due to not sitting on a saddle
* Risk of clamping of limbs/clothing
* Danger of slipping due to combination tire-road surface
* Explosion of the tires due to high speed
* Too large of a reaction time during braking
* Overheating of the motor
* Overheating the speedcontroller
* Possible dangers of the battery
* Short-circuit due to water intrusion/sudden temperature changes
* Slipping over footplate
* Hazards due to imbalance of the vehicle
* Uncontrollability during testing
* Roller chain fails


### 2. Mathematics
Took me less than 10 mins to write this simple mathematics program which will give me an easier time choosing a gear ratio:
![mathematics.jpg](https://github.com/rubenvanopstal/Electric-Scooter/blob/master/README_IMGS/mathematics.jpg)

The code is in the source. I later realised I could've simply used Excel...

As seen in the above (left) console output a gear ratio of 12 to 36 would do fine. I chose to go with the following parts:
* Drive sprocket (12 tooth 3/8“ x 7/32“ DIN ISO 606)
* Driven sprocket (36 tooth 3/8“ x 7/32“ DIN ISO 606)
* Roller chain (3/8“ x 7/32“ DIN ISO 606)

### 3. Design
I'm designing a completely new scooter frame, based of casual scooters with the motor driving the rear wheel.


![design.gif](https://github.com/rubenvanopstal/Electric-Scooter/blob/master/README_IMGS/design.gif)


Main electronics. These will go inside the waterproof box:
* Turnigy Aerodrive SK3 - 6374-149KV Brushless Outrunner Motor
* YEP 120A HV (4~14S) Brushless Speed Controller (OPTO)
* ZIPPY Compact 5000mAh 6S 25C Lipo Pack
* Arduino Uno V3

I chose to go with the above electronic components simply because I had already bought these for my [electric bike](https://github.com/rubenvanopstal/Electric-Bike) which I had disassembled before starting this project.


### 4. Production
Processes used to fabricate the scooter:
* Welding
* Milling
* Turning
* Boring
* Tapping

![mechanical.jpg](https://github.com/rubenvanopstal/Electric-Scooter/blob/master/README_IMGS/mechanical.jpg)


### 5. Software
First code, needs safety implementation:
```C++
#include <Servo.h>
Servo esc;

int throttlePin = 0;
 
void setup(){
  esc.attach(8);
}
 
void loop(){
  int throttle = analogRead(throttlePin);
  throttle = map(throttle, 0, 1023, 0, 179);
  esc.write(throttle);
}
```


### 6. Safety
Applying safety by thinking back on the risks I talked about. Changing software/hardware:
* Added a waterproof box (Short-circuit due to water intrusion/sudden temperature changes)
* Added an emergency stop (Motor cannot be stopped)
* Added a main switch
* Added fuses

![safety1.jpg](https://github.com/rubenvanopstal/Electric-Scooter/blob/master/README_IMGS/safety1.jpg)
![safety2.jpg](https://github.com/rubenvanopstal/Electric-Scooter/blob/master/README_IMGS/safety2.jpg)


* Added ramping in my code (Accelerate too fast/decelerate too slowly)
```C++
#include <Servo.h>
Servo esc;

#define throttlePin A0

#define MIN_READ_VALUE 178
#define MAX_READ_VALUE 880
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
```


### 7. Pricing
Cost: **€ ???**
* Motor
* Speedcontroller
* Programming card
* Batteries (5S & 6S LiPo)
* LiPo Balance charger
* Scooter wheels (200mm x 50mm = 8“)
* Sprockets (12 tooth & 36 tooth 3/8“ x 7/32“ DIN ISO 606)
* Roller chain (3/8“ x 7/32“ DIN ISO 606)
* Translock/taperlock (8mm x 19mm)
* Steel for the frame
* Waterproof box
* Heat shrink tubing
* All sorts of connectors
* Fuses & fuse holder
* Main switch
* Cables


Expenses I didn't take into account:
* Cutting plates from the milling and turning process
* Welding wire, power consumption and gas consumption from the welding process
* Power consumption of the milling machine and lathe
* DC-to-DC step-down converter, wires, soldering, small fuse, resistors, ...


### 8. Logs
August 2018 up to ?????.
