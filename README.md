# Integrated Environmental Monitoring and Control System

## Project Description
This project is a monitoring system based on the **PIC16F887** microcontroller. It integrates multiple industrial communication protocols and peripheral controllers to establish a local control loop along with remote monitoring capabilities.

### 🔧 Key Technical Features
* **Real-Time Clock (RTC):** An **RTC 1307** clock module was implemented using **I2C** with a custom interactive menu for setting the date and time via a matrix keypad.

* **Thermal Management:** Integrated temperature sensors (**LM75**) with automatic fan speed control via **PWM** modulation based on real-time environmental thresholds.

* **Dual Interface Communication:** A dual interface was designed with a local **LCD display** and **RS232 (UART)** serial communication for remote monitoring and data logging from a PC.

* * **Control Interface:** An intuitive menu system was programmed, controlled by both the physical **matrix keypad** and remote **serial commands**.

--

## System Architecture and Circuit Diagram

Here you can see the microcontroller's connections to the peripherals (LCD, keyboard, RTC, sensors, and actuators):

![System Architecture](./Project.png)

---

## Repository Structure
```text
Project-pic16f887/
├── src/ # Main application source code (PROJECT.c)
├── drivers/ # Hardware peripheral drivers (.c and .h files)
├── build/ # Compiled files (.hex and mikroC project files)
└── Project.png # System diagram image
