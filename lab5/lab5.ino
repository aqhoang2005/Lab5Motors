#define BLUETOOTH_BAUD_RATE 38400

//From LAB 5 PWM Motor.c.txt
// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
#define MotorPWM_A 4 //left motor
#define MotorPWM_B 5 //right motor
#define INA1A 32
#define INA2A 34
#define INA1B 30
#define INA2B 36

//From Lab 5 RPM Encoder.c.txt
#define ENCODER_LEFT 2  // Motor 1
#define ENCODER_RIGHT 3 // Motor 2
static volatile int16_t count_left=0;
// 3.215 = (60sec/0.1sec)/(48gear ratio * 4pulses/rev)
float rotation=3.125;  
float RPM=0;

// Method: Forward
// Input: speed – value [0-255]
// Rotate the motor in a clockwise fashion
void Forward(int speed)
{
  analogWrite(MotorPWM_A, speed);
  analogWrite(MotorPWM_B, speed);

  // Left Motor
  digitalWrite(INA1A, HIGH);
  digitalWrite(INA2A, LOW);

  // Right Motor
  digitalWrite(INA1B, HIGH);
  digitalWrite(INA2B, LOW);
}

//Method: Drive
// Input: speed - value[0-255], duration - int for microseconds
void drive(int speed, int duration) 
{   digitalWrite(Standby, HIGH); // Turn the motor on
    if (speed >= 0) forward(speed);
    else reverse(-speed);

    delay(duration)
}

/***************************************/
// This is the Interrupt Service Routine
// for the left motor.
/***************************************/
void ISRMotorLeft()
{
  count_left++;
}

void setup() {
  //Motor
  pinMode(MotorPWM_A, OUTPUT);
  pinMode(MotorPWM_B, OUTPUT);
  pinMode(INA1A, OUTPUT);
  pinMode(INA2A, OUTPUT);
  pinMode(INA1B, OUTPUT);
  pinMode(INA2B, OUTPUT);

  //Encoder
  pinMode(ENCODER_LEFT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), ISRMotorLeft, FALLING);
}

//encoder reading to RPM   
void loop() {
    count_left=0;
    delay(100);
    RPM = count_left*rotation;
    Serial.print("RPM = ");
    Serial.println(RPM);

    if (Serial2.available()){ //send to car
      char receivedChar = Serial2.read(); // Read the incoming byte
      Serial.print("Received on Serial2: ");
      Serial.println(receivedChar); // Print it to the Serial Monitor
      if(receivedChar == 'F'){
        
      }
      else if(receivedChar == 'B'){
        
      }
    }
    if (Serial2.available()) {
      char sentChar = Serial2.read(); // Read the incoming byte
      Serial.print("Sending to Serial2: ");
      Serial.println(sentChar);
      Serial2.write(sentChar); // Send it out through Serial1
    }
 }