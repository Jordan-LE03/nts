/*
** EPITECH PROJECT, 2025
** Shell
** File description:
** Shell
*/

#pragma once

#include "../Component.hpp"
#include "../AllComponents.hpp"
#include "../Parsing/Parser.hpp"


#include <iostream>
#include <map>
#include <vector>
#include <unistd.h>
#include <csignal>
#include <limits>
#include <sstream>
#include <algorithm>


namespace nts
{
    class Shell {
        public:
            Shell(std::map<std::string, std::unique_ptr<IComponent>> &components) : _components(components) {}
            ~Shell() = default;
            void run();
            std::size_t getTick() const;
            bool executeCommand(const std::string& command);
        private:
            void setValue(const std::string& name, const std::string& value);
            void display();
            void simulate();
            void loop();
            bool runningLoop = false;
            std::map<std::string, std::unique_ptr<IComponent>> &_components;
            std::size_t _tick = 0;
    };
}
