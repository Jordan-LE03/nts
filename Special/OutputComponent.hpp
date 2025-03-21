/*
** EPITECH PROJECT, 2025
** OutputComponent
** File description:
** OutputComponent
*/

#pragma once

#include "../Component.hpp"

namespace nts
{
    class OutputComponent : public AComponent {
        public:
            OutputComponent();
            ~OutputComponent();
            Tristate compute(std::size_t pin = 1) final;
            void setValue(Tristate value);
        private:
            Tristate _state = UNDEFINED;
    };
}
