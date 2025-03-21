/*
** EPITECH PROJECT, 2025
** Main
** File description:
** Main
*/

#include "AllComponents.hpp"
#include "Parsing/Parser.hpp"
#include "Shell/Shell.hpp"

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: ./nanotekspice [file]" << std::endl;
        return 84;
    }
    nts::Circuit circuit;
    std::string filename = argv[1];
    nts::Parser parser(circuit, filename);

    // Testing the parser
    try {
        parser.parse();
    } catch (const nts::Error &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    // Testing the shell
    nts::Shell shell(circuit.getComponents());
    shell.run();

    return 0;
}
