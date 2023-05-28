#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  140 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  490 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

float getAngle1(float x, float y, float phi);
float getAngle2(float x, float y);
void moveLeg(float x, float y);
void step(int shoulder1, int shoulder2, int knee1, int knee2);

void setup() {
    Serial.begin(9600);
    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

//    moveLeg(0, 60, 0, 1);
    uint16_t pulse = map(90, 0, 180, SERVOMIN, SERVOMAX);

    pwm.setPWM(4, 0, pulse);

}

void loop() {
    if (1 == 2) {
    int y = 50;
    int xmin = 0;
    int xmax = 60;

        for (int i = xmin; i < xmax; i++) {
            moveLeg(i, y, 3, 4);
            moveLeg(i, y, 0, 1);
            delay(10);
        }

        for (int i = xmax; i > xmin; i--) {
            moveLeg(i, y, 3, 4);
            moveLeg(i, y, 0, 1);
            delay(10);
        }
    }
}

void moveLeg(float x, float y, int shoulder, int knee) {
  float phi = 3.1415 - acos((3656 - x * x - y * y) / (3400));
  float theta = atan(y / x) - atan((50 * sin(phi)) / (34 + 50 * cos(phi)));

  // radian to degree conversion
  theta = theta * 180 / 3.1415;
  phi = phi * 180 / 3.1415;

  // opposite rotation due to orientation of servo
  if (theta < 0) {
    theta = theta + 180;
  }
  theta = 180 - theta;

  // max angle
  if (phi > 145) {
    phi = 145;
  }

  uint16_t pulse1 = map(theta, 0, 180, SERVOMIN, SERVOMAX);
  uint16_t pulse2 = map(phi, 0, 180, SERVOMIN, SERVOMAX);

  pwm.setPWM(shoulder, 0, pulse1);
  pwm.setPWM(knee, 0, pulse2);
}

void step(int shoulder1, int shoulder2, int knee1, int knee2) {
    for (int i = 0; i < 50; i++) {

    }
}