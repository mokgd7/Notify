# **Project Summary: IoT WhatsApp Notification System**


## **1. Project Overview**
This project aims to bridge mobile software triggers with physical hardware feedback. Using **MacroDroid** on an Android device and an **ESP32 microcontroller**, the system detects incoming WhatsApp notifications and sends a real-time HTTP request to the ESP32. The hardware then provides visual feedback on an **OLED Display** (showing the message count) and audible feedback via a **Buzzer**.

## **2. Key Features & Capabilities**
* **Real-time Synchronization:** Instant physical notification upon receiving a mobile message.
* **Dynamic Counter:** An internal logic that tracks notifications and automatically resets after 5 messages to maintain system efficiency.
* **Custom Typography:** Integration of professional fonts (*FreeSansBold*) for a polished UI on the OLED screen.
* **Power Optimization:** Configured to run at 80MHz (CPU Frequency Scaling) to reduce heat and power consumption without sacrificing response time.
* **Aesthetic UI:** Multi-size text rendering and precise coordinate mapping for a clean layout.

## **3. Hardware Components (Bill of Materials)**
1.  **ESP32 Development Board:** The core Wi-Fi-enabled microcontroller.
2.  **OLED Display (SSD1306, 128x64):** For visual output using the I2C protocol.
3.  **Active/Passive Buzzer:** For acoustic signaling.
4.  **Breadboard & Jumper Wires:** For circuit prototyping.
5.  **Micro-USB Cable:** For power supply and firmware uploading.

## **4. Wiring Diagram & Connections**
The components are wired to prioritize "Single-Side" board management for a cleaner setup:
* **OLED Display (I2C):**
    * VCC -> 3.3V
    * GND -> GND
    * SCL -> GPIO 22
    * SDA -> GPIO 21
* **Buzzer:**
    * Positive (+) -> **GPIO 4
    * Negative (-) -> GND

## **5. MacroDroid Configuration (Software Logic)**

The automation is built on a **Trigger-Action** architecture with a local variable to handle data transmission.

### **A. Variable Setup**
* **Variable Name:** `n`
* **Type:** Integer
* **Scope:** Local (within the macro)

### **B. Trigger**
* **Trigger Type:** Notification Received.
* **Parameters:** Select "WhatsApp" as the target application. *Optional: Filter by specific contacts or keywords.*

### **C. Actions (Sequential Order)**
To ensure the correct value is sent, the order of actions is critical:

1.  **Set Variable (Variable Update):**
    * **Logic:** `n = n + 1`
    * **Expression:** Use the expression `{lv=n} + 1` to increment the local variable every time a notification is intercepted.
2.  **HTTP Request (Data Transmission):**
    * **Method:** GET
    * **URL:** `http://[ESP32_IP_ADDRESS]/notify?count={lv=n}`
    * **Description:** This action sends the current value of `n` to the ESP32 server. The `{lv=n}` tag acts as a placeholder that MacroDroid replaces with the actual numerical value before sending the packet.

### **D. Macro Logic Flow**
* **Event:** WhatsApp Message -> **Trigger** fires.
* **Process:** MacroDroid increments the local counter `n`.
* **Output:** MacroDroid executes a GET request to the local IP of the ESP32.
* **Hardware Response:** The ESP32 server receives the `count` argument, triggers the double-beep sequence, and updates the OLED display with the formatted "WhatsApp / Message(s) : X" layout.

---
