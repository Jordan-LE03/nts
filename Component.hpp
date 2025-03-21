/*
** EPITECH PROJECT, 2025
** Component
** File description:
** Component
*/

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <memory>

#include "Nts.hpp"

namespace nts
{
    class IComponent {
        public:
            virtual ~IComponent() = default;
            virtual void simulate(std::size_t tick) = 0;
            virtual Tristate compute(std::size_t pin = 1) = 0;
            virtual void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) = 0;
    };

    class AComponent : public IComponent {
        public:
            AComponent() = default;
            virtual ~AComponent() = default;
            virtual void simulate(std::size_t tick) override;
            virtual Tristate compute(std::size_t pin = 1) = 0;
            virtual void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) final;
            std::map<std::size_t, std::pair<IComponent *, std::size_t>> getPins() const;
        protected:
            void addPin(std::size_t pin);
            std::map<std::size_t, std::pair<IComponent *, std::size_t>> _pins;
    };

    class Circuit { // Factory
        public:
            Circuit() = default;
            ~Circuit();
            std::map<std::string, std::unique_ptr<IComponent>> &getComponents();
            std::unique_ptr<IComponent> createComponent(const std::string &type);
        private:
            std::map<std::string, std::unique_ptr<IComponent>> _components;
            std::unique_ptr<IComponent> create4001();
            std::unique_ptr<IComponent> create4011();
            std::unique_ptr<IComponent> create4030();
            std::unique_ptr<IComponent> create4069();
            std::unique_ptr<IComponent> create4071();
            std::unique_ptr<IComponent> create4081();
            std::unique_ptr<IComponent> create4013();
            std::unique_ptr<IComponent> createInput();
            std::unique_ptr<IComponent> createOutput();
            std::unique_ptr<IComponent> createTrue();
            std::unique_ptr<IComponent> createFalse();
            std::unique_ptr<IComponent> createClock();
            std::unique_ptr<IComponent> createAND();
            std::unique_ptr<IComponent> createOR();
            std::unique_ptr<IComponent> createXOR();
            std::unique_ptr<IComponent> createNOT();
            std::unique_ptr<IComponent> createNAND();
            std::unique_ptr<IComponent> createNOR();
            std::unique_ptr<IComponent> createLogger();
    };
}
