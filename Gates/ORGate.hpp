/*
** EPITECH PROJECT, 2025
** ORComponent
** File description:
** ORComponent
*/

#pragma once

#include "../Component.hpp"

namespace nts
{
    class ORGate : public AComponent {
        public:
            ORGate();
            ~ORGate();
            Tristate compute(std::size_t pin = 1) final;
    };
}