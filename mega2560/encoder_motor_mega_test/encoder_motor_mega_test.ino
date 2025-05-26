// === 핀 설정 ===
const byte encoder0pinA = 2;     // 엔코더 A상 (인터럽트)
const byte encoder0pinB = 4;     // 엔코더 B상

const int motorPWM = 3;          // PWM 핀 (Motor Shield M1)
const int motorDir1 = 12;        // 방향 제어 핀 1
const int motorDir2 = 9;         // 방향 제어 핀 2

// === 엔코더 및 속도 측정 ===
volatile long pulseCount = 0;
byte encoder0PinALast;
bool Direction;

unsigned long lastTime = 0;
float speed_cmps = 0.0;

const float wheel_diameter_cm = 6.6;
const float wheel_circumference_cm = 3.1416 * wheel_diameter_cm;  // ≈ 20.73 cm
const int gear_ratio = 120;
const int ppr = 20;
const int pulses_per_revolution = gear_ratio * ppr;  // 2400

void setup() {
  Serial.begin(57600);

  // 엔코더 핀 설정
  pinMode(encoder0pinA, INPUT);
  pinMode(encoder0pinB, INPUT);
  encoder0PinALast = digitalRead(encoder0pinA);
  Direction = true;
  attachInterrupt(digitalPinToInterrupt(encoder0pinA), countPulse, CHANGE);

  // 모터 핀 설정
  pinMode(motorPWM, OUTPUT);
  pinMode(motorDir1, OUTPUT);
  pinMode(motorDir2, OUTPUT);

  // 모터 방향 설정 (전진)
  digitalWrite(motorDir1, HIGH);
  digitalWrite(motorDir2, LOW);

  // 모터 속도 설정 (PWM 출력)
  analogWrite(motorPWM, 100);  // 0~255 사이로 조절 가능
}

void loop() {
  unsigned long now = millis();
  if (now - lastTime >= 10) {  // 100ms 주기
    noInterrupts();
    long pulses = pulseCount;
    pulseCount = 0;
    interrupts();

    // float revs_per_sec = (float) / pulses_per_revolution / 0.1;
    speed_cmps = pulses * 1.063;

    Serial.print("Pulse: ");
    Serial.print(pulses);
    Serial.print("\tSpeed: ");
    Serial.print(speed_cmps, 2);
    Serial.println(" cm/s");

    lastTime = now;
  }
}

void countPulse() {
  int Lstate = digitalRead(encoder0pinA);
  if ((encoder0PinALast == LOW) && Lstate == HIGH) {
    int val = digitalRead(encoder0pinB);
    if (val == LOW && Direction) {
      Direction = false;  // Reverse
    } else if (val == HIGH && !Direction) {
      Direction = true;   // Forward
    }
  }
  encoder0PinALast = Lstate;

  if (!Direction)
    pulseCount++;
  else
    pulseCount--;
}
