#include <NewPing.h>

// تعریف پین‌ها برای سنسور فاصله
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200 // فاصله حداکثر برای سنسور (سانتی‌متر)

// تعریف پین‌ها برای موتورها
#define MOTOR_A_PIN  3
#define MOTOR_B_PIN  4

// ایجاد شیء سنسور فاصله
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  pinMode(MOTOR_A_PIN, OUTPUT);
  pinMode(MOTOR_B_PIN, OUTPUT);
}

void loop() {
  iterativeDeepeningSearch();
}

void iterativeDeepeningSearch() {
  int limit = 1; // شروع با لیمیت 1 سانتی‌متر
  bool exitFound = false;

  while (!exitFound) {
    exitFound = depthFirstSearch(0, limit, 0);
    limit++; // افزایش لیمیت برای تکرار بعدی
  }
}

bool depthFirstSearch(int depth, int limit, int zeroCounter) {
  if (depth >= limit) return false; // رسیدن به لیمیت

  // بررسی فاصله تا دیوار
  unsigned int distance = sonar.ping_cm();
  if (distance == 0 || distance > MAX_DISTANCE) {
    zeroCounter++;
    if (zeroCounter == 2) {
      // فرض بر این است که خروجی پیدا شده است
      return true;
    }
  } else {
    zeroCounter = 0; // ریست شمارنده اگر دیوار تشخیص داده شود
  }

  // حرکت به جلو
  moveForward();

  // تلاش برای یافتن خروجی در عمق بیشتر
  if (depthFirstSearch(depth + 1, limit, zeroCounter)) {
    return true;
  }

  // حرکت به عقب
  moveBackward();

  // ادامه جستجو در سایر جهات اگر نیاز باشد
  // ...

  return false; // خروجی پیدا نشده است
}

void moveForward() {
  digitalWrite(MOTOR_A_PIN, HIGH);
  digitalWrite(MOTOR_B_PIN, LOW);
  delay(100); // حرکت به مدت 100 میلی‌ثانیه
}

void moveBackward() {
  digitalWrite(MOTOR_A_PIN, LOW);
  digitalWrite(MOTOR_B_PIN, HIGH);
  delay(100); // حرکت به مدت 100 میلی‌ثانیه
}
