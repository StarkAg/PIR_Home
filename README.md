# 🏠 PIR Motion Sensor with Stadium Wave LED Effect

<div align="center">

![Arduino](https://img.shields.io/badge/Arduino-Uno-00979D?style=for-the-badge&logo=Arduino&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**A home automation project that detects motion using a PIR sensor and creates a mesmerizing stadium wave effect with LEDs**

[Features](#-features) • [Hardware](#-hardware-requirements) • [Setup](#-setup) • [Usage](#-usage) • [Demo](#-demo)

</div>

---

## 📖 About

This project combines a **PIR (Passive Infrared) motion sensor** with an **Arduino Uno** to create an interactive lighting system. When motion is detected, three LEDs perform a stadium-style wave effect, turning on sequentially and then turning off with a visible delay—perfect for home security, room lighting, or just a cool visual display!

### 🎯 Use Cases

- **Home Security**: Visual alert when motion is detected
- **Room Lighting**: Automatic light activation
- **Educational Project**: Learn about sensors, state machines, and Arduino programming
- **Visual Display**: Create an eye-catching LED animation

---

## ✨ Features

- 🎯 **Motion Detection**: Reliable PIR sensor (HC-SR501) with 3-7 meter range
- 🌊 **Stadium Wave Effect**: Sequential LED activation with customizable timing
- ⚙️ **Configurable**: Easy to adjust timing, pins, and number of LEDs
- 📊 **Serial Debugging**: Real-time status messages via serial monitor
- 🏗️ **State Machine Architecture**: Clean, maintainable code structure
- 🔧 **Arduino CLI Support**: No IDE required, compile and upload from terminal

---

## 🏠 Home Setup Visualization

### Physical Setup
```
    ┌─────────────────────────────────────────┐
    │         Home Setup View                 │
    │                                         │
    │    [PIR Sensor]                         │
    │      (Wall)                             │
    │       │                                 │
    │       │ Detects Motion                  │
    │       ▼                                 │
    │    ┌─────────────┐                      │
    │    │  Arduino    │                      │
    │    │    Uno      │                      │
    │    │             │                      │
    │    │  Pin 8  ────┼───► [LED 1] 🔴      │
    │    │  Pin 9  ────┼───► [LED 2] 🟡      │
    │    │  Pin 10 ────┼───► [LED 3] 🟢      │
    │    │  Pin 2  ◄───┼─── [PIR OUT]        │
    │    └─────────────┘                      │
    │                                         │
    │    When motion detected:                │
    │    🔴 → 🟡 → 🟢 (Wave ON)              │
    │    🔴🟡🟢 (All ON - 3 sec)            │
    │    🔴 → 🟡 → 🟢 (Wave OFF)             │
    └─────────────────────────────────────────┘
```

### Stadium Wave Effect Animation
```
Motion Detected! 🎉

STEP 1: Wave ON (200ms intervals)
    🔴          🟡          🟢
    ON  ────►  OFF ────►  OFF
    ON  ────►  ON  ────►  OFF
    ON  ────►  ON  ────►  ON

STEP 2: All ON (3 seconds)
    🔴🟡🟢
    ALL ON!

STEP 3: Wave OFF (300ms intervals)
    🔴          🟡          🟢
    OFF ────►  ON  ────►  ON
    OFF ────►  OFF ────►  ON
    OFF ────►  OFF ────►  OFF

Ready for next motion detection...
```

---

## 🛠️ Hardware Requirements

| Component | Quantity | Notes |
|-----------|----------|-------|
| Arduino Uno | 1× | Or compatible board |
| PIR Sensor (HC-SR501) | 1× | Motion detection sensor |
| LED (any color) | 3× | For stadium wave effect |
| 220Ω Resistor | 3× | One for each LED |
| Jumper Wires | ~10× | For connections |
| Breadboard | 1× | Optional, but recommended |
| USB Cable | 1× | For Arduino programming |

**Estimated Cost**: ~$15-25 USD

---

## 📐 Wiring Diagram

### Circuit Diagram (ASCII Art)
```
                    ┌─────────────────┐
                    │   Arduino Uno   │
                    │                 │
     PIR Sensor     │  5V ────────────┼───► VCC
    ┌──────────┐    │                 │
    │ HC-SR501 │    │  GND ───────────┼───► GND
    │          │    │                 │
    │  VCC ────┼────┼──► 5V           │
    │  GND ────┼────┼──► GND          │
    │  OUT ────┼────┼──► Pin 2        │
    └──────────┘    │                 │
                    │  Pin 8 ────[220Ω]───► LED 1 (+)
                    │                 │      │
                    │  Pin 9 ────[220Ω]───► LED 2 (+)
                    │                 │      │
                    │  Pin 10 ───[220Ω]───► LED 3 (+)
                    │                 │      │
                    │  GND ───────────┼──────┼──────┼──► LED (-)
                    │                 │      │      │
                    └─────────────────┘      │      │
                                             │      │
                                           [220Ω] [220Ω]
                                             │      │
                                            GND    GND
```

### Connection Table

| Component | Pin/Port | Arduino Connection |
|-----------|----------|-------------------|
| PIR Sensor | VCC | 5V |
| PIR Sensor | GND | GND |
| PIR Sensor | OUT | Digital Pin 2 |
| LED 1 | Anode (+) | Digital Pin 8 (via 220Ω resistor) |
| LED 1 | Cathode (-) | GND |
| LED 2 | Anode (+) | Digital Pin 9 (via 220Ω resistor) |
| LED 2 | Cathode (-) | GND |
| LED 3 | Anode (+) | Digital Pin 10 (via 220Ω resistor) |
| LED 3 | Cathode (-) | GND |

**⚠️ Important**: 
- Always use resistors (220Ω) with LEDs to prevent damage
- Check LED polarity (longer leg = anode/+)
- Ensure PIR sensor has 30-60 seconds to calibrate after power-on

---

## 🚀 Setup

### Prerequisites

1. **Install Arduino CLI**
   ```bash
   # macOS (using Homebrew)
   brew install arduino-cli
   
   # Linux
   curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
   
   # Windows (using Chocolatey)
   choco install arduino-cli
   ```

2. **Initialize Arduino CLI**
   ```bash
   arduino-cli config init
   arduino-cli core update-index
   arduino-cli core install arduino:avr
   ```

3. **Clone this repository**
   ```bash
   git clone https://github.com/yourusername/pir-motion-sensor.git
   cd pir-motion-sensor
   ```

### Upload to Arduino

1. **Find your Arduino port**
   ```bash
   arduino-cli board list
   # Look for something like: /dev/cu.usbmodemXXXX or COM3
   ```

2. **Compile and upload**
   ```bash
   # Create sketch directory (Arduino CLI requirement)
   mkdir -p pir_motion_sensor
   cp pir_motion_sensor.ino pir_motion_sensor/pir_motion_sensor.ino
   
   # Compile
   arduino-cli compile --fqbn arduino:avr:uno pir_motion_sensor
   
   # Upload (replace PORT with your actual port)
   arduino-cli upload -p /dev/cu.usbmodemXXXX --fqbn arduino:avr:uno pir_motion_sensor
   ```

3. **Or use the provided scripts**
   ```bash
   # Make scripts executable
   chmod +x upload.sh monitor.sh
   
   # Upload
   ./upload.sh /dev/cu.usbmodemXXXX
   
   # Monitor serial output
   ./monitor.sh
   ```

---

## 📊 Usage

### Serial Monitor

Open the serial monitor to see real-time status:
```bash
arduino-cli monitor -p /dev/cu.usbmodemXXXX -c baudrate=9600
```

### Expected Output
```
PIR Motion Sensor with Stadium Wave - Initialized
Calibrating PIR sensor... Please wait 30-60 seconds.
Calibration complete. Ready to detect motion!
Wave effect: LEDs will turn on in sequence (8->9->10)
Then turn off in sequence with visible delay.

Motion detected! Starting stadium wave...
LED 8 ON
LED 9 ON
LED 10 ON
All LEDs ON - Stadium wave complete!
LED 8 OFF - Starting wave off
LED 9 OFF
LED 10 OFF
All LEDs OFF - Ready for next motion detection
```

### Configuration

Edit `pir_motion_sensor.ino` to customize:

```cpp
// Pin configuration
const int PIR_PIN = 2;              // PIR sensor pin
const int LED_PINS[] = {8, 9, 10};  // LED pins
const int NUM_LEDS = 3;             // Number of LEDs

// Timing configuration
const unsigned long WAVE_ON_DELAY = 200;    // Delay between LEDs turning on (ms)
const unsigned long ALL_ON_DURATION = 3000; // All LEDs on duration (ms)
const unsigned long WAVE_OFF_DELAY = 300;   // Delay between LEDs turning off (ms)
```

---

## 🎬 Demo

### How It Works

1. **Initialization**: Arduino waits 30 seconds for PIR calibration
2. **Motion Detection**: PIR sensor detects movement (rising edge trigger)
3. **Wave ON**: LEDs turn on sequentially (200ms delay)
4. **All ON**: All LEDs stay on for 3 seconds
5. **Wave OFF**: LEDs turn off sequentially (300ms delay)
6. **Idle**: System waits for next motion detection

### State Machine
```
    IDLE
      │
      │ Motion Detected
      ▼
   WAVE_ON (8→9→10)
      │
      │ All LEDs ON
      ▼
    ALL_ON (3 seconds)
      │
      │ Duration Expired
      ▼
   WAVE_OFF (8→9→10)
      │
      │ All LEDs OFF
      ▼
    IDLE (waiting...)
```

---

## 🐛 Troubleshooting

### LEDs Don't Turn On
- ✅ Check LED polarity (longer leg = anode)
- ✅ Verify 220Ω resistors are connected
- ✅ Test LEDs individually (connect to 5V via resistor)
- ✅ Verify pins 8, 9, 10 are correctly wired
- ✅ Check if wave effect is working (should see sequential lighting)

### PIR Sensor Not Detecting Motion
- ✅ Wait 30-60 seconds after power-on for calibration
- ✅ Adjust sensitivity potentiometer on HC-SR501
- ✅ Check connections (VCC, GND, OUT)
- ✅ Move within detection range (3-7 meters)
- ✅ Ensure sensor has clear line of sight

### Upload Errors
- ✅ Check USB cable connection
- ✅ Verify correct port in upload command
- ✅ Close other programs using the serial port
- ✅ Try unplugging and replugging Arduino
- ✅ Install correct board drivers

### Serial Monitor Not Showing Output
- ✅ Verify baud rate is 9600
- ✅ Check correct port is selected
- ✅ Ensure Arduino is powered and connected
- ✅ Wait for calibration period to complete

---

## 🔧 Expanding the Project

### Possible Enhancements

- **More LEDs**: Add more LEDs to the wave (increase `NUM_LEDS`)
- **Reverse Wave**: Change direction (10→9→8)
- **RGB LEDs**: Use RGB LEDs for colorful effects
- **Multiple Waves**: Trigger multiple wave cycles
- **Audio Feedback**: Add buzzer synchronized with wave
- **OLED Display**: Show motion status and statistics
- **WiFi Integration**: ESP32 for remote monitoring
- **Relay Module**: Control larger devices (lights, fans)
- **Motion Counter**: Log and display motion count
- **Different Patterns**: Circular, back-and-forth waves
- **Web Interface**: Control via web dashboard
- **Mobile App**: Smartphone notifications

### Code Structure

```
pir_motion_sensor.ino
├── Pin Definitions
├── Timing Configuration
├── State Machine Enum
├── State Variables
├── setup()
│   ├── Serial initialization
│   ├── Pin configuration
│   └── Calibration delay
└── loop()
    ├── Motion detection
    └── State machine
        ├── IDLE
        ├── WAVE_ON
        ├── ALL_ON
        └── WAVE_OFF
```

---

## 📁 Project Structure

```
pir-motion-sensor/
├── pir_motion_sensor.ino    # Main Arduino sketch
├── README.md                 # This file
├── upload.sh                 # Upload script
├── monitor.sh                # Serial monitor script
└── .gitignore               # Git ignore file
```

---

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

---

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 🙏 Acknowledgments

- Arduino community for excellent documentation
- HC-SR501 PIR sensor manufacturers
- All contributors and testers

---

## 📧 Contact

For questions or suggestions, please open an issue on GitHub.

---

<div align="center">

**Made with ❤️ and Arduino**

⭐ Star this repo if you found it helpful!

</div>
