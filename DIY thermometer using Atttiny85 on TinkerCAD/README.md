
# Thermometer using ATtiny85 Microcontroller 🌡️
This project demonstrates how to build a compact digital thermometer using the ultra-low-power ATtiny85 microcontroller and an LM35 temperature sensor. Based on the sensed temperature, an LED provides visual feedback using different blink patterns — a simple and efficient solution for minimal-display or wearable applications.


# 🔧 Required Components
ATtiny85 microcontroller

LM35 Temperature Sensor (or compatible analog sensor)

LED

Resistor (220Ω or 330Ω)

Jumper wires

Breadboard or minimal circuit board

USBasp programmer (or similar, to upload code to ATtiny85)
# 💡 How It Works
# 🔍 Analog Temperature Sensing
The LM35 sensor is connected to analog pin A1 (PB2) of the ATtiny85.

It outputs an analog voltage: 10mV per °C.
# 🔢 Temperature Conversion
The analog input is converted into voltage.

Voltage is translated to temperature in Celsius and then to Fahrenheit using:

Temp (°C) = (Voltage - 0.5) * 100  

Temp (°F) = (Temp °C * 9 / 5) + 32
# 🚨 LED Blink Patterns Based on Temperature
<img width="571" height="243" alt="Image" src="https://github.com/user-attachments/assets/79d2299e-d35a-4a95-a137-45061afdeab1" />


This system allows users to quickly gauge the temperature without a display.
# ⚙️ Working Principle
The ATtiny85 reads analog voltage from the LM35.

After conversion and calibration, the program checks the range and updates LED behavior.

No external display is needed — LED blinks give instant feedback.

Great for ultra-low-power environments and wearable tech.
# 📦 Applications
Basic environmental temperature monitoring

Wearables or compact gadgets

Display-less sensor nodes

Educational microcontroller projects

Low-cost room or outdoor thermometers
# 🏷️ Hashtags
# #ATtiny85 #Arduino #Thermometer #TemperatureSensor #EmbeddedSystems #MinimalElectronics #DIYProjects #LM35 #Microcontroller #LowPowerDevices #BlinkPattern #ArduinoProjects

