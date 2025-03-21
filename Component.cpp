/*
** EPITECH PROJECT, 2025
** Component
** File description:
** Component
*/

#include "Component.hpp"

std::map<std::size_t, std::pair<nts::IComponent *, std::size_t>> nts::AComponent::getPins() const
{
    return _pins;
}

void nts::AComponent::simulate(std::size_t tick)
{
    (void)tick;
}

void nts::AComponent::setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin)
{
    nts::AComponent *otherComponent = dynamic_cast<nts::AComponent *>(&other);

    if (_pins.find(pin) == _pins.end())
        throw nts::Error("Pin not found");
    if (otherComponent->_pins.find(otherPin) == otherComponent->_pins.end())
        throw nts::Error("Pin not found");
    _pins[pin] = std::pair(&other, otherPin);
    otherComponent->_pins[otherPin] = std::pair(this, pin);
}

void nts::AComponent::addPin(std::size_t pin)
{
    _pins[pin] = std::pair(nullptr, 0);
}
