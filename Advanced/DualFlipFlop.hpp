/*
** EPITECH PROJECT, 2025
** DualFlipFlop:wComponent
** File description:
** DualFlipFlopComponent
*/

#pragma once

#include "../Component.hpp"

namespace nts
{
    class DualFlipFlop : public AComponent {
        public:
            DualFlipFlop();
            ~DualFlipFlop();
            Tristate compute(std::size_t pin = 1) final;
    };
}
