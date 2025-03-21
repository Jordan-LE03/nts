/*
** EPITECH PROJECT, 2025
** Parser
** File description:
** Parser
*/

#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "../Component.hpp"
#include "../AllComponents.hpp"

namespace nts
{
    class Parser {
        public:
            Parser(Circuit &circuit, const std::string &filename);
            ~Parser();
            void parse();

        private:
            std::string retrieveChipsets(std::ifstream &file);
            void retrieveLinks(std::ifstream &file);
            Circuit &_circuit;
            std::string _filename;
    };
}
