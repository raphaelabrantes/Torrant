// Copyright (c) Raphael Prandini Thome de Abrantes 2022

#pragma once
#include <utility>
#include <vector>
#include "BencodeObject.h"

class BencodeObject;

class BencodeList {
public:
    explicit BencodeList(std::vector<BencodeObject> &values);
    std::vector<BencodeObject>& values();
private:
    std::vector<BencodeObject> m_values ;
};



