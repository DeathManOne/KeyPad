
# KeyPad 4x4 (or 4x3) for arduino, ESP32
- Does it works with RaspberryPi ?
## Initialization
```c++
#include <keypad.h>
KeyPad *_KEYPAD;
std::vector<int> _KEYPAD_PINS_COLUMNS = {6,7,8,9}
std::vector<int> _KEYPAD_PINS_ROWS = {2,3,4,5}

void setup() {
  _KEYPAD = new KeyPad(_KEYPAD_PINS_COLUMNS, _KEYPAD_PINS_ROWS);
}
```

## Delete
```c++a
delete _KEYPAD;
```

## Commands
#### Get pushed key
```c++
int maxWaitTime = 10;
char tapedKey = _KEYPAD->getKey(maxWaitTime);

if (tapedKey)
  { Serial.println(c); }
else { Serial.println("Timeout"); }
```
