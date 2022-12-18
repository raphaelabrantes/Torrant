// Copyright (c) Raphael Prandini Thome de Abrantes 2022

#include <iostream>
#include "BencodeParser.h"

BencodeObject BencodeParser::parse() {
    auto type = peek();
    switch (type) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return string_helper();
        case 'i':
            return integer_helper();
        case 'l':
            return list_helper();
        case 'd':
            return dict_helper();
        default:
            throw std::exception();
    }
}

char BencodeParser::peek(int offset) const {
    return (m_index + offset < m_input.length()) ? m_input[m_index + offset] : '\0';
}

std::string BencodeParser::consume(size_t count) {
    auto result = m_input.substr(m_index, count);
    m_index += count;
    return result;
}

BencodeObject BencodeParser::string_helper() {
    size_t string_size = get_size();
    increment();
    return BencodeObject{consume(string_size)};
}

size_t BencodeParser::get_size(char until) {
    size_t string_size = 0;
    char c;
    while((c = peek())!= until){
        if(!isdigit(c)) {
            throw std::exception();
        }
        string_size = (string_size * 10) + c - '0';
        increment();
    }
    return string_size;
}

BencodeObject BencodeParser::integer_helper() {
    increment();
    bool negative = false;
    if(peek() == '-'){
        negative = true;
        increment();
    }
    size_t value = get_size('e');
    increment();
    return BencodeObject( negative? -1 * value : value);
}

BencodeObject BencodeParser::list_helper() {
    increment();
    std::list<BencodeObject> becode_objects;
    while (peek() != 'e'){
        auto object = parse();
        becode_objects.push_back(object);
    }
    increment();
    BencodeList becode_list(becode_objects);
    return BencodeObject{becode_list};
}

BencodeObject BencodeParser::dict_helper() {
    increment();
    BencodeDict becode_dict;
    while (peek() != 'e'){
        auto size = get_size();
        increment();
        auto key = consume(size);
        //FIXME : Find a way to work with the correct amount of charecters
        if(key != std::string("pieces")){
            auto value = parse();
            becode_dict.set(key, value);
        } else{
            auto index = m_input.find("e6:locale");
            if(index == std::string::npos){
                throw std::exception();
            }
            auto value = BencodeObject{consume(index - m_index)};
            becode_dict.set(key, value);
        }
    }
    increment();
    return BencodeObject {becode_dict};
}
