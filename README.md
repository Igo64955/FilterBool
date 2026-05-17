# FilterBool

Header-only C++ moving-average debounce filter for digital (boolean) signals.

## Class: `BoolFilter<SIZE>`

| Method | Description |
|---|---|
| `BoolFilter()` | Default constructor. Ring buffer zeroed. |
| `void setup(int initialValue)` | Fill the entire ring buffer with `initialValue` (call once on startup). |
| `void setWert(int wert)` | Push a new sample (0 or 1) into the ring buffer. |
| `bool getWert()` | Returns `true` when the buffer mean < 0.5 (signal mostly LOW), `false` otherwise. |

The template parameter `SIZE` (default **15**) controls the ring-buffer depth.

## Arduino example

```cpp
#include "BoolFilter.hpp"

const int PIN = 8;
BoolFilter<15> filter;

void setup() {
    filter.setup(digitalRead(PIN));
}

void loop() {
    filter.setWert(digitalRead(PIN));
    bool pressed = filter.getWert();
}
```

## Notes

* Fixes an off-by-one buffer overrun present in the original procedural code
  (`filterPos > filterSize` → `filterPos >= SIZE - 1`).
* No dynamic allocation — safe for embedded/Arduino targets.