/*
** EPITECH PROJECT, 2025
** Nts
** File description:
** Nts
*/

#pragma once

namespace nts
{
    enum Tristate {
        UNDEFINED = (-true),
        TRUE = true,
        FALSE = false
    };

    class Error : public std::exception {
        public:
            Error(const std::string &message) : _message(message) {}
            const char *what() const noexcept override { return _message.c_str(); }
        private:
            std::string _message;
    };
}
