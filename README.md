###### [(ระบบนี้ Transfer มาจาก Github Account เก่า --> https://github.com/TOEYJIRAKIT/IOT-MiniProject)](https://github.com/TOEYJIRAKIT/IOT-MiniProject)

## 🚀 **Project Name** :

Attendance System – Attendance Notification System (Smart School Entry)

## 📌 **Project Overview** :

Attendance Notification System (Smart School Entry) is an IoT-based that utilizes RFID and Arduino to efficiently track student check-ins and check-outs. Traditional attendance methods often face issues such as lost paper records, delayed updates, and lack of real-time notifications for parents. This system enhances student security and improves school management by providing real-time attendance tracking, web-based monitoring, and instant notifications via LINE Notify.

## 🎯 **Objective** :

- Develop a system to record student check-in and check-out data and display it on a website.  
- Implement a notification system that sends attendance alerts to parents via LINE Notify.

## ✨ **Key Features** :

- **RFID-Based Check-in System** – Uses RFID to log student attendance.
- **Web Dashboard** – Displays student attendance records.
- **LINE Notify Integration** – Sends real-time attendance notifications to parents.
- **Basic Data Logging** – Stores and retrieves attendance records in JSON format.

## 💻 **Development Details** :

### **Hardware Components**
- **Arduino UNO+WiFi R3 ATmega328P+ESP8266 Web Server** – Used for reading sensor data and connecting components.
- **RFID Sensor** – Reads student ID cards.
- **OLED Display** – Displays scanned card details.
- **Jumper Wires** – Connects sensors to the microcontroller.
- **Key Tag** – Used for scanning and sending data.

### **Programming Languages**
- **C** – Programs the microcontroller to read and send data.
- **JSON** – Stores and transfers data via JSON Server.
- **JavaScript** – Retrieves data from JSON Server for display.
- **HTML & CSS** – Designs the web interface for attendance monitoring.

### **Libraries Used**
- SPI.h – Serial Peripheral Interface communication.
- Wire.h – I2C communication for RFID module.
- Adafruit_GFX.h – Graphics library for OLED display.
- Adafruit_SSD1306.h – OLED control library.
- MFRC522.h – RFID card reader library.
- ESP8266WiFi.h – WiFi connection for ESP8266.
- NTPClient.h – Synchronizes time with NTP server.
- WiFiUdp.h – Handles UDP communication.
- PubSubClient.h – MQTT protocol for message transmission.
- TridentTD_LineNotify.h – Sends notifications via LINE Notify API.

## 📂 **GitHub Repository (Source Code)** :

- [https://github.com/TOEYJIRAKID/Attendance-System-IOT](https://github.com/TOEYJIRAKID/Attendance-System-IOT)

## ⚙️ **Installation & Setup** :

1. **Clone the repository**  
   ```bash
   git clone https://github.com/TOEYJIRAKID/Attendance-System-IOT.git
   ```  
2. **Install json-server**  
   ```bash
   npm install json-server
   ```  
3. **Run the JSON Server**  
   ```bash
   npx json-server data.json --watch --port 3000
   ```  
4. **Open http://localhost:3000/users to view the json data.**

## 🏗️ **System Architecture** :

### **Collect Layer**  
- **RFID Sensor & Arduino UNO**: Reads student ID cards and sends data to **NodeMCU**  
- **NodeMCU 1.0**: Transfers the data to the processing server  

### **Process Layer**  
- **MQTT**: Transfers data between devices and the server  
- **Flask API**: Processes data and communicates with the web interface  
- **JSON Server**: Stores student attendance records  

### **Frontend Layer**  
- **Web Dashboard**: Displays attendance data in real-time  
- **LINE Notify**: Sends check-in and check-out alerts to parents  
- **OLED Display**: Shows attendance status on-site  

![System Architecture](https://github.com/TOEYJIRAKIT/IOT-MiniProject/assets/110581279/b21fff0b-52df-42eb-b967-e8df4bcfc9d8)

## 🖥️ **Software Architecture** :

### **Collect Layer**  
- **Arduino UNO WiFi**: Reads data from the RFID sensor  
- **NodeMCU 1.0**: Sends student data to the MQTT broker  

### **Process Layer**  
- **MQTT**: Transfers data to the Flask server  
- **Flask API**: Stores and retrieves data from the **JSON Server**  
- **JSON Server**: Stores attendance records  

### **Frontend Layer**  
- **Web Dashboard**: Displays attendance records  
- **LINE Notify**: Sends notifications to parents  
- **OLED Display**: Shows attendance status  

![Software Architecture](https://github.com/TOEYJIRAKIT/IOT-MiniProject/assets/110581279/27c4a44d-e4de-4dcf-af2b-b90ca1ab6e14)

## 🏛️ **Database Structure** :

| Attribute   | Description             | Data Type | Example       |  
|------------|-------------------------|-----------|--------------|  
| uid        | Unique user ID           | String    | 2            |  
| studentid  | Student ID               | String    | 64125735     |  
| firstname  | First name               | String    | Thanawat     |  
| lastname   | Last name                | String    | Kongsisang   |  
| position   | Role                     | String    | Student      |  
| timestamp  | Time of check-in/out      | String    | 20:15:43     |  
| status     | Attendance status        | String    | Check-in     |  
| id         | Record ID                 | Int       | 1            |  

## 📃 Example JSON Data :
The attendance data is stored in **JSON format**, containing student details such as **ID, name, position, timestamp, and status**.

```json
{
  "users": [
    {
      "uid": "2",
      "studentid": "64125735",
      "firstname": "Thanawat",
      "lastname": "Kongsisang",
      "position": "Student",
      "timestamp": "20:15:40",
      "status": "Check-in",
      "id": 1
    },
    {
      "uid": "3",
      "studentid": "64102080",
      "firstname": "Jirakit",
      "lastname": "Iadhet",
      "position": "Student",
      "timestamp": "20:15:43",
      "status": "Check-out",
      "id": 2
    }
  ]
}
```

## 🧑‍🔬 **Testing Scenarios** :

### **Scenario 1 : Scanning a Registered RFID Card**
- **Independent Variable:** A card with registered student data.
- **Dependent Variable:** Data is read and displayed correctly.
- **Control Variables:** RFID Sensor, OLED Display, Key Tag.
- **Result:** ![Test Image](https://github.com/TOEYJIRAKIT/IOT-MiniProject/assets/110581279/937fa408-c1ff-4490-8df2-835b1f327a6c)

### **Scenario 2 : Scanning an Unregistered RFID Card**
- **Independent Variable:** A card not registered in the system.
- **Dependent Variable:** No data is displayed or stored.
- **Control Variables:** RFID Sensor, OLED Display, Key Tag.
- **Result:** ![Test Image](https://github.com/TOEYJIRAKIT/IOT-MiniProject/assets/110581279/c837699d-fabb-4724-983b-86ad8e897e8e)

## 📽️ **Project Preview** :
https://github.com/TOEYJIRAKID/personal_gif_public/blob/main/attendance.gif
