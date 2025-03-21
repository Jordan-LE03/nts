/*
** EPITECH PROJECT, 2025
** ClockComponent
** File description:
** ClockComponent
*/

#include "ClockComponent.hpp"

nts::ClockComponent::ClockComponent()
{
    addPin(1);
}

nts::ClockComponent::~ClockComponent() {}

nts::Tristate nts::ClockComponent::compute(std::size_t pin)
{
    if (pin != 1)
        throw nts::Error("Pin not found");
    return current;
}

void nts::ClockComponent::simulate(std::size_t tick)
{
    (void)tick;
    current = next;
    if (current == UNDEFINED)
        return;
    if (current == TRUE) {
        next = FALSE;
        return;
    }
    next = TRUE;
}

void nts::ClockComponent::setValue(nts::Tristate value)
{
    next = value;
}
