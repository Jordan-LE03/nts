/*
** EPITECH PROJECT, 2025
** DualFlipFlop
** File description:
** DualFlipFlop
*/

#include "DualFlipFlop.hpp"

nts::DualFlipFlop::DualFlipFlop()
{
    addPin(1); // Q1
    addPin(2); // Qnot1
    addPin(3); // Clock1
    addPin(4); // Reset1
    addPin(5); // Data1
    addPin(6); // Set1
    addPin(8); // Set2
    addPin(9); // Data2
    addPin(10); // Reset2
    addPin(11); // Clock2
    addPin(12); // Qnot2
    addPin(13); // Q2
}

nts::DualFlipFlop::~DualFlipFlop() {}

nts::Tristate nts::DualFlipFlop::compute(std::size_t pin)
{
    if (pin == 7)
        throw nts::Error("Cannot compute pin 7");
    if (pin < 1 || pin > 13)
        throw nts::Error("Pin not found");
    if (pin == 1 || pin == 2) { // Output of the first DualFlipFlop
        bool oneOrBothPinsNotLinked = _pins[3].first == nullptr || _pins[4].first == nullptr || _pins[5].first == nullptr || _pins[6].first == nullptr;
        nts::Tristate pin3Value = _pins[3].first ? _pins[3].first->compute(_pins[3].second) : UNDEFINED;
        nts::Tristate pin4Value = _pins[4].first ? _pins[4].first->compute(_pins[4].second) : UNDEFINED;
        nts::Tristate pin5Value = _pins[5].first ? _pins[5].first->compute(_pins[5].second) : UNDEFINED;
        nts::Tristate pin6Value = _pins[6].first ? _pins[6].first->compute(_pins[6].second) : UNDEFINED;
        if (oneOrBothPinsNotLinked)
            return UNDEFINED;
        if (pin4Value == TRUE || pin5Value == FALSE) {
            if (pin == 1)
                return FALSE;
            if (pin == 2)
                return TRUE;
        }
        if (pin6Value == TRUE || pin5Value == TRUE) {
            if (pin == 1)
                return TRUE;
            if (pin == 2)
                return FALSE;
        }
        if (pin3Value == UNDEFINED || pin5Value == UNDEFINED)
            return UNDEFINED;

        if (pin == 1) {
            return pin5Value;
        } else {
            if (pin5Value == TRUE) {
                return FALSE;
            } else {
                return TRUE;
            }
        }
    } else if (pin == 13 || pin == 12) { // Output of the second DualFlipFlop
        bool oneOrBothPinsNotLinked = _pins[8].first == nullptr || _pins[9].first == nullptr || _pins[10].first == nullptr || _pins[11].first == nullptr;
        nts::Tristate pin8Value = _pins[8].first ? _pins[8].first->compute(_pins[8].second) : UNDEFINED;
        nts::Tristate pin9Value = _pins[9].first ? _pins[9].first->compute(_pins[9].second) : UNDEFINED;
        nts::Tristate pin10Value = _pins[10].first ? _pins[10].first->compute(_pins[10].second) : UNDEFINED;
        nts::Tristate pin11Value = _pins[11].first ? _pins[11].first->compute(_pins[11].second) : UNDEFINED;
        if (oneOrBothPinsNotLinked)
            return UNDEFINED;
        if (pin10Value == TRUE || pin9Value == FALSE) {
            if (pin == 13)
                return FALSE;
            if (pin == 12)
                return TRUE;
        }
        if (pin8Value == TRUE || pin9Value == TRUE) {
            if (pin == 13)
                return TRUE;
            if (pin == 12)
                return FALSE;
        }
        if (pin11Value == UNDEFINED || pin9Value == UNDEFINED)
            return UNDEFINED;

        if (pin == 13) {
            return pin9Value;
        } else {
            if (pin9Value == TRUE) {
                return FALSE;
            } else {
                return TRUE;
            }
        }
        return UNDEFINED;
    } else {
        if (_pins[pin].first == nullptr)
            return UNDEFINED;
        return _pins[pin].first->compute(_pins[pin].second);
    }
}
