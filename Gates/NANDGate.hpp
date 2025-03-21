/*
** EPITECH PROJECT, 2025
** NANDComponent
** File description:
** NANDComponent
*/

#pragma once

#include "../Component.hpp"

namespace nts
{
    class NANDGate : public AComponent {
        public:
            NANDGate();
            ~NANDGate();
            Tristate compute(std::size_t pin = 1) final;
    };
}
