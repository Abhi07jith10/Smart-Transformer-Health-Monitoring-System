#include <WiFi.h>              
#include <HTTPClient.h>         

// Ultrasonic Sensor
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

// ZMPT101B Voltage Sensor
#include "ZMPT101B.h"           
#define ZMPT101B_PIN 34  

// DS18B20 Temperature Sensor
#include <OneWire.h>
#include <DallasTemperature.h>


// Ultrasonic Sensor Pins
const int trigPin = 18;
const int echoPin = 5;

// Define Relay and LED Pins
const int relayPin = 15;
const int ledPin = 2;  // Update this according to your ESP32 setup

// Voltage Sensor Initialization
ZMPT101B voltageSensor(ZMPT101B_PIN);

// Temperature Sensor Initialization
const int oneWireBus = 4;       
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

// WiFi & Telegram Configurations
const char* ssid = "aaaa"; 
const char* password = "a8dua422"; 
String serverName = "https://api.telegram.org/bot7619235038:AAFY-pWMQ-XHLNiKVYb9MXoXG7Phvkhp6nE/sendPhoto?chat_id=1619616619&caption=";

// Timers
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;
unsigned long VoltagelastTime = 0;
unsigned long VoltagetimerDelay = 5000;
unsigned long templastTime = 0;
unsigned long temptimerDelay = 5000;

void setup() {
    delay(2000);
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi!");
    Serial.print("ESP32 IP Address: ");
    Serial.println(WiFi.localIP());
    
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    
    sensors.begin();
    Serial.println("Calibrating Voltage Sensor...");
    delay(100);
    voltageSensor.calibrate();
    Serial.println("Done!");

    pinMode(relayPin, OUTPUT); // Set relay as output
    pinMode(ledPin, OUTPUT);   // Set LED as output
    
    digitalWrite(relayPin, LOW); // Initially keep the relay OFF (Transformer ON)
    digitalWrite(ledPin, HIGH);  // Initially keep the LED ON
}

void loop() {
    // Read Ultrasonic Sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    float distanceCm = duration * SOUND_SPEED / 2;
    Serial.print("Distance (cm): "); Serial.println(distanceCm);

    // Read Voltage Sensor
    float voltage = voltageSensor.getVoltageAC();
    Serial.print("Voltage: "); Serial.print(voltage); Serial.println("V");

    // Read Temperature Sensor
    sensors.requestTemperatures();
    float temperatureC = sensors.getTempCByIndex(0);
    Serial.print("Temperature: "); Serial.print(temperatureC); Serial.println("°C");
    
    // Send alerts
    if (voltage <= 1  && millis() - VoltagelastTime > VoltagetimerDelay) {
        sendWhatsAppMessage("Voltage is low: " + String(voltage) + "V", "https://i.imgur.com/szo4kij.png");
        VoltagelastTime = millis();
    } else if (voltage > 2 && millis() - VoltagelastTime > VoltagetimerDelay) {
        sendWhatsAppMessage("Voltage is high: " + String(voltage) + "V", "https://i.imgur.com/338wSKu.png");
        VoltagelastTime = millis();
    }

    if (temperatureC >= 20 && millis() - templastTime > temptimerDelay) {
        sendWhatsAppMessage("Temperature is high: " + String(temperatureC) + "°C", "https://i.imgur.com/8Xdsc9o.png");
        templastTime = millis();
    }
    
    if (distanceCm <= 3 && millis() - lastTime > timerDelay) {
        sendWhatsAppMessage("Oil level is full. Distance: " + String(distanceCm) + "cm", "https://i.imgur.com/BzEiWFC.jpeg");
        lastTime = millis();
    } else if (distanceCm <= 5 && millis() - lastTime > timerDelay) {
        sendWhatsAppMessage("Oil level is medium. Distance: " + String(distanceCm) + "cm", "https://i.imgur.com/k16Gbt9.jpeg");
        lastTime = millis();
    } else if (distanceCm <= 10 && millis() - lastTime > timerDelay) {
        sendWhatsAppMessage("Oil level is low. Distance: " + String(distanceCm) + "cm", "https://i.imgur.com/HCjKBNf.jpeg");
        lastTime = millis();
    }

    // Relay and LED Control based on Temperature
    if (temperatureC >= 50) {  
        digitalWrite(relayPin, HIGH); // Relay ON (Transformer OFF)
        digitalWrite(ledPin, LOW);    // LED OFF
        Serial.println("🔥 High Temperature! Relay Activated, Transformer OFF, LED OFF.");
    } else {
        digitalWrite(relayPin, LOW);  // Relay OFF (Transformer ON)
        digitalWrite(ledPin, HIGH);   // LED ON
        Serial.println("✅ Temperature Normal. Relay Deactivated, Transformer ON, LED ON.");
    }

    delay(5000); // Avoid rapid relay switching
}

void sendWhatsAppMessage(String message, String photoUrl) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String serverPath = serverName + message + "&photo=" + photoUrl;
        serverPath.replace(" ", "%20");
        Serial.println(serverPath);
        
        http.begin(serverPath.c_str());
        int httpResponseCode = http.GET();
        if (httpResponseCode > 0) {
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);
            String payload = http.getString();
            Serial.println(payload);
        } else {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }
        http.end();
    } else {
        Serial.println("WiFi Disconnected");
    }
}


