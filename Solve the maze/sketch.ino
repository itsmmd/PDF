#include <Servo.h>

// تعریف پین‌های سنسور
const int sensorUp = 2;
const int sensorDown = 3;
const int sensorLeft = 4;
const int sensorRight = 5;

// تعریف پین‌های موتور
const int motor1Pin1 = 6;
const int motor1Pin2 = 7;
const int motor2Pin1 = 8;
const int motor2Pin2 = 9;
const int motor3Pin1 = 10;
const int motor3Pin2 = 11;
const int motor4Pin1 = 12;
const int motor4Pin2 = 13;

// تابع برای تشخیص دیوار
bool isWall(int sensorPin) {
  return digitalRead(sensorPin) == HIGH; // فرض بر اینکه سنسور 1 را در صورت تشخیص دیوار باز می‌گرداند
}

// تابع برای حرکت به جلو
void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, HIGH);
  digitalWrite(motor4Pin2, LOW);
}

// تابع برای چرخش به چپ
void turnLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  digitalWrite(motor3Pin1, HIGH);
  digitalWrite(motor3Pin2, LOW);
  digitalWrite(motor4Pin1, HIGH);
  digitalWrite(motor4Pin2, LOW);
}

// تابع برای چرخش به راست
void turnRight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, HIGH);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, HIGH);
}

// تابع برای برگشتن
void turnAround() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  digitalWrite(motor3Pin1, LOW);
  digitalWrite(motor3Pin2, HIGH);
  digitalWrite(motor4Pin1, LOW);
  digitalWrite(motor4Pin2, HIGH);
  delay(500); // فرض بر اینکه این زمان کافی برای چرخش 180 درجه است
}

// تابع DFS
void dfs() {
  if (isWall(sensorUp)) {
    // اگر جلو دیوار است
    turnAround();
  } else {
    // اگر جلو دیوار نیست
    moveForward();
    if (isWall(sensorRight)) {
      // اگر راست دیوار است
      turnLeft();
    } else {
      // اگر راست دیوار نیست
      turnRight();
    }
  }
}

void setup() {
  // مقداردهی اولیه سنسورها و موتورها
  pinMode(sensorUp, INPUT);
  pinMode(sensorDown, INPUT);
  pinMode(sensorLeft, INPUT);
  pinMode(sensorRight, INPUT);
  
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);
  pinMode(motor4Pin1, OUTPUT);
  pinMode(motor4Pin2, OUTPUT);
}

void loop() {
  dfs(); // اجرای الگوریتم DFS
}
