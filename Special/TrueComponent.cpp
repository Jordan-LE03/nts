/*
** EPITECH PROJECT, 2025
** TrueComponent
** File description:
** TrueComponent
*/

#include "TrueComponent.hpp"

nts::TrueComponent::TrueComponent()
{
    addPin(1);
}

nts::TrueComponent::~TrueComponent() {}

nts::Tristate nts::TrueComponent::compute(std::size_t pin)
{
    if (pin != 1)
        throw nts::Error("Pin not found");
    return _state;
}
