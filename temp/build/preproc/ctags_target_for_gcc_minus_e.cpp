# 1 "C:\\Users\\Daniel\\Documents\\GitHub\\con-cho\\main\\main.ino"
# 2 "C:\\Users\\Daniel\\Documents\\GitHub\\con-cho\\main\\main.ino" 2
# 3 "C:\\Users\\Daniel\\Documents\\GitHub\\con-cho\\main\\main.ino" 2

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();





float getAngle1(float x, float y, float phi);
float getAngle2(float x, float y);
void moveLeg(float x, float y, int shoulder, int knee);
void step(int shoulder1, int shoulder2, int knee1, int knee2);
void sit();
void walk(int speed);

void setup() {
    Serial.begin(9600);
    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(50 /* Analog servos run at ~50 Hz updates*/); // Analog servos run at ~50 Hz updates

    // initial state
    uint16_t pulse = map(98, 0, 180, 140 /* This is the 'minimum' pulse length count (out of 4096)*/, 490 /* This is the 'maximum' pulse length count (out of 4096)*/);
    pwm.setPWM(0, 0, pulse);
    pulse = map(94, 0, 180, 140 /* This is the 'minimum' pulse length count (out of 4096)*/, 490 /* This is the 'maximum' pulse length count (out of 4096)*/);
    pwm.setPWM(8, 0, pulse);
    pulse = map(85, 0, 180, 140 /* This is the 'minimum' pulse length count (out of 4096)*/, 490 /* This is the 'maximum' pulse length count (out of 4096)*/);
    pwm.setPWM(12, 0, pulse);
    pulse = map(82, 0, 180, 140 /* This is the 'minimum' pulse length count (out of 4096)*/, 490 /* This is the 'maximum' pulse length count (out of 4096)*/);
    pwm.setPWM(4, 0, pulse);

    // legs resting
    moveLeg(0, 70, 1, 2);
    moveLeg(0, 70, 5, 6);
    moveLeg(0, 70, 9, 10);
    moveLeg(0, 70, 13, 14);

    // step(1, 13, 2, 14);
    // straighten(1, 13, 2, 14);

    // step(5, 9, 6, 10);
    // straighten(5, 9, 6, 10);



    // moveLeg(44, 70, 1, 2);
    delay(1000);
}


void loop() {
    if (1 == 1) {
        // step(1, 13, 2, 14);
        // straighten(1, 13, 2, 14);

        // step(5, 9, 6, 10);
        // straighten(5, 9, 6, 10);
        walk(90);
    }
}

void moveLeg(float x, float y, int shoulder, int knee) {
    // leg cant go that far
    if (sqrt(x*x+y*y) >= 84) {
        uint16_t pulse1 = map(0, 0, 180, 140 /* This is the 'minimum' pulse length count (out of 4096)*/, 490 /* This is the 'maximum' pulse length count (out of 4096)*/);
        uint16_t pulse2 = map(0, 0, 180, 140 /* This is the 'minimum' pulse length count (out of 4096)*/, 490 /* This is the 'maximum' pulse length count (out of 4096)*/);

        pwm.setPWM(shoulder, 0, pulse1);
        pwm.setPWM(knee, 0, pulse2);
    }

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

    uint16_t pulse1 = map(theta, 0, 180, 140 /* This is the 'minimum' pulse length count (out of 4096)*/, 490 /* This is the 'maximum' pulse length count (out of 4096)*/);
    uint16_t pulse2 = map(phi, 0, 180, 140 /* This is the 'minimum' pulse length count (out of 4096)*/, 490 /* This is the 'maximum' pulse length count (out of 4096)*/);

    pwm.setPWM(shoulder, 0, pulse1);
    pwm.setPWM(knee, 0, pulse2);
}

void sit() {

}

void step(int shoulder1, int shoulder2, int knee1, int knee2) {
    int r = 7;
    int x, y;
    // cycloid
    for (int i = 0; i <50; i++) {
        float x = r*(i*0.12566-sin(i*0.12566));
        float y = 70-r*0.7*(1-cos(i*0.12566));
        moveLeg(x, y, shoulder1, knee1);
        moveLeg(x, y, shoulder2, knee2);
        delay(20);
    }
}

void straighten(int shoulder1, int shoulder2, int knee1, int knee2) {
    // move back
    float stepsize = 44/50;
    for (int i = 0; i <= 50; i++) {
        moveLeg(44-0.88*i, 70, shoulder1, knee1);
        moveLeg(44-0.88*i, 70, shoulder2, knee2);
        delay(20);
    }
}

void walk(int speed) {
    int r = 7;
    for (int i = 0; i <50; i++) {
        float x = r*(i*0.12566-sin(i*0.12566));
        float y = 70-r*0.7*(1-cos(i*0.12566));
        moveLeg(x, y-5, 1, 2);
        moveLeg(44-0.88*i-5, 70, 5, 6);
        moveLeg(44-0.88*i, 65, 9, 10);
        moveLeg(x-5, y, 13, 14);
        delay(100-speed);
    }

    for (int i = 0; i <50; i++) {
        float x = r*(i*0.12566-sin(i*0.12566));
        float y = 70-r*0.7*(1-cos(i*0.12566));
        moveLeg(44-0.88*i, 65, 1, 2);
        moveLeg(x-5, y, 5, 6);
        moveLeg(x, y-5, 9, 10);
        moveLeg(44-0.88*i-5, 70, 13, 14);
        delay(100-speed);
    }
}
