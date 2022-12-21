// Copyright (c) Raphael Prandini Thome de Abrantes 2022

#pragma once
#include <map>
#include <string>
#include "BencodeObject.h"

class BencodeObject;


class BencodeDict {
public:
    explicit BencodeDict(std::map<std::string, BencodeObject> becode_map);
    BencodeDict() = default;
    void set(const std::string& key, const BencodeObject& becodeObject);
    BencodeObject at(const std::string& key) const;
    std::string get_encoded() const;
    std::map<std::string, BencodeObject> values() const { return m_values; }
    std::string get_beautiful() const;

private:
    std::map<std::string, BencodeObject> m_values;
};
