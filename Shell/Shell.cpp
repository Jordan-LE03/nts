/*
** EPITECH PROJECT, 2025
** Shell
** File description:
** Shell
*/

#include "Shell.hpp"

bool nts::Shell::executeCommand(const std::string &command)
{
    if (command.empty() || command.find_first_not_of(" \t") == std::string::npos) {
        return true;
    }

    std::string cleanCommand = command;
    cleanCommand.erase(0, cleanCommand.find_first_not_of(" \t"));
    cleanCommand.erase(cleanCommand.find_last_not_of(" \t") + 1);

    if (cleanCommand == "simulate") {
        simulate();
        return true;
    } else if (cleanCommand == "loop") {
        loop();
        return true;
    } else if (cleanCommand == "display") {
        display();
        return true;
    } else if (cleanCommand == "exit") {
        return false;
    } else if (cleanCommand.find("=") != std::string::npos) {
        std::size_t equalPos = cleanCommand.find("=");
        std::string name = cleanCommand.substr(0, equalPos);
        std::string value = cleanCommand.substr(equalPos + 1);
        
        name.erase(0, name.find_first_not_of(" \t"));
        name.erase(name.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));
        value.erase(value.find_last_not_of(" \t") + 1);
        
        setValue(name, value);
        return true;
    } else {
        std::cerr << "Unknow command: " << cleanCommand << std::endl;
        return true;
    }
}

void nts::Shell::setValue(const std::string& name, const std::string& valueStr)
{
    if (_components.find(name) == _components.end()) {
        std::cerr << "Unknow component name: " << name << std::endl;
        return;
    }

    int value;
    if (valueStr == "U") {
        value = -1;
    } else {
        std::stringstream converter(valueStr);
        if (!(converter >> value) || value < 0 || value > 1) {
            std::cerr << "Invalid value: " << valueStr << std::endl;
            return;
        }
    }

    InputComponent* input = dynamic_cast<InputComponent*>(_components.at(name).get());
    if (input) {
        input->setValue(static_cast<Tristate>(value));
        return;
    }

    ClockComponent* clock = dynamic_cast<ClockComponent*>(_components.at(name).get());
    if (clock) {
        clock->setValue(static_cast<Tristate>(value));
    }
}

void nts::Shell::run()
{
    while (true) {
        std::string command;
        std::cout << "> ";
        std::cin.clear(); // Clear error flags
        std::getline(std::cin, command);

        // Handling EOF (CTRL+D)
        if (std::cin.eof()) {
            break;
        }
        if (!executeCommand(command))
            break;
    }
}

void nts::Shell::simulate()
{
    for (auto &component : _components) {
        component.second->simulate(1);
    }
    _tick++;
}

bool running = true;

void handleSignal(int signal)
{
    if (signal == SIGINT) {
        running = false;
    }
}

void nts::Shell::loop()
{
    signal(SIGINT, handleSignal);

    while (running) {
        simulate();
        display();
        sleep(1);
    }
    signal(SIGINT, SIG_DFL);
    running = true;
    std::cout << std::endl;
}


void nts::Shell::display()
{
    std::cout << "tick: " << _tick << std::endl;
    nts::Tristate value;

    // Displaying inputs
    std::cout << "input(s):" << std::endl;
    for (auto &component : _components) {

        // Input Component
        nts::InputComponent *input = dynamic_cast<nts::InputComponent *>(component.second.get());
        if (input) {
            std::cout << "  ";
            value = input->compute();
            if (value == nts::Tristate::UNDEFINED) {
                std::cout << component.first << ": U" << std::endl;
                continue;
            }
            std::cout << component.first << ": " << value << std::endl;
            continue;
        }

        // Clock Component
        nts::ClockComponent *clock = dynamic_cast<nts::ClockComponent *>(component.second.get());
        if (clock) {
            std::cout << "  ";
            value = clock->compute();
            if (value == nts::Tristate::UNDEFINED) {
                std::cout << component.first << ": U" << std::endl;
                continue;
            }
            std::cout << component.first << ": " << value << std::endl;
        }
    }

    // Displaying outputs
    std::cout << "output(s):" << std::endl;
    for (auto &component : _components) {
        nts::OutputComponent *output = dynamic_cast<nts::OutputComponent *>(component.second.get());
        if (output) {
            std::cout << "  ";
            value = output->compute();
            if (value == nts::Tristate::UNDEFINED) {
                std::cout << component.first << ": U" << std::endl;
                continue;
            }
            std::cout << component.first << ": " << value << std::endl;
        }
    }
}

std::size_t nts::Shell::getTick() const
{
    return _tick;
}
