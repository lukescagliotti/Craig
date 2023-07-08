-#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

// Wi-Fi credentials
char ssid[] = "YourSSID";
char password[] = "YourPassword";
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

// Blynk authentication token
char auth[] = "YourAuthToken";

// Servo objects and pins
Servo servo1, servo2, servo3, servo4, servo5, servo6;
const int servo1Pin = 2;
const int servo2Pin = 3;
const int servo3Pin = 4;
const int servo4Pin = 5;
const int servo5Pin = 6;
const int servo6Pin = 7;
int servopos = 0;
int servodelay = 15; // in milliseconds

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Attach Servo objects to pins
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);
  servo5.attach(servo5Pin);
  servo6.attach(servo6Pin);

  // Set initial positions of Servo objects
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  servo5.write(90);
  servo6.write(90);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");

  // Start Blynk connection
  Blynk.begin(auth, WiFi.SSID().c_str(), WiFi.psk().c_str());
  Serial.println("Connected to Blynk");

  // Set up virtual pins for servos
  Blynk.virtualWrite(V1, "90");
  Blynk.virtualWrite(V2, "90");
  Blynk.virtualWrite(V3, "90");
  Blynk.virtualWrite(V4, "90");
  Blynk.virtualWrite(V5, "90");
  Blynk.virtualWrite(V6, "90");

  // Set up virtual pin handlers for servos
  Blynk.virtualWrite(V1, [] (BlynkParam param) {
    int servo1Pos = param.asInt();
    servo1.write(servo1Pos);
  });

  Blynk.virtualWrite(V2, [] (BlynkParam param) {
    int servo2Pos = param.asInt();
    servo2.write(servo2Pos);
  });

  Blynk.virtualWrite(V3, [] (BlynkParam param) {
    int servo3Pos = param.asInt();
    servo3.write(servo3Pos);
  });

  Blynk.virtualWrite(V4, [] (BlynkParam param) {
    int servo4Pos = param.asInt();
    servo4.write(servo4Pos);
  });

  Blynk.virtualWrite(V5, [] (BlynkParam param) {
    int servo5Pos = param.asInt();
    servo5.write(servo5Pos);
  });

  Blynk.virtualWrite(V6, [] (BlynkParam param) {
    int servo6Pos = param.asInt();
    servo6.write(servo6Pos);
  });

//    Blynk.begin(auth, ssid, pass);
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  servo6.attach(7);
}

void loop() {
  Blynk.run();
  for (int i = 0; i <= 180; i++) {
    servopos = i;
    servo1.write(servopos);
    servo2.write(servopos);
    servo3.write(servopos);
    servo4.write(servopos);
    servo5.write(servopos);
    servo6.write(servopos);
    delay(servodelay);
  }
  
BLYNK_WRITE(V1) {
  String servoValues = param.asStr();

  int pos1 = servoValues.substring(0, 3).toInt();
  int pos2 = servoValues.substring(3, 6).toInt();
  int pos3 = servoValues.substring(6, 9).toInt();
  int pos4 = servoValues.substring(9, 12).toInt();
  int pos5 = servoValues.substring(12, 15).toInt();
  int pos6 = servoValues.substring(15, 18).toInt();

  servo1.write(pos1);
  servo2.write(pos2);
  servo3.write(pos3);
  servo4.write(pos4);
  servo5.write(pos5);
  servo6.write(pos6);
  delay(2000); // Wait for 2 seconds
  
  for (int i = 180; i >= 0; i--) {
    servopos = i;
    servo1.write(servopos);
    servo2.write(servopos);
    servo3.write(servopos);
    servo4.write(servopos);
    servo5.write(servopos);
    servo6.write(servopos);
    delay(servodelay);
  }
  
  Serial.print("Servo values: ");
  Serial.print(pos1);
  Serial.print(", ");
  Serial.print(pos2);
  Serial.print(", ");
  Serial.print(pos3);
  Serial.print(", ");
  Serial.print(pos4);
  Serial.print(", ");
  Serial.print(pos5);
  Serial.print(", ");
  Serial.println(pos6);
  delay(2000); // Wait for 2 seconds
}