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
    class ANDComponent : public AComponent {
        public:
            ANDComponent();
            ~ANDComponent();
            Tristate compute(std::size_t pin = 1) final;
    };
}
