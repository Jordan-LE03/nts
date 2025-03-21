/*
** EPITECH PROJECT, 2025
** XORComponent
** File description:
** XORComponent
*/

#pragma once

#include "../Component.hpp"

namespace nts
{
    class XORComponent : public AComponent {
        public:
            XORComponent();
            ~XORComponent();
            Tristate compute(std::size_t pin = 1) final;
    };
}