// Motor Pin Assignments
const int FL1 = 2; // Front Left Motor IN1
const int FL2 = 3; // Front Left Motor IN2
const int FR1 = 4; // Front Right Motor IN1
const int FR2 = 5; // Front Right Motor IN2
const int BL1 = 6; // Back Left Motor IN1
const int BL2 = 7; // Back Left Motor IN2
const int BR1 = 8; // Back Right Motor IN1
const int BR2 = 9; // Back Right Motor IN2

void setup() {
  // Set motor pins as outputs
  pinMode(FL1, OUTPUT);
  pinMode(FL2, OUTPUT);
  pinMode(FR1, OUTPUT);
  pinMode(FR2, OUTPUT);
  pinMode(BL1, OUTPUT);
  pinMode(BL2, OUTPUT);
  pinMode(BR1, OUTPUT);
  pinMode(BR2, OUTPUT);
}

void loop() {
  // Move forward for 2 seconds
  moveForward();
  delay(2000);
  
  // Turn right for 1 second
  turnRight();
  delay(1000);
  
  // Move backward for 2 seconds
  moveBackward();
  delay(2000);
  
  // Turn left for 1 second
  turnLeft();
  delay(1000);
  
  // Stop for a moment
  stopMotors();
  delay(1000);
}

void moveForward() {
  // Front left and back left move forward
  digitalWrite(FL1, HIGH);
  digitalWrite(FL2, LOW);
  digitalWrite(BL1, HIGH);
  digitalWrite(BL2, LOW);
  
  // Front right and back right move forward
  digitalWrite(FR1, HIGH);
  digitalWrite(FR2, LOW);
  digitalWrite(BR1, HIGH);
  digitalWrite(BR2, LOW);
}

void moveBackward() {
  // Front left and back left move backward
  digitalWrite(FL1, LOW);
  digitalWrite(FL2, HIGH);
  digitalWrite(BL1, LOW);
  digitalWrite(BL2, HIGH);
  
  // Front right and back right move backward
  digitalWrite(FR1, LOW);
  digitalWrite(FR2, HIGH);
  digitalWrite(BR1, LOW);
  digitalWrite(BR2, HIGH);
}

void turnRight() {
  // Turn right (rotate clockwise)
  digitalWrite(FL1, HIGH);
  digitalWrite(FL2, LOW);
  digitalWrite(BL1, HIGH);
  digitalWrite(BL2, LOW);
  digitalWrite(FR1, LOW);
  digitalWrite(FR2, HIGH);
  digitalWrite(BR1, LOW);
  digitalWrite(BR2, HIGH);
}

void turnLeft() {
  // Turn left (rotate counter-clockwise)
  digitalWrite(FL1, LOW);
  digitalWrite(FL2, HIGH);
  digitalWrite(BL1, LOW);
  digitalWrite(BL2, HIGH);
  digitalWrite(FR1, HIGH);
  digitalWrite(FR2, LOW);
  digitalWrite(BR1, HIGH);
  digitalWrite(BR2, LOW);
}

void stopMotors() {
  digitalWrite(FL1, LOW);
  digitalWrite(FL2, LOW);
  digitalWrite(FR1, LOW);
  digitalWrite(FR2, LOW);
  digitalWrite(BL1, LOW);
  digitalWrite(BL2, LOW);
  digitalWrite(BR1, LOW);
  digitalWrite(BR2, LOW);
}