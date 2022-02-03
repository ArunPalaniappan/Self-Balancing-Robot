// This is the Final Code that we used for the project. 
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Motor A
int motor1Pin1 = 12; 
int motor1Pin2 = 14; 
int enable1Pin = 33; 


// Motor B
int motor2Pin1 = 27; 
int motor2Pin2 = 26; 
int enable2Pin = 25;  


// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8; // resolution is 8, 2^8 = 256. So duty cycle should take values from 0 to 255. Map it accordingly to percentage.
int dutyCycle = 200;

Adafruit_MPU6050 mpu;

void moveForward(int speedDuty){ // speedDuty is an int from 0 to 255

  // setting both motors to 'forward' configuration
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  
  ledcWrite(pwmChannel, speedDuty);
  Serial.print("Forward with duty cycle: ");
  Serial.println(speedDuty);
  // should maintain this signal until it starts rotating in the opposite direction

  delay(100);
}

void moveBackward(int speedDuty){

  // setting both motors to 'forward' configuration
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  
  ledcWrite(pwmChannel, speedDuty);
  Serial.print("Backward with duty cycle: ");
  Serial.println(speedDuty);
  // should maintain this signal until it starts rotating in the opposite direction

  delay(100);
}


void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin(0x69)) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  
  sensors_event_t a1, g1, temp1;
  mpu.getEvent(&a1, &g1, &temp1);

  float initial = g1.gyro.x;
  Serial.print("Initial: ");
  Serial.println(initial);
  Serial.println("");
  delay(100);

  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  pinMode(enable1Pin, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  
  // configure LED Control PWM functionalities -- setting up a PWM channel to create the signal (there are 16 PWM Channels from 0 to 15)
  // LEDC is used to generate PWM signals, but not necessarily only for LEDs
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled -- channeling the same PWM signal through enable1Pin and enable2Pin
  ledcAttachPin(enable1Pin, pwmChannel);
  ledcAttachPin(enable2Pin, pwmChannel);
  
  
  // testing
  Serial.print("Testing DC Motor...");

  // FIRST TEST BACKWARD AND FORWARD PWM MOTION OF MOTORS
  // setting both motors to 'forward' configuration
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);

  for(int j = 0; j<2; j++){
    for(int i = 200; i < 255; i+=5) {
      ledcWrite(pwmChannel, i);
      Serial.print("Forward with duty cycle: ");
      Serial.println(i);
      delay(1000);
    }
  }
 
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  
  for(int j = 0; j<2; j++){
    for(int i = 200; i < 255; i+=5) {
      ledcWrite(pwmChannel, i);
      Serial.print("Backward with duty cycle: ");
      Serial.println(i);
      delay(1000);
    }
  }

  ledcWrite(pwmChannel, 0);
  
  // DONE TESTING
  
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float gyroX = g.gyro.x;

  //PRINT THE ROTATION SPEED OF X
  Serial.print("Rotation X: ");
  Serial.print(gyroX);
  Serial.println("");

  // NOW NEED MAKE IT SELF-BALANCE
  // [-0.03, 0.06, 0.30, 0.53, 0.84, 0.97, 1.32, 1.42, 1.57, 1.84, 2.06, 2.29, 2.37, 2.86, 3.38, 3.56, 3.72, 4.09, 4.45, 4.49]
  
  int speed;

  if(gyroX < 0) {
    speed = 200 + (-1*gyroX/4.49)*55;
    moveForward(speed);
    
  }
  else {
    speed = 200 + (gyroX/4.49)*55;
    moveBackward(speed);
  }
  
}
