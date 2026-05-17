#pragma once

// BoolFilter – moving-average debounce filter for a digital (boolean) signal.
//
// Usage (Arduino example):
//   BoolFilter<15> filter;
//   void setup() { filter.setup(digitalRead(8)); }
//   void loop()  { filter.setWert(digitalRead(8));
//                  bool pressed = filter.getWert(); }
//
// Template parameter SIZE sets the ring-buffer depth (default 15).

template<int SIZE = 15>
class BoolFilter {
public:
    BoolFilter() : filterPos(0) {
        for (int i = 0; i < SIZE; i++) {
            buf[i] = 0;
        }
    }

    // Fill the entire ring buffer with the given initial value.
    void setup(int initialValue) {
        for (int i = 0; i < SIZE; i++) {
            buf[i] = initialValue;
        }
        filterPos = 0;
    }

    // Push a new sample into the ring buffer.
    void setWert(int wert) {
        if (++filterPos >= SIZE) {
            filterPos = 0;
        }
        buf[filterPos] = wert;
    }

    // Return the averaged boolean value (inverted).
    // Returns true  when the buffer mean < 0.5  (signal mostly LOW / button pressed).
    // Returns false when the buffer mean >= 0.5 (signal mostly HIGH / button released).
    bool getWert() const {
        float summe = 0.0f;
        for (int i = 0; i < SIZE; i++) {
            summe += static_cast<float>(buf[i]);
        }
        return (summe / SIZE) < 0.5f;
    }

private:
    int buf[SIZE];
    int filterPos;
};
