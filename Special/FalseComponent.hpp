/*
** EPITECH PROJECT, 2025
** FalseComponent
** File description:
** FalseComponent
*/

#pragma once

#include "../Component.hpp"

namespace nts
{
    class FalseComponent : public AComponent {
        public:
            FalseComponent();
            ~FalseComponent();
            Tristate compute(std::size_t pin = 1) final;
        private:
            Tristate _state = FALSE;
    };
}