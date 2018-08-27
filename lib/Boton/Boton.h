#include <Arduino.h>

class Boton {
    private:
        bool _state;
        int _pin;

    public:
        Boton(int pin) : _pin(pin) {};
        void begin();
        bool isReleased();
};
