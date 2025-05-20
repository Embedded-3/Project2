const byte encoder0pinA = 2; // A상: 인터럽트 핀
const byte encoder0pinB = 3; // B상: 일반 입력
volatile long pulseCount = 0; // 펄스 누적용
byte encoder0PinALast;
bool Direction;

unsigned long lastTime = 0;
float speed_cmps = 0.0;

const float wheel_diameter_cm = 6.6;
const float wheel_circumference_cm = 3.1416 * wheel_diameter_cm;
const int gear_ratio = 120;
const int ppr = 20;
const int pulses_per_revolution = gear_ratio * ppr; // = 2400

void setup() {
  Serial.begin(57600);
  pinMode(encoder0pinA, INPUT);
  pinMode(encoder0pinB, INPUT);
  encoder0PinALast = digitalRead(encoder0pinA);
  Direction = true;
  attachInterrupt(digitalPinToInterrupt(encoder0pinA), countPulse, CHANGE);
}

void loop() {
  unsigned long now = millis();
  if (now - lastTime >= 100) { // 100ms 주기
    noInterrupts();
    long pulses = pulseCount;
    pulseCount = 0;
    interrupts();

    float revs_per_sec = (float)pulses / pulses_per_revolution / 0.1;
    speed_cmps = revs_per_sec * wheel_circumference_cm;

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
      Direction = false; // Reverse
    } else if (val == HIGH && !Direction) {
      Direction = true; // Forward
    }
  }
  encoder0PinALast = Lstate;

  if (!Direction)
    pulseCount++;
  else
    pulseCount--;
}
