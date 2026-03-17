// Copyright (c) Raphael Prandini Thome de Abrantes 2023

#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "Piece.h"
#include "bencode/BencodeObject.h"
#define HASH_SIZE 20

class PieceManager {
public:
    explicit PieceManager(BencodeDict &InfoDic);

    Piece get_piece_info(int index);

private:
    bool is_single_file;
    std::unordered_map<std::string, std::pair<BencodeObject, Piece::Status>> m_pieces_map;
     std::vector<Piece> m_pieces_list;
    uint64_t pieces_amount;

};