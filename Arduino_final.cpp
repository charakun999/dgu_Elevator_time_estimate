    #define PIR1_PIN 2
    #define PIR2_PIN 3
    #define ULTRASONIC1_TRIG_PIN 4
    #define ULTRASONIC1_ECHO_PIN A0
    #define ULTRASONIC2_TRIG_PIN 5
    #define ULTRASONIC2_ECHO_PIN A1
    #define ULTRASONIC3_TRIG_PIN 6
    #define ULTRASONIC3_ECHO_PIN A2
    #define EV1_RED 7
    #define EV1_GREEN 8
    #define EV2_RED 9
    #define EV2_YELLOW 10
    #define EV2_GREEN 11

    void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600); // Start serial communication at 9600 baud rate
    pinMode(PIR1_PIN, INPUT);
    pinMode(PIR2_PIN, INPUT);
    pinMode(ULTRASONIC1_TRIG_PIN, OUTPUT);
    pinMode(ULTRASONIC1_ECHO_PIN, INPUT);
    pinMode(ULTRASONIC2_TRIG_PIN, OUTPUT);
    pinMode(ULTRASONIC2_ECHO_PIN, INPUT);
    pinMode(ULTRASONIC3_TRIG_PIN, OUTPUT);
    pinMode(ULTRASONIC3_ECHO_PIN, INPUT);

    }

    long getDistance(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    long distance = duration * 0.034 / 2; // Calculate the distance in cm
    return distance;
    }

    void loop() {
    // put your main code here, to run repeatedly:
    int motionDetected1 = digitalRead(PIR1_PIN);
    int motionDetected2 = digitalRead(PIR2_PIN);

    if (motionDetected1 == 1){
    long distance1 = getDistance(ULTRASONIC1_TRIG_PIN, ULTRASONIC1_ECHO_PIN);
    Serial.print("EV1 line");
    Serial.print(distance1);
    if (distance1 > 30){
    digitalWrite(EV1_GREEN, HIGH);
    digitalWrite(EV1_RED, LOW);
    }
    if (distance1 <= 30){
    digitalWrite(EV1_GREEN, LOW);
    digitalWrite(EV1_RED, HIGH);
    }
    }

    if (motionDetected2 == 1){
    long distance2 = getDistance(ULTRASONIC2_TRIG_PIN, ULTRASONIC2_ECHO_PIN);
    Serial.print("EV2 line");
    Serial.print(distance2);
    long distance3 = 0;
    if (distance2 < 10 && distance2 != 0) {
    distance3 = getDistance(ULTRASONIC3_TRIG_PIN, ULTRASONIC3_ECHO_PIN);
    }
    if (distance2 > 30){
    digitalWrite(EV2_GREEN, HIGH);
    digitalWrite(EV2_YELLOW, LOW);
    digitalWrite(EV2_RED, LOW);
    }
    if (distance2 <= 30 && distance2 >= 15){
    digitalWrite(EV2_GREEN, LOW);
    digitalWrite(EV2_YELLOW, HIGH);
    digitalWrite(EV2_RED, LOW);
    }
    if (distance2 <= 15){
    digitalWrite(EV2_GREEN, LOW);
    digitalWrite(EV2_YELLOW, LOW);
    digitalWrite(EV2_RED, HIGH);
    }

    if (motionDetected1 == 0 && motionDetected2 ==0){
    digitalWrite(EV1_GREEN, HIGH);
    digitalWrite(EV1_RED, LOW);
    digitalWrite(EV2_GREEN, HIGH);
    digitalWrite(EV2_YELLOW, LOW);
    digitalWrite(EV2_RED, LOW);
    }
    }
    }
  