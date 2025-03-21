/*
** EPITECH PROJECT, 2025
** NOTComponent
** File description:
** NOTComponent
*/

#include "NOTComponent.hpp"

nts::NOTComponent::NOTComponent()
{
    addPin(1);
    addPin(2);
}

nts::NOTComponent::~NOTComponent() {}

nts::Tristate nts::NOTComponent::compute(std::size_t pin)
{
    if (pin < 1 || pin > 2)
        throw nts::Error("Pin not found");
    if (pin == 2) { // Output of the NOT Component
        bool pinIsNotLinked = _pins[1].first == nullptr;
        if (pinIsNotLinked)
            return UNDEFINED;

        // Check the value of pin 1 to get the value of pin 2
        bool pinIsUndefined = _pins[1].first->compute(_pins[1].second) == UNDEFINED;
        bool pinIsFalse = _pins[1].first->compute(_pins[1].second) == FALSE;

        if (pinIsFalse)
            return TRUE;
        if (pinIsUndefined)
            return UNDEFINED;
        return FALSE;
    } else {
        if (_pins[pin].first == nullptr)
            return UNDEFINED;
        return _pins[pin].first->compute(_pins[pin].second);
    }
}
