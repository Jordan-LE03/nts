/*
** EPITECH PROJECT, 2025
** ClockComponent
** File description:
** ClockComponent
*/

#pragma once

#include "../Component.hpp"

namespace nts
{
    class ClockComponent : public AComponent {
        public:
            ClockComponent();
            ~ClockComponent();
            void simulate(std::size_t tick) final;
            Tristate compute(std::size_t pin = 1) final;
            void setValue(Tristate value);
        private:
            Tristate current = UNDEFINED;
            Tristate next = UNDEFINED;
    };
}
