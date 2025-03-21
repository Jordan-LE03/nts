/*
** EPITECH PROJECT, 2025
** NORGate
** File description:
** NORGate
*/

#include "NORGate.hpp"

nts::NORGate::NORGate()
{
    addPin(1);
    addPin(2);
    addPin(3); // Output of 1 and 2
    addPin(4); // Output of 5 and 6
    addPin(5);
    addPin(6);
    addPin(8);
    addPin(9);
    addPin(10); // Output of 8 and 9
    addPin(11); // Output of 12 and 13
    addPin(12);
    addPin(13);
}

nts::NORGate::~NORGate() {}

nts::Tristate nts::NORGate::compute(std::size_t pin)
{
    if ((pin < 1 || pin > 13) || pin == 7)
        throw nts::Error("Pin not found");
    
    std::size_t count = 0;
    for (std::size_t i = 0; i < _computedPins.size(); i++) {
        if (_computedPins.at(i) == pin) {
            count++;
        }
        if (count > 100)
            return UNDEFINED;
    }
    _computedPins.push_back(pin);

    if (pin == 3) { // Output of the NOR Component
        nts::Tristate pin1Value = _pins[1].first ? _pins[1].first->compute(_pins[1].second) : UNDEFINED;
        nts::Tristate pin2Value = _pins[2].first ? _pins[2].first->compute(_pins[2].second) : UNDEFINED;
        if (pin1Value == TRUE || pin2Value == TRUE)
            return FALSE;
        if (pin1Value == UNDEFINED || pin2Value == UNDEFINED)
            return UNDEFINED;
        return TRUE;
    } else if (pin == 4) { //Output of the NOR Component
        nts::Tristate pin5Value = _pins[5].first ? _pins[5].first->compute(_pins[5].second) : UNDEFINED;
        nts::Tristate pin6Value = _pins[6].first ? _pins[6].first->compute(_pins[6].second) : UNDEFINED;
        if (pin5Value == TRUE || pin6Value == TRUE)
            return FALSE;
        if (pin5Value == UNDEFINED || pin6Value == UNDEFINED)
            return UNDEFINED;
        return TRUE;
    } else if (pin == 10) { // Output of the NOR Component
        nts::Tristate pin8Value = _pins[8].first ? _pins[8].first->compute(_pins[8].second) : UNDEFINED;
        nts::Tristate pin9Value = _pins[9].first ? _pins[9].first->compute(_pins[9].second) : UNDEFINED; 
        if (pin8Value == TRUE || pin9Value == TRUE)
            return FALSE;
        if (pin8Value == UNDEFINED || pin9Value == UNDEFINED)
            return UNDEFINED;
        return TRUE;
    } else if (pin == 11) { // Output of the NOR Component 
        nts::Tristate pin12Value = _pins[12].first ? _pins[12].first->compute(_pins[12].second) : UNDEFINED;
        nts::Tristate pin13Value = _pins[13].first ? _pins[13].first->compute(_pins[13].second) : UNDEFINED;
        if (pin12Value == TRUE || pin13Value == TRUE)
            return FALSE;
        if (pin12Value == UNDEFINED || pin13Value == UNDEFINED)
            return UNDEFINED;
        return TRUE;
    } else {
        if (_pins[pin].first == nullptr)
            return UNDEFINED;
        return _pins[pin].first->compute(_pins[pin].second);
    }
}
