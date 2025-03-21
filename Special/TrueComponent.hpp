/*
** EPITECH PROJECT, 2025
** TrueComponent
** File description:
** TrueComponent
*/

#pragma once

#include "../Component.hpp"

namespace nts
{
    class TrueComponent : public AComponent {
        public:
            TrueComponent();
            ~TrueComponent();
            Tristate compute(std::size_t pin = 1) final;
        private:
            Tristate _state = TRUE;
    };
}
