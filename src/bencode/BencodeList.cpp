// Copyright (c) Raphael Prandini Thome de Abrantes 2022

#include "BencodeList.h"

#include <utility>
#include "BencodeObject.h"


BencodeList::BencodeList(const std::list<BencodeObject>& values):
    m_values(values) {}

std::list<BencodeObject>& BencodeList::values() {
    return m_values;
}

std::string BencodeList::get_encoded() const {
    std::string enconded = "l" ;
    for(auto each: m_values){
        enconded += each.get_encoded();
    }
    enconded+='e';
    return enconded;
}
