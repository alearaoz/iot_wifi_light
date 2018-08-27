#include <Arduino.h>
#include <Boton.h>

void Boton::begin() {
    pinMode(_pin, INPUT_PULLUP);
    _state = digitalRead(_pin);
}

bool Boton::isReleased() {
    bool v = digitalRead(_pin);
    if (v != _state) {
        _state = v;
        if (_state) {
            return true;
        }
    }
    return false;
}
