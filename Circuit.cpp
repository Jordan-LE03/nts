/*
** EPITECH PROJECT, 2025
** Circuit
** File description:
** Circuit
*/

#include "Advanced/DualFlipFlop.hpp"
#include "Advanced/LoggerComponent.hpp"
#include "Component.hpp"
#include "AllComponents.hpp"
#include <memory>

nts::Circuit::~Circuit() {}

std::map<std::string, std::unique_ptr<nts::IComponent>> &nts::Circuit::getComponents()
{
    return _components;
}

std::unique_ptr<nts::IComponent> nts::Circuit::createComponent(const std::string &type)
{
    if (type == "input") {
        return createInput();
    } else if (type == "output") {
        return createOutput();
    } else if (type == "clock") {
        return createClock();
    } else if (type == "true") {
        return createTrue();
    } else if (type == "false") {
        return createFalse();
    } else if (type == "and") {
        return createAND();
    } else if (type == "not") {
        return createNOT();
    } else if (type == "or") {
        return createOR();
    } else if (type == "xor") {
        return createXOR();
    } else if (type == "4001") {
        return create4001();
    } else if (type == "4011") {
        return create4011();
    } else if (type == "4030") {
        return create4030();
    } else if (type == "4069") {
        return create4069();
    } else if (type == "4071") {
        return create4071();
    } else if (type == "4081") {
        return create4081();
    } else if (type == "4013") {
        return create4013();
    } else if (type == "logger") {
        return createLogger();
    } else {
        throw nts::Error("Component not found: " + type);
    }
}

std::unique_ptr<nts::IComponent> nts::Circuit::create4001()
{
    return std::make_unique<nts::NORGate>();
}

std::unique_ptr<nts::IComponent> nts::Circuit::create4011()
{
    return std::make_unique<nts::NANDGate>();
}

std::unique_ptr<nts::IComponent> nts::Circuit::create4030()
{
    return std::make_unique<nts::XORGate>();
}

std::unique_ptr<nts::IComponent> nts::Circuit::create4069()
{
    return std::make_unique<nts::NOTGate>();
}

std::unique_ptr<nts::IComponent> nts::Circuit::create4071()
{
    return std::make_unique<nts::ORGate>();
}

std::unique_ptr<nts::IComponent> nts::Circuit::create4081()
{
    return std::make_unique<nts::ANDGate>();
}

std::unique_ptr<nts::IComponent> nts::Circuit::createInput()
{
    return std::make_unique<nts::InputComponent>();
}

std::unique_ptr<nts::IComponent> nts::Circuit::createOutput()
{
    return std::make_unique<nts::OutputComponent>();
}

std::unique_ptr<nts::IComponent> nts::Circuit::createTrue()
{
    return std::make_unique<nts::TrueComponent>();
}

std::unique_ptr<nts::IComponent> nts::Circuit::createFalse()
{
    return std::make_unique<nts::FalseComponent>();
}

std::unique_ptr<nts::IComponent> nts::Circuit::createClock()
{
    return std::make_unique<nts::ClockComponent>();
}

std::unique_ptr<nts::IComponent> nts::Circuit::createAND()
{
    return std::make_unique<nts::ANDComponent>();
}

std::unique_ptr<nts::IComponent> nts::Circuit::createOR()
{
    return std::make_unique<nts::ORComponent>();
}

std::unique_ptr<nts::IComponent> nts::Circuit::createXOR()
{
    return std::make_unique<nts::XORComponent>();
}

std::unique_ptr<nts::IComponent> nts::Circuit::createNOT()
{
    return std::make_unique<nts::NOTComponent>();
}

std::unique_ptr<nts::IComponent> nts::Circuit::createLogger()
{
    return std::make_unique<nts::LoggerComponent>();
}

std::unique_ptr<nts::IComponent> nts::Circuit::create4013()
{
    return std::make_unique<nts::DualFlipFlop>();
}
