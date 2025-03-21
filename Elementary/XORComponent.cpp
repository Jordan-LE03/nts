/*
** EPITECH PROJECT, 2025
** XORComponent
** File description:
** XORComponent
*/

#include "XORComponent.hpp"

nts::XORComponent::XORComponent()
{
    addPin(1);
    addPin(2);
    addPin(3);
}

nts::XORComponent::~XORComponent() {}

nts::Tristate nts::XORComponent::compute(std::size_t pin)
{
    if (pin < 1 || pin > 3)
        throw nts::Error("Pin not found");
    if (pin == 3) { // Output of the XOR Component
        bool oneOrBothPinsNotLinked = _pins[1].first == nullptr || _pins[2].first == nullptr;
        if (oneOrBothPinsNotLinked)
            return UNDEFINED;

        // Check the value of pins 1 & 2 to get the value of pin 3
        bool oneOrBothPinsUndefined = _pins[1].first->compute(_pins[1].second) == UNDEFINED || _pins[2].first->compute(_pins[2].second) == UNDEFINED;
        bool pinsEqual = _pins[1].first->compute(_pins[1].second) != _pins[2].first->compute(_pins[2].second);

        if (oneOrBothPinsUndefined)
            return UNDEFINED;
        if (pinsEqual)
            return TRUE;
        return FALSE;
    } else {
        if (_pins[pin].first == nullptr)
            return UNDEFINED;
        return _pins[pin].first->compute(_pins[pin].second);
    }
}
