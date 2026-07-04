# ⚡ Smart Transformer Health Monitoring System

A real-time IoT-based transformer monitoring system that continuously monitors transformer health by measuring **voltage**, **oil temperature**, and **oil level**. The system sends instant Telegram alerts whenever abnormal conditions are detected and automatically disconnects the transformer using a relay module during critical overheating conditions.

---

## 📌 Overview

Power transformers are critical components in electrical distribution systems. Traditional transformer inspection relies on manual monitoring, which can delay fault detection and increase maintenance costs.

This project automates transformer health monitoring using an **ESP32** and multiple sensors to provide real-time condition monitoring, remote notifications, and automatic protection against failures.

---

## ✨ Features

- 📊 Real-time voltage monitoring
- 🌡️ Oil temperature monitoring
- 🛢️ Oil level monitoring using an ultrasonic sensor
- 📲 Instant Telegram notifications
- ⚠️ Low voltage and overheating alerts
- 🔌 Automatic transformer shutdown using a relay module
- 📡 Wireless monitoring over Wi-Fi
- 💰 Reduces manual inspection and maintenance cost

---

## 🛠 Hardware Components

- ESP32 Development Board
- ZMPT101B AC Voltage Sensor
- DS18B20 Temperature Sensor
- HC-SR04 Ultrasonic Sensor
- 5V Relay Module
- LM1117 & 7805 Voltage Regulators
- 12-0-12 Step Down Transformer
- Rectifier Circuit
- AC Power Supply

---

## 💻 Software & Technologies

- Arduino IDE
- Embedded C++
- ESP32 Wi-Fi Library
- HTTPClient Library
- DallasTemperature Library
- OneWire Library
- Telegram Bot API
- Cirkit Designer (Circuit Simulation)

---

## 🏗 System Architecture

```
                 AC Supply
                     │
             Step Down Transformer
                     │
                 Rectifier
                     │
        ┌────────── ESP32 ──────────┐
        │            │              │
 Voltage Sensor  Temperature   Ultrasonic
 (ZMPT101B)        Sensor        Sensor
        │            │              │
        └────────────┼──────────────┘
                     │
              Data Processing
                     │
        ┌────────────┴────────────┐
        │                         │
 Telegram Bot               Relay Module
 (Alerts)              (Automatic Shutdown)
```

---

## ⚙️ Working

1. The ESP32 continuously reads:
   - Transformer voltage
   - Oil temperature
   - Oil level

2. Sensor data is processed in real time.

3. When abnormal conditions are detected:
   - Telegram alerts are sent immediately.
   - The relay disconnects the transformer if overheating occurs.

4. Users can remotely monitor transformer health through Telegram notifications.

---

## 🚨 Alert Conditions

| Parameter | Condition | Action |
|-----------|-----------|--------|
| Voltage | Below safe threshold | Low Voltage Alert |
| Temperature | Above 50°C | High Temperature Alert + Relay Shutdown |
| Oil Level | Medium/Low | Telegram Warning |

---

## 📸 Sample Alerts

- ⚠️ Voltage is Low
- 🔥 Temperature is High
- 🛢️ Oil Level is Medium
- 🛢️ Oil Level is Low

---

## 📂 Project Structure

```
Smart-Transformer-Monitoring/
│
├── Arduino_Code/
│   └── transformer_monitoring.ino
│
├── Circuit_Diagram/
│   └── circuit.png
│
├── Images/
│   ├── block_diagram.png
│   ├── hardware_setup.png
│   └── telegram_alerts.png
│
├── Documentation/
│   └── Project_Report.pdf
│
└── README.md
```

---

## 🚀 Future Improvements

- Cloud-based data logging
- AI-based predictive maintenance
- Web dashboard for live monitoring
- Mobile application integration
- Historical analytics and visualization
- Multiple transformer monitoring support

---

## 📈 Outcomes

- Automated transformer monitoring
- Reduced manual inspections
- Improved transformer safety
- Instant fault notifications
- Preventive maintenance support
- Increased system reliability

---

## 🎯 Applications

- Electrical Substations
- Industrial Power Distribution
- Smart Grid Infrastructure
- Utility Companies
- Transformer Maintenance Systems

---

## 👨‍💻 Team

- Abhijith S Sanal
- Jayakrishnan V.B
- Nandana V.S
- Sumi S

**Guide:** Smt. Neethu Verjisen  
Assistant Professor  
Department of Electronics & Communication Engineering  
College of Engineering Chengannur

---

## 📚 References

- ESP32 Documentation
- Arduino Documentation
- Telegram Bot API
- Cirkit Designer
- DallasTemperature Library
- OneWire Library

---

## ⭐ If you found this project useful, consider giving it a Star!
