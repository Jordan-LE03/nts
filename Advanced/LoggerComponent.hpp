/*
 ** EPITECH PROJECT, 2025
 ** LoggerComponent
 ** File description:
 ** LoggerComponent
 */

#pragma once

#include "../Component.hpp"
#include <cstddef>
#include <cmath>
namespace nts
{
    class LoggerComponent : public AComponent {
        public:
            LoggerComponent();
            ~LoggerComponent();
            Tristate compute(std::size_t) final;
            void simulate(std::size_t tick) final;
        private:
            std::pair<Tristate, Tristate> _clockValue;
    };
}
