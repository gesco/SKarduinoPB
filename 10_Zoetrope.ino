// Name constants
const int controlPin1 = 2;
const int controlPin2 = 3;
const int enablePin = 9;
const int directionSwitchPin = 4;
const int onOffSwitchStateSwitchPin = 5;
const int potPin = A0;

// Variables for remembering program state
int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;
int directionSwitchState = 0;
int previousDirectionSwitchState = 0;

// Variables for moter control
int motorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 1;

void setup() {
  // Declare the digital pins as inputs and outputs
  pinMode(directionSwitchPin, INPUT);
  pinMode(onOffSwitchStateSwitchPin, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // Turn the motor off
  digitalWrite(enablePin, LOW);
}

void loop() {
  // Read sensor information
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin);
  delay(1);
  directionSwitchState = digitalRead(directionSwitchPin);
  motorSpeed = analogRead(potPin)/4;

  // Check if on/off sensor has changed
  if(onOffSwitchState != previousOnOffSwitchState) {
    if(onOffSwitchState == HIGH) {
      motorEnabled = !motorEnabled;
    }
  }

  // Change the pins to turn the motor in the proper direction
  if(motorDirection == 1) {
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
  }
  else {
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
  }

  // PWM the motor if it is enabled
  if(motorEnabled == 1) {
    analogWrite(enablePin, motorSpeed);
  }
  else {
    analogWrite(enablePin, 0);
  }

  // Save the current state for the next loop()
  previousDirectionSwitchState = directionSwitchState;
  previousOnOffSwitchState = onOffSwitchState;
}
