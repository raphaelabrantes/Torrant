// Copyright (c) Raphael Prandini Thome de Abrantes 2022

#pragma once
#include <utility>
#include <list>
#include "BencodeObject.h"

class BencodeObject;

class BencodeList {
public:
    explicit BencodeList(const std::list<BencodeObject> &values);
    std::list<BencodeObject>& values();
    std::string get_encoded() const;
    std::string get_beautiful() const;

private:
    std::list<BencodeObject> m_values ;
};



