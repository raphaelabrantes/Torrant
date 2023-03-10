// Copyright (c) Raphael Prandini Thome de Abrantes 2022

#include <cassert>
#include "BencodeObject.h"
#include "BencodeParser.h"

BencodeObject BencodeObject::from_string(const std::string &input) {
    return BencodeParser(input).parse();
}

std::string BencodeObject::as_string() const {
    assert(is_string());
    return *m_value.as_string ;
}

int64_t BencodeObject::as_integer() const {
    assert(is_integer());
    return m_value.as_integer;
}


BencodeList BencodeObject::as_list() const {
    assert(is_list());
    return *m_value.as_list;
}

BencodeDict BencodeObject::as_dict() const {
    assert(is_dict());
    return *m_value.as_dict;
}

BencodeObject::BencodeObject(const BencodeList&  becodeList): m_type(Type::List) {
    m_value.as_list = new BencodeList(becodeList);
}

BencodeObject::BencodeObject(const BencodeDict& becodeDict): m_type(Type::Dict) {
    m_value.as_dict = new BencodeDict(becodeDict.values());

}

BencodeObject::BencodeObject(int64_t integer): m_type(Type::Integer) {
    m_value.as_integer = integer;
}

BencodeObject::BencodeObject(const std::string & str): m_type(Type::String){
    m_value.as_string = new std::string(str);
}

BencodeObject::BencodeObject(const BencodeObject &other) {
    copy_from(other);

}

void BencodeObject::copy_from(const BencodeObject &other) {
    m_type = other.m_type;
    switch (m_type) {
        case Type::String:
            m_value.as_string = other.m_value.as_string;
            break;
        case Type::Integer:
            m_value.as_integer = other.m_value.as_integer;
            break;
        case Type::List:
            m_value.as_list = new BencodeList(*other.m_value.as_list);
            break;
        case Type::Dict:
            m_value.as_dict = new BencodeDict(*other.m_value.as_dict);
            break;
        default:
            throw std::exception();

    }
}

BencodeObject &BencodeObject::operator=(const BencodeObject &other) {
    if(this != &other){
        clear();
        copy_from(other);
    }
    return *this;
}

BencodeObject::~BencodeObject() {
    clear();
}

void BencodeObject::clear() {
    switch (m_type) {
        case Type::String:
            std::destroy(m_value.as_string->begin(), m_value.as_string->end());
            m_type = Type::UNKOWN;
            break;
        case Type::List:
            m_type = Type::UNKOWN;
            delete m_value.as_list;
            break;
        case Type::Dict:
            m_type = Type::UNKOWN;
            delete m_value.as_dict;
            break;
        default:
            break;
    }
}

BencodeObject::BencodeObject(BencodeObject && other) {
    m_type = std::exchange(other.m_type, Type::UNKOWN);
    m_value.as_integer = std::exchange(other.m_value.as_integer, 0);

}

BencodeObject &BencodeObject::operator=(BencodeObject && other) {
    if (this != &other) {
        clear();
        m_type = std::exchange(other.m_type, Type::UNKOWN);
        m_value.as_integer = std::exchange(other.m_value.as_integer, 0);
    }
    return *this;
}

std::string BencodeObject::get_encoded() const {
    std::string encoded;
    switch(m_type){
        case Type::String:
            encoded = std::to_string(as_string().length()) + ":" + as_string();
            break;
        case Type::Integer:
            encoded =  "i" + std::to_string(as_integer()) + "e";
            break;
        case Type::List:
            encoded = as_list().get_encoded();
            break;
        case Type::Dict:
            encoded = as_dict().get_encoded();
            break;
        default:
            break;
    }
    return encoded;
}

std::string BencodeObject::get_beautiful() const {
    std::string beautiful;
    switch(m_type){
        case Type::String:
            beautiful =  "\"" + as_string() + "\"";
            break;
        case Type::Integer:
            beautiful = std::to_string(as_integer()) ;
            break;
        case Type::List:
            beautiful = as_list().get_beautiful();
            break;
        case Type::Dict:
            beautiful = as_dict().get_beautiful();
            break;
        default:
            break;
    }
    return beautiful;}
