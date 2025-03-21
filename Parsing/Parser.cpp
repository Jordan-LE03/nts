/*
** EPITECH PROJECT, 2025
** Parser
** File description:
** Parser
*/

#include "Parser.hpp"

nts::Parser::Parser(nts::Circuit &circuit, const std::string &filename) : _circuit(circuit), _filename(filename) {}

nts::Parser::~Parser() = default;

// Parse the .chipsets section of the file
std::string nts::Parser::retrieveChipsets(std::ifstream &file)
{
    std::string line;

    while (std::getline(file, line)) {
        if (line[0] && line[0] == '#')
            continue;
        std::stringstream ss(line);
        std::string type;
        std::string name;

        // Type verification
        ss >> type;
        if (type.empty() || type[0] == '#')
            continue;
        if (type == ".links:")
            break;

        // Name verification
        ss >> name;
        if (name.empty() || name[0] == '#')
            throw nts::Error("Parsing error: Missing name for '" + type + "'");
        if (_circuit.getComponents().find(name) != _circuit.getComponents().end())
            throw nts::Error("Parsing error: Name already exists '" + name + "'");

        // Create the component
        _circuit.getComponents().insert_or_assign(name, _circuit.createComponent(type));
    }
    return ".links:";
}

// Parse the links and check if the names and pins are valid
void nts::Parser::retrieveLinks(std::ifstream &file)
{
    std::string line;

    while (std::getline(file, line)) {
        if (line[0] && line[0] == '#')
            continue;
        
        // Replace ':' by ' ' to make the parsing with stringstream easier
        std::replace(line.begin(), line.end(), ':', ' ');

        std::stringstream ss(line);
        std::string name1;
        std::size_t pin1;
        std::string name2;
        std::size_t pin2;

        // Name1 verification
        ss >> name1;
        if (name1.empty() || name1[0] == '#')
            continue;
        if (_circuit.getComponents().find(name1) == _circuit.getComponents().end())
            throw nts::Error("Parsing error: Unknow component name '" + name1 + "'");

        // Pin1 verification
        if (!(ss >> pin1)) {
            throw nts::Error("Parsing error: Invalid pin value for '" + name1 + "'");
        }

        // Name2 verification
        ss >> name2;
        if (name2.empty() || name2[0] == '#')
            throw nts::Error("Parsing error: Missing target to link with '" + name1 + "'");
        if (_circuit.getComponents().find(name2) == _circuit.getComponents().end())
            throw nts::Error("Parsing error: Unknow component name '" + name2 + "'");

        // Pin2 verification
        if (!(ss >> pin2)) {
            throw nts::Error("Parsing error: Invalid pin value for '" + name2 + "'");
        }

        // Create the link
        _circuit.getComponents().at(name1)->setLink(pin1, *_circuit.getComponents().at(name2), pin2);
    }
}

// Parse the file and check if the file is valid
void nts::Parser::parse()
{
    std::ifstream file(_filename);

    if (!file)
        throw nts::Error("File not found: " + _filename);
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string type;

        // Type verification
        ss >> type;
        if (type[0] && type[0] == '#')
            continue;
        
        // Retrieving the chipsets
        if (type == ".chipsets:") {
            type = retrieveChipsets(file);
        }
        
        // Retrieving the links
        if (type == ".links:") {
            retrieveLinks(file);
            continue;
        }

        if (type[0])
            throw nts::Error("Parsing error: Unknow instruction '" + type + "'");
    }
    file.close();
}
