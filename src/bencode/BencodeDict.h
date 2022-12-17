// Copyright (c) Raphael Prandini Thome de Abrantes 2022

#pragma once
#include <map>
#include <string>
#include "BencodeObject.h"

class BencodeObject;

using std::map;
using std::string;

class BencodeDict {
public:
    BencodeDict(std::map<string, BencodeObject> becode_map);
    BencodeDict() = default;
    void set(string key, BencodeObject& becodeObject);

    map<string, BencodeObject> values() const { return m_values; }
private:
    map<string, BencodeObject> m_values;
};
