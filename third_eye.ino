#define button1 2 // button for only Alarm mode
#define button2 3 // button for Alarm and Vibrator mode
#define button3 4 // button for only Vibrator mode

#define buzzer 5 // pin use for Alarm
#define motor 6 // pin use for Vibrator Motor

#define echopin 7 // echo pin
#define trigpin 8 // trigger pin

int Alarm = 1, Vibrator = 1;
int cm; // Duration used to calculate distance
int distance;

void setup() {
  Serial.begin(9600); // Serial communication at 9600 bits per second

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(motor, OUTPUT);

  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  delay(100);
}

void loop() {

  if (digitalRead(button1) == 0) {
    Alarm = 1;
    Vibrator = 0; // only Alarm mode
  } else if (digitalRead(button2) == 0) {
    Alarm = 1;
    Vibrator = 1; // Alarm and Vibrator mode
  } else if (digitalRead(button3) == 0) {
    Alarm = 0;
    Vibrator = 1; // only Vibrator mode
  }
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  distance = pulseIn(echopin, HIGH);

  // Determine distance from duration
  // Use 343 metres per second as speed of sound
  cm = distance * 0.0343 / 2;

  Serial.print("cm: ");
  Serial.println(cm);

  if (cm > 50) {
    digitalWrite(buzzer, LOW); // Turn off Buzzer
    digitalWrite(motor, LOW); // Turn off Vibrator
  } else {
    int d = map(cm, 20, 100, 20, 2000);
    if (Alarm == 1) {
      digitalWrite(buzzer, HIGH); // Turn on Buzzer
    }
    if (Vibrator == 1) {
      digitalWrite(motor, HIGH); // Turn on Vibrator
    }
    delay(100);
    }
    
    digitalWrite(buzzer, LOW); // Turn off Buzzer
    digitalWrite(motor, LOW); // Turn off Vibrator
  
}
