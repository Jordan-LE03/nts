/*
** EPITECH PROJECT, 2025
** FourBitsAdderComponent
** File description:
** FourBitsAdderComponent
*/

#pragma once

#include "../Component.hpp"
#include "../AllComponents.hpp"
#include <cstddef>

namespace nts
{
    class BitsAdderComponent : public AComponent {
        public:
            BitsAdderComponent();
            ~BitsAdderComponent();
            Tristate compute(std::size_t pin);
    };

    class FourBitsAdderComponent : public AComponent {
        public:
            FourBitsAdderComponent();
            ~FourBitsAdderComponent();
            Tristate compute(std::size_t pin) final;
    };
}
