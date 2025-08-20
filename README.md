# Smart Home & Security System  

This project demonstrates the design and implementation of a **smart home automation and security system** using **ESP32 microcontrollers**.  
It combines **environmental monitoring, video surveillance, and access authentication** into one integrated solution with a local **Flask-based web dashboard**.  

The goal is to create a **cost-effective, modular, and scalable IoT system** that improves comfort, safety, and security at home.  

---

## 🔍 Project Overview  

Modern smart homes aim to make daily life more **convenient, safe, and energy-efficient**.  
This project focuses on:  

- Real-time **monitoring of environmental conditions** (temperature, humidity, gas, light).  
- A **secure keypad + servo motor lock** for access control.  
- A **live ESP32-CAM stream** for indoor/outdoor surveillance.  
- A **Python Flask dashboard** that collects, visualizes, and serves all system data locally.  

---

## 🛠️ System Architecture  

The system consists of **three major subsystems**, all interconnected:  

### 1. Environmental Monitoring Node  
- **Hardware**: ESP32 + DHT11 (temperature & humidity), MQ-2 (butane gas), LDR (light sensor).  
- **Function**: Collects sensor readings every few seconds.  
- **Communication**: Sends data to the Flask server over **Bluetooth (Serial via PySerial)**.  

### 2. Authentication & Access Control Node  
- **Hardware**: ESP32 + 4x4 Keypad + Servo Motor.  
- **Function**:  
  - Users enter a **username-password combination**.  
  - On success, servo unlocks the system.  
  - On failure, access is denied and can be logged for security analysis.  
- **Predefined Users**:  
  - User A → `a / 123`  
  - User B → `b / 456`  
  - User C → `c / 789`  

### 3. Video Surveillance Node  
- **Hardware**: ESP32-CAM with OV2640 module.  
- **Function**: Provides **live video stream** accessible via a fixed IP address.  
- **Integration**: Video feed embedded directly into the Flask dashboard.  

### 4. Server & Dashboard  
- **Software**: Python Flask + HTML/CSS/JS  
- **Functions**:  
  - Receive and log sensor data (`data.csv`).  
  - Serve dashboard with **real-time sensor values** and **historical graphs**.  
  - Embed ESP32-CAM stream.  
  - Provide an **information page** about the system.  

---

## 🧩 Implementation Details  

- **ESP32 Code**: Written in Arduino IDE (C++). Each ESP32 node has its own program.  
- **Python Flask Server**:  
  - Uses **PySerial** for Bluetooth communication.  
  - Stores incoming data into a CSV file.  
  - Updates the web interface every ~30s with latest sensor values.  
- **Web Dashboard**:  
  - Built with Flask templates (`templates/` folder).  
  - Includes graphs, live values, and video stream integration.  
  - Optimized with Bootstrap for responsive display.  

---

## 📊 Results  

- **Sensor Readings Example** (during testing):  
  - Temperature: 29.7 °C  
  - Humidity: 52.5 %  
  - Gas (butane): 18 %  
  - Light intensity: 73 units  

- **Authentication**:  
  - Correct username-password successfully triggered the servo lock.  
  - Incorrect attempts were ignored, ensuring basic security.  

- **Video Stream**:  
  - Accessible on local IP.  
  - Clear visuals with minimal latency.  

## ⚡ Getting Started  

### 🔧 Requirements  
- Hardware:  
  - 2 × ESP32 Dev Boards  
  - 1 × ESP32-CAM Module (OV2640)  
  - DHT11 Sensor  
  - MQ-2 Gas Sensor  
  - LDR Sensor  
  - 4x4 Keypad  
  - Servo Motor  
- Software:  
  - Arduino IDE with ESP32 boards installed  
  - Python 3.x with:  
    ```bash
    pip install flask pyserial
    ```
