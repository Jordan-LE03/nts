/*
** EPITECH PROJECT, 2025
** OutputComponent
** File description:
** OutputComponent
*/

#include "OutputComponent.hpp"

nts::OutputComponent::OutputComponent()
{
    addPin(1);
}

nts::OutputComponent::~OutputComponent() {}

nts::Tristate nts::OutputComponent::compute(std::size_t pin)
{
    if (pin != 1) {
        throw nts::Error("Pin not found");
    }
    if (_pins[pin].first == nullptr) {
        return UNDEFINED;
    }
    return _pins[pin].first->compute(_pins[pin].second);
}
