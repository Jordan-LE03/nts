/*
** EPITECH PROJECT, 2025
** InputComponent
** File description:
** InputComponent
*/

#include "InputComponent.hpp"

nts::InputComponent::InputComponent()
{
    addPin(1);
}

nts::InputComponent::~InputComponent() {}

nts::Tristate nts::InputComponent::compute(std::size_t pin)
{
    if (pin != 1)
        throw nts::Error("Pin not found");
    return current;
}

void nts::InputComponent::simulate(std::size_t tick)
{
    (void)tick;
    current = next;
}

void nts::InputComponent::setValue(nts::Tristate value)
{
    next = value;
}
