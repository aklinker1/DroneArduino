#include <Servo.h>

void performCommand(char action, int value);

const int THROTTLE_TRIM = 4;
const int PITCH_TRIM = 8;
const int ROLL_TRIM = 6;
const int YAW_TRIM = 6;

Servo throttle;
Servo pitch;
Servo roll;
Servo yaw;
Servo arm;
Servo dropper;

void setup() {
  pitch.attach(A0);
  roll.attach(A1);
  yaw.attach(A2);
  throttle.attach(A3);
  arm.attach(A4);
  dropper.attach(A5);
  Serial.begin(9600);
  Serial.setTimeout(10);
  Serial.println("Ready");

  throttle.writeMicroseconds(1000 + THROTTLE_TRIM);
  pitch.writeMicroseconds(1500 + PITCH_TRIM);
  roll.writeMicroseconds(1500 + ROLL_TRIM);
  yaw.writeMicroseconds(1500 + YAW_TRIM);
  arm.writeMicroseconds(1500);
  dropper.writeMicroseconds(50);
}

void loop() {
  if (Serial.available()) {
    long tic = millis();
    String command = Serial.readStringUntil(';');
    char action = command.charAt(0);
    String value = command.substring(1);
    performCommand(action, value);
    long tok = millis() - tic;
    //    Serial.print(command);
    //    Serial.print(": ");
    //    Serial.println(tok);
  }
}

void performCommand(char action, String value) {
  if (action == 'm') {
    int t = value.substring(0, 4).toInt();
    int r = value.substring(4, 8).toInt();
    int p = value.substring(8, 12).toInt();
    int y = value.substring(12, 16).toInt();
    throttle.writeMicroseconds(t + THROTTLE_TRIM);
    roll.writeMicroseconds(r + ROLL_TRIM);
    pitch.writeMicroseconds(p + PITCH_TRIM);
    yaw.writeMicroseconds(y + YAW_TRIM);
  } else if (action == 'a') {
    arm.writeMicroseconds(value.toInt() == 0 ? 1500 : 1000);
  } else if (action == 'd') {
    dropper.writeMicroseconds(value.toInt() == 0 ? 50 : 1500);
  }
}

