# Arduino IR Passage Counter — V1

An Arduino Uno project that counts entries into an infrared obstacle sensor's detection area and reports each event with a timestamp over USB serial.

This project demonstrates digital inputs, state tracking, edge detection, and structured serial output. It uses one reflective IR sensor; it does not measure distance or identify the direction of travel.

## V1 features

- Count a new event only when the input changes from HIGH (clear) to LOW (detected).
- Keep the count unchanged while an object remains detected.
- Send one CSV row per event: `time_ms,count`.
- Use Arduino uptime in milliseconds for the timestamp.

## Hardware and wiring

- Arduino Uno or compatible 5 V board
- Three-pin digital IR obstacle sensor, active-low output
- Breadboard, jumper wires, and a USB data cable

Disconnect USB power while changing the wiring. Follow the labels on your module; pin order can differ between modules.

| Sensor pin | Arduino Uno pin | Purpose |
| --- | --- | --- |
| VCC | 5V | Sensor power |
| GND | GND | Shared ground |
| OUT | 2 | Digital input |

The Uno pin marked `2` is the digital pin often called `D2`. On a standard breadboard, put each sensor pin in a separate numbered row and connect its jumper within the same connected group of five holes.

## Run the sketch

1. Keep the `ir_passage_counter` folder and `ir_passage_counter.ino` filename together; their names must match.
2. Open `ir_passage_counter/ir_passage_counter.ino` in Arduino IDE.
3. Select the Arduino Uno board and the port assigned to the connected board.
4. Upload the sketch. No additional Arduino libraries are required.
5. Open Serial Monitor at **9600 baud**.
6. Start with the detection area clear, then move an object into it, remove it, and repeat.

The monitor stays blank until the first detected entry. If necessary, adjust the sensor's threshold trimmer while watching its detection indicator.

## Serial output

The sketch sends two decimal integers separated by a comma. It does **not** send a header or regular samples between events.

Illustrative output (not a recorded measurement):

```csv
2450,1
5130,2
8020,3
```

| Field | Meaning |
| --- | --- |
| `time_ms` | Milliseconds since the Arduino sketch started |
| `count` | Total detected entries since startup |

`millis()` is not a clock date or a computer timestamp. The timestamp and counter restart when the board resets. Opening a serial connection can reset an Uno. Only one program should open the serial port at a time: close Serial Monitor before connecting Python or MATLAB.

A Python or MATLAB reader must split each line at the comma and parse **both** values. A reader written for the previous potentiometer project, which expects one integer per line, needs to be adapted.


- Reflectivity, object angle, ambient light, and the threshold setting affect detection.
- One sensor cannot determine travel direction or guarantee that each detection corresponds to a different object.
- On an Uno, `millis()` wraps after approximately 49.7 days.

Possible next versions: stable-state filtering, time between events, and Python/MATLAB CSV logging and plots.
