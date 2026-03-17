// Copyright (c) Raphael Prandini Thome de Abrantes 2026

#include <iostream>
#include <fstream>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <boost/beast/core.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "bencode/BencodeObject.h"
#include "AnnounceSynchronizer.h"
#include "PieceManager.h"




int main() {
    std::ifstream metafile("tests/words.torrent");
    std::stringstream buffer;
    buffer << metafile.rdbuf();
    std::string metafile_contents = buffer.str();
    BencodeObject becode_object = BencodeObject::from_string(metafile_contents);
    BencodeDict info = becode_object
        .as_dict()
        .at("info")
        .as_dict();
    PieceManager piece_manager(info);
    AnnounceSynchronizer announce_synchronizer(becode_object);
    Server server(piece_manager, announce_synchronizer);
    return 0;
}