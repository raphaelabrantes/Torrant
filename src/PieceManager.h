// Copyright (c) Raphael Prandini Thome de Abrantes 2023

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "bencode/BencodeObject.h"


class PieceManager {
public:
    explicit PieceManager(const BencodeObject &piecesObject);

    std::string get_piece_info(const std::string &basicString);

    std::string add_piece(const std::string &basicString);

    void failed_to_retrive_info(const std::string &md5);

    std::string get_random_piece();

private:
    enum class Status {
        Acquired,
        NotAcquired,
        Searching,
    };

    std::unordered_map<std::string, std::pair<BencodeObject, Status>> m_pieces_map;

};