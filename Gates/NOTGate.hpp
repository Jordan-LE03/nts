/*
** EPITECH PROJECT, 2025
** NOTGate
** File description:
** NOTGate
*/

#pragma once

#include "../Component.hpp"

namespace nts
{
    class NOTGate : public AComponent {
        public:
            NOTGate();
            ~NOTGate();
            Tristate compute(std::size_t pin = 1) final;
    };
}