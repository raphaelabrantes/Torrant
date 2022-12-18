// Copyright (c) Raphael Prandini Thome de Abrantes 2022

#include "BencodeDict.h"
#include "BencodeObject.h"

void BencodeDict::set(const std::string& key, const BencodeObject &becodeObject) {
    m_values[key] = becodeObject;
}

BencodeDict::BencodeDict(std::map<std::string, BencodeObject> becode_map) {
    m_values.merge(becode_map);
}

std::string BencodeDict::get_encoded() const {
    std::string encoded = "d";
    for(const auto& each: m_values){
        encoded += std::to_string(each.first.length()) + ":" + each.first;
        encoded += each.second.get_encoded();
    }
    encoded += "e";
    return encoded;
}
