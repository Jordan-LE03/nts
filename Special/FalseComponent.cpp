/*
** EPITECH PROJECT, 2025
** FalseComponent
** File description:
** FalseComponent
*/

#include "FalseComponent.hpp"

nts::FalseComponent::FalseComponent()
{
    addPin(1);
}

nts::FalseComponent::~FalseComponent() {}

nts::Tristate nts::FalseComponent::compute(std::size_t pin)
{
    if (pin != 1)
        throw nts::Error("Pin not found");
    return _state;
}
