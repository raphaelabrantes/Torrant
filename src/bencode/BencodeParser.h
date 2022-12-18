// Copyright (c) Raphael Prandini Thome de Abrantes 2022

#pragma once
#include <string>
#include <utility>
#include "BencodeObject.h"


class BencodeParser {
public:
    explicit BencodeParser(std::string input): m_input(std::move(input)){};
    BencodeObject parse();
    std::string consume(size_t count);

private:
    char peek(int offset = 0) const;
    inline void increment() { m_index++;}
    size_t m_index { 0 };
    std::string m_input;

    BencodeObject string_helper();

    BencodeObject integer_helper();

    size_t get_size(char until = ':');

    BencodeObject list_helper();

    BencodeObject dict_helper();
};
