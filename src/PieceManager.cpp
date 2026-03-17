// Copyright (c) Raphael Prandini Thome de Abrantes 2026

#include <iostream>
#include "PieceManager.h"

#include <assert.h>
#include <cmath>


PieceManager::PieceManager(BencodeDict &info_dic) {
    auto pieces_object = info_dic.orElse("files", "pieces");

    if (pieces_object.is_string()) {
        is_single_file = true;
        const auto pieces = pieces_object.as_string();
        const auto length = info_dic.at("length").as_integer();
        const auto pieces_size = info_dic.at("piece length").as_integer();
        pieces_amount = std::ceil(length / static_cast<float>(pieces_size));


        for (int i = 0; i < pieces_amount; i += 1) {
            auto basic_string = pieces.substr(i*HASH_SIZE, (i + 1 )*HASH_SIZE);
            Piece piece(basic_string);
            m_pieces_list.push_back(piece);
        }
    }

    if (pieces_object.is_list()) {
        // TODO: REFINE
        //     auto pieces = piecesObject.as_list().values();
        //     for (auto &item: pieces) {
        //         auto md5 = item.as_dict().at("md5").as_string();
        //         m_pieces_map[md5] = std::pair<BencodeObject, Status>(item, Status::NotAcquired);
        //     }
        // } else {
        //     throw std::exception();
    }
}

Piece PieceManager::get_piece_info(int index) {
    return m_pieces_list.at(index);
}

