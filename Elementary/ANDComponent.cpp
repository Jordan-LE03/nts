/*
** EPITECH PROJECT, 2025
** ANDComponent
** File description:
** ANDComponent
*/

#include "ANDComponent.hpp"

nts::ANDComponent::ANDComponent()
{
    addPin(1);
    addPin(2);
    addPin(3);
}

nts::ANDComponent::~ANDComponent() {}

nts::Tristate nts::ANDComponent::compute(std::size_t pin)
{
    if (pin < 1 || pin > 3)
        throw nts::Error("Pin not found");
    if (pin == 3) { // Output of the AND Component
        bool oneOrBothPinsNotLinked = _pins[1].first == nullptr || _pins[2].first == nullptr;
        if (oneOrBothPinsNotLinked)
            return UNDEFINED;

        // Check the value of pins 1 & 2 to get the value of pin 3
        bool oneOrBothPinsUndefined = _pins[1].first->compute(_pins[1].second) == UNDEFINED || _pins[2].first->compute(_pins[2].second) == UNDEFINED;
        bool oneOrBothPinsFalse = _pins[1].first->compute(_pins[1].second) == FALSE || _pins[2].first->compute(_pins[2].second) == FALSE;
        
        if (oneOrBothPinsFalse)
            return FALSE;
        if (oneOrBothPinsUndefined)
            return UNDEFINED;
        return TRUE;
    } else {
        if (_pins[pin].first == nullptr)
            return UNDEFINED;
        return _pins[pin].first->compute(_pins[pin].second);
    }
}
