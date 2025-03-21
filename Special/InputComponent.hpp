/*
** EPITECH PROJECT, 2025
** InputComponent
** File description:
** InputComponent
*/

#pragma once

#include "../Component.hpp"

namespace nts
{
    class InputComponent : public AComponent {
        public:
            InputComponent();
            ~InputComponent();
            void simulate(std::size_t tick) final;
            Tristate compute(std::size_t pin = 1) final;
            void setValue(Tristate value);
        private:
            Tristate current = UNDEFINED;
            Tristate next = UNDEFINED;
    };
}
