void setup() {
  // setting up pins for motor, ultrasonic and linefollowing sensors
  setupSensorActuator();
}

void loop() {
  // put your main code here, to run repeatedly:

  // reading distance from ultrasonic sensor
  float distance = readDistance();
 
  // reading the sensors and saving their values in _Dark variables
  int leftDark = analogRead(A0);
  int midDark = analogRead(A1);
  int rightDark = analogRead(A2);
  
  /// Turning on motors, spin for a half second
  motorControl(255, -255);
  delay(500);
  motorControl(0,0);
  // printing out to Serial from sensors
  Serial.println("Distance: "+String(distance)+" leftDark: " +String(leftDark)+" midDark: "+String(midDark)+" rightDark: "+String(rightDark));
  
}


void setupSensorActuator(){
  // setting up the serial monitor and sensor pins
  Serial.begin(9600);
  // setting up sensor pins for line following
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  // setting up ultrasonic sensors as input/output
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);
  // setting up motor pins as output
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}
// read distance from ultrasonic sensor
float readDistance(){
  // pulse the ultrasonic speaker
  digitalWrite(13, LOW);
  delayMicroseconds(2);
  digitalWrite(13, HIGH);
  delayMicroseconds(20);
  digitalWrite(13, LOW);
  // read the time it takes to return the ultrasonic pulse
  float duration = pulseIn(12, HIGH);
  // return the distance to the main program
  return duration / 58;
}
// motor control inputs of left motor, right motor from -255 to 255
void motorControl(float leftSpeed, float rightSpeed) {
  // turning motors on
  digitalWrite(3, HIGH);
  // setting motor direction with boolean operators for HIGH/LOW ~ forward/back
  digitalWrite(7, leftSpeed > 0);
  digitalWrite(8, rightSpeed > 0);
  // finding the absolute value of motor speeds, then constraining to 0-255 and setting speed left/right
  analogWrite(5, constrain(abs(leftSpeed), 0, 255));
  analogWrite(6, constrain(abs(rightSpeed), 0, 255));
}
