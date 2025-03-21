/*
** EPITECH PROJECT, 2025
** ORComponent
** File description:
** ORComponent
*/

#include "ORComponent.hpp"

nts::ORComponent::ORComponent()
{
    addPin(1);
    addPin(2);
    addPin(3);
}

nts::ORComponent::~ORComponent() {}

nts::Tristate nts::ORComponent::compute(std::size_t pin)
{
    if (pin < 1 || pin > 3)
        throw nts::Error("Pin not found");
    if (pin == 3) { // Output of the OR Component

        // Check the value of pins 1 & 2 to get the value of pin 3
        bool oneOrBothPinsNotLinked = _pins[1].first == nullptr || _pins[2].first == nullptr;
        nts::Tristate pin1Value = _pins[1].first ? _pins[1].first->compute(_pins[1].second) : UNDEFINED;
        nts::Tristate pin2Value = _pins[2].first ? _pins[2].first->compute(_pins[2].second) : UNDEFINED;
        if (oneOrBothPinsNotLinked)
            return UNDEFINED;
        if (pin1Value == TRUE || pin2Value == TRUE)
            return TRUE;
        if (pin1Value == UNDEFINED || pin2Value == UNDEFINED)
            return UNDEFINED;
        return FALSE;
    } else {
        if (_pins[pin].first == nullptr)
            return UNDEFINED;
        return _pins[pin].first->compute(_pins[pin].second);
    }
}
