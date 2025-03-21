/*
** EPITECH PROJECT, 2025
** FourBitsAdderComponent
** File description:
** FourBitsAdderComponent
*/

#include "FourBitsAdderComponent.hpp"


nts::BitsAdderComponent::BitsAdderComponent()
{
    std::size_t pin;

    for (pin = 1; pin <= 5; pin++) {
        addPin(pin);
    }
}

nts::BitsAdderComponent::~BitsAdderComponent() {}

nts::Tristate nts::BitsAdderComponent::compute(std::size_t pin)
{

    if (_pins[pin].first == nullptr) {
        return UNDEFINED;
    }

    nts::ORGate c_or;
    nts::XORGate c_xor;
    nts::ANDGate c_and;
    nts::InputComponent i1;
    nts::InputComponent i2;
    nts::InputComponent carry;
    nts::NOTComponent c_not;

    i1.setValue(compute(1));
    i2.setValue(compute(2));
    carry.setValue(compute(3));
    i1.simulate(1);
    i2.simulate(1);
    carry.simulate(1);

    if (pin == 4) { // Carry out
        if (carry.compute(1) == nts::Tristate::TRUE) {
            c_or.setLink(1, i1, 1);
            c_or.setLink(2, i2, 1);
            return c_or.compute(3);
        }
        c_and.setLink(1, i1, 1);
        c_and.setLink(2, i2, 1);
        return c_and.compute(3);
    }

    if (pin == 5) { // Sum output
        c_xor.setLink(1, i1, 1);
        c_xor.setLink(2, i2, 1);
        
        if (compute(3) == nts::Tristate::FALSE)
            return c_xor.compute(3);
        c_not.setLink(1, c_xor, 3);
        return c_not.compute(2);
    }
    return _pins[pin].first->compute(_pins[pin].second);
}

nts::FourBitsAdderComponent::FourBitsAdderComponent()
{
    for (std::size_t pin = 1; pin <= 15; pin++) {
        if (pin == 8)
            continue;
        addPin(pin);
    }

    BitsAdderComponent adder1;
    BitsAdderComponent adder2;
    BitsAdderComponent adder3;
    BitsAdderComponent adder4;

    // Bits adder 1
    setLink(6, adder1, 1);
    setLink(7, adder1, 2);
    setLink(9, adder1, 3);
    setLink(10, adder1, 5);

    // Bits adder 2
    setLink(4, adder2, 1);
    setLink(5, adder2, 2);
    setLink(11, adder2, 5);

    // Bits adder 3
    setLink(2, adder3, 1);
    setLink(3, adder3, 2);
    setLink(12, adder3, 5);

    // Bits adder 4
    setLink(15, adder4, 1);
    setLink(1, adder4, 2);
    setLink(13, adder4, 5);

    // Carry-out
    setLink(14, adder4, 4);

    // Links between adders (carry-out to carry-in)
    adder1.setLink(4, adder2, 3);
    adder2.setLink(4, adder3, 3);
    adder3.setLink(4, adder4, 3);
}

nts::FourBitsAdderComponent::~FourBitsAdderComponent() {}

nts::Tristate nts::FourBitsAdderComponent::compute(std::size_t pin) {
    if (_pins[pin].first == nullptr) {
        return nts::Tristate::UNDEFINED;
    }
    return _pins[pin].first->compute(_pins[pin].second);
}
