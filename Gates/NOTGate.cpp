/*
** EPITECH PROJECT, 2023
** NOTGate
** File description:
** NOTGate
*/

#include "NOTGate.hpp"

nts::NOTGate::NOTGate()
{
    addPin(1);
    addPin(2);
    addPin(3);
    addPin(4);
    addPin(5);
    addPin(6);
    addPin(8);
    addPin(9);
    addPin(10);
    addPin(11);
    addPin(12);
    addPin(13);
}

nts::NOTGate::~NOTGate() {}

nts::Tristate nts::NOTGate::compute(std::size_t pin)
{
    if (pin == 7)
        throw nts::Error("Cannot compute pin 7");
    if (pin < 1 || pin > 13)
        throw nts::Error("Pin not found");
    if (pin == 2) { // Output of the NOT Component
        bool oneOrBothPinsNotLinked = _pins[1].first == nullptr;
        nts::Tristate pin1Value = _pins[1].first ? _pins[1].first->compute(_pins[1].second) : UNDEFINED;
        if (oneOrBothPinsNotLinked)
            return UNDEFINED;
        if (pin1Value == TRUE)
            return FALSE;
        if (pin1Value == UNDEFINED)
            return UNDEFINED;
        return TRUE;
    } else if (pin == 4) { // Output of the NOT Component
        bool oneOrBothPinsNotLinked = _pins[3].first == nullptr;
        nts::Tristate pin3Value = _pins[3].first ? _pins[3].first->compute(_pins[3].second) : UNDEFINED;
        if (oneOrBothPinsNotLinked)
            return UNDEFINED;
        if (pin3Value == TRUE)
            return FALSE;
        if (pin3Value == UNDEFINED)
            return UNDEFINED;
        return TRUE;
    } else if (pin == 6) { // Output of the NOT Component
        bool oneOrBothPinsNotLinked = _pins[5].first == nullptr;
        nts::Tristate pin5Value = _pins[5].first ? _pins[5].first->compute(_pins[5].second) : UNDEFINED;
        if (oneOrBothPinsNotLinked)
            return UNDEFINED;
        if (pin5Value == TRUE)
            return FALSE;
        if (pin5Value == UNDEFINED)
            return UNDEFINED;
        return TRUE;
    } else if (pin == 8) { // Output of the NOT Component
        bool oneOrBothPinsNotLinked = _pins[9].first == nullptr;
        if (oneOrBothPinsNotLinked)
            return UNDEFINED;
        nts::Tristate pin9Value = _pins[9].first ? _pins[9].first->compute(_pins[9].second) : UNDEFINED;
        if (pin9Value == TRUE)
            return FALSE;
        if (pin9Value == UNDEFINED)
            return UNDEFINED;
        return TRUE;
    } else if (pin == 10) { // Output of the NOT Component
        bool oneOrBothPinsNotLinked = _pins[11].first == nullptr;
        nts::Tristate pin11Value = _pins[11].first ? _pins[11].first->compute(_pins[11].second) : UNDEFINED;
        if (oneOrBothPinsNotLinked)
            return UNDEFINED;
        if (pin11Value == TRUE)
            return FALSE;
        if (pin11Value == UNDEFINED)
            return UNDEFINED;
        return TRUE;
    } else if (pin == 12) { // Output of the NOT Component
        bool oneOrBothPinsNotLinked = _pins[13].first == nullptr;
        nts::Tristate pin13Value = _pins[13].first ? _pins[13].first->compute(_pins[13].second) : UNDEFINED;
        if (oneOrBothPinsNotLinked)
            return UNDEFINED;
        if (pin13Value == TRUE)
            return FALSE;
        if (pin13Value == UNDEFINED)
            return UNDEFINED;
        return TRUE;
    } else {
        if (_pins[pin].first == nullptr)
            return UNDEFINED;
        return _pins[pin].first->compute(_pins[pin].second);
    }
}
