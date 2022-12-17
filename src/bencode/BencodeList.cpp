// Copyright (c) Raphael Prandini Thome de Abrantes 2022

#include "BencodeList.h"

#include <utility>
#include "BencodeObject.h"


BencodeList::BencodeList(std::vector<BencodeObject>& values): m_values(std::move(values)) {}

std::vector<BencodeObject>& BencodeList::values(){
    return m_values ;
}

