/*
** EPITECH PROJECT, 2025
** ANDComponent
** File description:
** ANDComponent
*/

#pragma once

#include "../Component.hpp"

namespace nts
{
    class ANDGate : public AComponent {
        public:
            ANDGate();
            ~ANDGate();
            Tristate compute(std::size_t pin = 1) final;
    };
}