/*
** EPITECH PROJECT, 2025
** XORGate
** File description:
** XORGate
*/

#include "XORGate.hpp"

nts::XORGate::XORGate()
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

nts::XORGate::~XORGate() {}

nts::Tristate nts::XORGate::compute(std::size_t pin)
{
    if (pin == 7)
        throw nts::Error("Cannot compute pin 7");
    if (pin < 1 || pin > 13)
        throw nts::Error("Pin not found");
    if (pin == 3) { // Output of the XOR Component
        bool oneOrBothPinsNotLinked = _pins[1].first == nullptr || _pins[2].first == nullptr;
        nts::Tristate pin1Value = _pins[1].first ? _pins[1].first->compute(_pins[1].second) : UNDEFINED;
        nts::Tristate pin2Value = _pins[2].first ? _pins[2].first->compute(_pins[2].second) : UNDEFINED;
        if (oneOrBothPinsNotLinked)
            return UNDEFINED;
        if ((pin1Value == TRUE && pin2Value == FALSE) || (pin1Value == FALSE && pin2Value == TRUE))
            return TRUE;
        if (pin1Value == UNDEFINED || pin2Value == UNDEFINED)
            return UNDEFINED;
        return FALSE;
    } else if (pin == 4) { // Output of the XOR Component
        bool oneOrBothPinsNotLinked = _pins[5].first == nullptr || _pins[6].first == nullptr;
        nts::Tristate pin5Value = _pins[5].first ? _pins[5].first->compute(_pins[5].second) : UNDEFINED;
        nts::Tristate pin6Value = _pins[6].first ? _pins[6].first->compute(_pins[6].second) : UNDEFINED;
        if (oneOrBothPinsNotLinked)
            return UNDEFINED;
        if ((pin5Value == TRUE && pin6Value == FALSE) || (pin5Value == FALSE && pin6Value == TRUE))
            return TRUE;
        if (pin5Value == UNDEFINED || pin6Value == UNDEFINED)
            return UNDEFINED;
        return FALSE;
    } else if (pin == 10) { // Output of the XOR Component
        bool oneOrBothPinsNotLinked = _pins[8].first == nullptr || _pins[9].first == nullptr;
        nts::Tristate pin8Value = _pins[8].first ? _pins[8].first->compute(_pins[8].second) : UNDEFINED;
        nts::Tristate pin9Value = _pins[9].first ? _pins[9].first->compute(_pins[9].second) : UNDEFINED;
        if (oneOrBothPinsNotLinked)
            return UNDEFINED;
        if ((pin8Value == TRUE && pin9Value == FALSE) || (pin8Value == FALSE && pin9Value == TRUE))
            return TRUE;
        if (pin8Value == UNDEFINED || pin9Value == UNDEFINED)
            return UNDEFINED;
        return FALSE;
    } else if (pin == 11) { // Output of the XOR Component
        bool oneOrBothPinsNotLinked = _pins[12].first == nullptr || _pins[13].first == nullptr;
        nts::Tristate pin12Value = _pins[12].first ? _pins[12].first->compute(_pins[12].second) : UNDEFINED;
        nts::Tristate pin13Value = _pins[13].first ? _pins[13].first->compute(_pins[13].second) : UNDEFINED;
        if (oneOrBothPinsNotLinked)
            return UNDEFINED;
        if ((pin12Value == TRUE && pin13Value == FALSE) || (pin12Value == FALSE && pin13Value == TRUE))
            return TRUE;
        if (pin12Value == UNDEFINED || pin13Value == UNDEFINED)
            return UNDEFINED;
        return FALSE;
    } else {
        if (_pins[pin].first == nullptr)
            return UNDEFINED;
        return _pins[pin].first->compute(_pins[pin].second);
    }
}
