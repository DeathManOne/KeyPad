# KeyPad for ESP32

Simple and lightweight keypad library for ESP32.

Supports:

* 4x3 matrix keypads
* 4x4 matrix keypads
* timeout handling
* key release handling
* configuration validation

Compatible with Arduino framework and PlatformIO.

---

# Features

* 4x3 and 4x4 keypad support
* Dynamic keypad layout detection
* Timeout protection
* Debounce and release handling
* Simple blocking API
* ESP32 optimized

---

# Installation

## PlatformIO

Add in `platformio.ini`:

```ini
lib_deps =
    https://github.com/DeathManOne/KeyPad.git
```

## Arduino IDE

Clone or download the repository into your `libraries` folder.

---

# Supported layouts

## 4x4 keypad

```text
1 2 3 A
4 5 6 B
7 8 9 C
* 0 # D
```

## 4x3 keypad

```text
1 2 3
4 5 6
7 8 9
* 0 #
```

---

# Initialization

```cpp
#include <Arduino.h>
#include <keypad.h>

KeyPad *keypad;

void setup() {
    keypad = new KeyPad(
        {21, 22, 23},
        {15, 16, 17, 18}
    );
}
```

---

# Constructor

```cpp
KeyPad(std::vector<int> pinsColumns,
       std::vector<int> pinsRows);
```

## Parameters

| Parameter     | Description                           |
| ------------- | ------------------------------------- |
| `pinsColumns` | GPIO pins connected to keypad columns |
| `pinsRows`    | GPIO pins connected to keypad rows    |

---

# Valid configurations

The library supports only:

| Layout | Columns | Rows |
| ------ | ------- | ---- |
| 4x3    | 3       | 4    |
| 4x4    | 4       | 4    |

Invalid configurations automatically disable keypad reading.

---

# Methods

---

# Check configuration

```cpp
if (keypad->isValid())
    { Serial.println("KeyPad valid"); }
else { Serial.println("Invalid KeyPad configuration"); }
```

---

# Wait for key press

```cpp
int key = keypad->getKey();
```

Default timeout:

```text
10 seconds
```

---

# Custom timeout

```cpp
int key = keypad->getKey(5);
```

Timeout here:

```text
5 seconds
```

---

# Return values

## Valid key

```cpp
'A'
'1'
'0'
'#'
```

## Error or timeout

```cpp
-1
```

---

# Examples

## Simple example

```cpp
#include <Arduino.h>
#include <keypad.h>

KeyPad keypad(
    {21, 22, 23},
    {15, 16, 17, 18}
);

void setup() {
    Serial.begin(115200);
}

void loop() {
    int key = keypad.getKey();

    if (key == -1)
        { return; }

    Serial.printf("Pressed: %c\n", key);
}
```

---

## Detect specific key

```cpp
int key = keypad.getKey();

if (key == 'A')
    { Serial.println("A pressed"); }

if (key == '#')
    { Serial.println("# pressed"); }

if (key == '0')
    { Serial.println("0 pressed"); }
```

---

# Timeout example

```cpp
int key = keypad.getKey(3);

if (key == -1)
    { Serial.println("Timeout"); }
```

---

# Notes

* The library is designed for ESP32.
* GPIO stabilization delays are automatically handled.
* Key release is automatically detected.
* Only one key can be pressed at the same time.
* Returned keys use ASCII values.

---

# License

GNU GPL v3 or later.
