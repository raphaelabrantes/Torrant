// Copyright (c) Raphael Prandini Thome de Abrantes 2022

#include "BencodeDict.h"
#include "BencodeObject.h"

void BencodeDict::set(const std::string& key, const BencodeObject &becodeObject) {
    m_values[key] = becodeObject;
}

BencodeDict::BencodeDict(std::map<std::string, BencodeObject> becode_map) {
    m_values.merge(becode_map);
}
