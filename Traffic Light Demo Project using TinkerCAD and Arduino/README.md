
# 🚦 Traffic Light System using Arduino
This project simulates a simple Traffic Light System using an Arduino and a push button. When the button is pressed, it initiates a sequence of red, yellow, and green LEDs representing "Stop," "Get Ready," and "Go" signals. The system resets after each cycle and waits for another button press.
# 🧰 Required Components
Arduino board (e.g., Uno, Mega)

Red LED

Yellow LED

Green LED

Push button

Resistors:

3 × 220Ω (for LEDs)

1 × 10kΩ (for button)

Breadboard & Jumper wires
# ⚙️ How It Works
The system stays idle until the button is pressed.

When the button is pressed, the following LED sequence runs:

🔴 Red LED turns on for 2 seconds — "Stop"

🟡 Yellow LED turns on for 2 seconds — "Get Ready"

🟢 Green LED turns on for 2 seconds — "Go"

After the cycle, all LEDs turn off, and the system waits for the next button press.
# 🔍 Working Principle
The push button is connected to a digital input pin and monitored in the loop().

When pressed, the program triggers a sequential LED pattern using:

digitalWrite() to control LED states.

delay() to manage timing.

The Serial Monitor prints status messages using Serial.print() to indicate the current traffic light state.
# 🏷️ Hashtags
# #Arduino #TrafficLight #EmbeddedSystems #IoT #LEDControl #SmartCity #Automation #ArduinoProjects #CProgramming #Electronics

