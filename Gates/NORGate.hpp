/*
** EPITECH PROJECT, 2025
** NORComponent
** File description:
** NORComponent
*/

#pragma once

#include "../Component.hpp"
#include <vector>

namespace nts
{
    class NORGate : public AComponent {
        public:
            NORGate();
            ~NORGate();
            Tristate compute(std::size_t pin = 1) final;
        private:
            std::vector<std::size_t> _computedPins;
    };
}
