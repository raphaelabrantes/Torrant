// Copyright (c) Raphael Prandini Thome de Abrantes 2022

#include <iostream>
#include <fstream>
#include <sstream>
#include "bencode/BencodeObject.h"


int main() {
    std::ifstream metafile("tests/alice_in_wonderland_librivox_archive.torrent");
    std::stringstream buffer;
    buffer << metafile.rdbuf();
    BencodeObject becodeObject = BencodeObject::from_string(buffer.str());
    if(becodeObject.is_dict() && !becodeObject.as_dict().values().empty()){
        auto dict = becodeObject.as_dict().values();
        auto announce_url = dict.at("announce").as_string();
    }
    return 0;
}