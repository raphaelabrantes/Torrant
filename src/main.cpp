// Copyright (c) Raphael Prandini Thome de Abrantes 2022

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
    std::ifstream metafile("tests/archlinux-2025.01.01-x86_64.iso.torrent");
    std::stringstream buffer;
    buffer << metafile.rdbuf();
    std::string metafile_contents = buffer.str();
    BencodeObject becode_object = BencodeObject::from_string(metafile_contents);
    PieceManager piece_manager(becode_object.as_dict().at("info").as_dict().at("files"));
    AnnounceSynchronizer announce_synchronizer(becode_object);
    announce_synchronizer.exec();
    return 0;
}