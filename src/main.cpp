// Copyright (c) Raphael Prandini Thome de Abrantes 2022

#include <iostream>
#include "bencode/BencodeObject.h"

int main() {
    string str ("i-3e");
    BencodeObject becodeObject = std::move(BencodeObject::from_string(str));
    std::cout << "Hello, World!" << std::endl;
    return 0;
}