/*
** EPITECH PROJECT, 2025
** NOTComponent
** File description:
** NOTComponent
*/

#pragma once

#include "../Component.hpp"

namespace nts
{
    class NOTComponent : public AComponent {
        public:
            NOTComponent();
            ~NOTComponent();
            Tristate compute(std::size_t pin = 1) final;
    };
}
