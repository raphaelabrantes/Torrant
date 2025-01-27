// Copyright (c) Raphael Prandini Thome de Abrantes 2022

#include "BencodeList.h"

#include "BencodeObject.h"


BencodeList::BencodeList(const std::list<BencodeObject>& values):
    m_values(values) {}

std::list<BencodeObject>& BencodeList::values() {
    return m_values;
}

std::string BencodeList::get_encoded() const {
    std::string enconded = "l" ;
    for(const auto& each: m_values){
        enconded += each.get_encoded();
    }
    enconded+='e';
    return enconded;
}

std::string BencodeList::get_beautiful() const {
    std::string beautiful = "[";
    for(const auto& each: m_values){
        beautiful += " " + each.get_beautiful() + " ";
    }
    beautiful += "]\n";
    return beautiful;
}
