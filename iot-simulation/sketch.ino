
#include <LiquidCrystal.h>
#include <DHT.h>
#include <ESP32Servo.h>
#include <math.h>

// Pin definitions
#define LED_RED 23
#define LED_GREEN 22
#define DHT_PIN 12
#define SERVO_PIN 14
#define SWITCH_LEFT 18
#define SWITCH_RIGHT 19
#define POT_PIN 34

#define DHT_TYPE DHT22

// Components
DHT dht(DHT_PIN, DHT_TYPE);
Servo irrigationServo;
LiquidCrystal lcd(2, 0, 4, 16, 17, 5);

// Settings
const int DRY_LEVEL = 30;
const float DRY_HUMIDITY = 30.0;
const float HOT_TEMPERATURE = 30.0;

void setup() {
  Serial.begin(115200);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(SWITCH_LEFT, INPUT_PULLUP);
  pinMode(SWITCH_RIGHT, INPUT_PULLUP);
  pinMode(POT_PIN, INPUT);

  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);

  dht.begin();

  irrigationServo.setPeriodHertz(50);
  irrigationServo.attach(SERVO_PIN, 500, 2400);
  irrigationServo.write(0);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Irrigation");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  
  Serial.println("Smart Irrigation System starting...");
  delay(2000);
}

void loop() {
  // Read sensors
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  int potValue = analogRead(POT_PIN);
  int soilLevel = map(potValue, 0, 4095, 0, 100);

  Serial.println("\n--- Sensor Readings ---");

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("ERROR: DHT22 sensor reading failed.");

    irrigationServo.write(0);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DHT22 Error");
    lcd.setCursor(0, 1);
    lcd.print("Watering OFF");

    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Pot level: ");
  Serial.print(soilLevel);
  Serial.println(" %");

  // Display sensor readings
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperature, 1);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Hum:");
  lcd.print(humidity, 1);
  lcd.print("%");

  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Soil level:");
  lcd.print(soilLevel);
  lcd.print("%");

  delay(1500);

  // Irrigation control
  String status;

  if (soilLevel < DRY_LEVEL &&
      humidity < DRY_HUMIDITY &&
      temperature > HOT_TEMPERATURE) {

    irrigationServo.write(90);
    status = "Full watering";

  } else if (soilLevel < DRY_LEVEL &&
             humidity < DRY_HUMIDITY) {

    irrigationServo.write(60);
    status = "Medium watering";

  } else {
    irrigationServo.write(0);
    status = "Watering OFF";
  }

  bool watering = (soilLevel < DRY_LEVEL &&
                   humidity < DRY_HUMIDITY);

  digitalWrite(LED_GREEN, watering ? HIGH : LOW);
  digitalWrite(LED_RED, watering ? LOW : HIGH);

  Serial.print("Irrigation status: ");
  Serial.println(status);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Irrigation:");

  lcd.setCursor(0, 1);
  lcd.print(status);

  delay(2000);
}
