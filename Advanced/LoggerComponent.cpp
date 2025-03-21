/*
** EPITECH PROJECT, 2025
** LoggerComponent
** File description:
** LoggerComponent
*/

#include "LoggerComponent.hpp"
#include <cmath>
#include <cstddef>
#include <fstream>

nts::LoggerComponent::LoggerComponent()
{
    int pin;

    for (pin = 1; pin <= 10; pin++) {
        addPin(pin);
    }
    _clockValue.first = UNDEFINED;
    _clockValue.second = UNDEFINED;
}

nts::LoggerComponent::~LoggerComponent() {}

nts::Tristate nts::LoggerComponent::compute(std::size_t pin)
{
    if (pin < 1 || pin > 10) {
        throw nts::Error("Pin not found");
    }
    if (_pins[pin].first == nullptr) {
        return UNDEFINED;
    }
    return _pins[pin].first->compute(_pins[pin].second);
}

void nts::LoggerComponent::simulate(std::size_t tick)
{
    (void)tick;
    
    Tristate clockPinValue = compute(9);
    Tristate inhibitPinValue = compute(10);

    // Update clock values pair
    _clockValue.second = _clockValue.first;
    _clockValue.first = clockPinValue; 

    if (inhibitPinValue != FALSE) {
        return;
    }
    if (_clockValue.first == TRUE && _clockValue.second == FALSE) {
        std::ofstream file("./log.bin", std::ios::app);

        if (!file) {
            throw Error("Logger: Error while opening log.bin file.");
        }
        unsigned char c = 0;
        for (std::size_t pin = 1; pin <= 8; pin++) {
            if (compute(pin) == TRUE) {
                c += std::pow(2, pin - 1);
            }
        }
        file << c;
        file.close();
    }
}
