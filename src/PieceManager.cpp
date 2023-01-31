// Copyright (c) Raphael Prandini Thome de Abrantes 2023

#include <iostream>
#include "PieceManager.h"

std::string PieceManager::add_piece(const std::string &md5) {
    if (m_pieces_map.contains(md5)){
        m_pieces_map.at(md5).second = Status::Acquired;
    }
    return md5;
}

PieceManager::PieceManager(const BencodeObject &piecesObject) {
    if (piecesObject.is_list()) {
        auto pieces = piecesObject.as_list().values();
        for (auto &item: pieces) {
            auto md5 = item.as_dict().at("md5").as_string();
            m_pieces_map[md5] = std::pair<BencodeObject, Status>(item, Status::NotAcquired);
        }
    } else {
        throw std::exception();
    }
}

std::string PieceManager::get_random_piece() {
    // FIXME: HORRIBLE
    for (auto &item: m_pieces_map){
        if(item.second.second == Status::NotAcquired){
            item.second.second = Status::Searching;
            return item.second.first.as_string();
        }
    }
    return {};
}

std::string PieceManager::get_piece_info(const std::string &md5) {
    if(m_pieces_map.contains(md5)){
        return m_pieces_map.at(md5).first.get_encoded();
    }
    return {};
}

void PieceManager::failed_to_retrive_info(const std::string& md5) {
    if(m_pieces_map.contains(md5) &&  m_pieces_map.at(md5).second == Status::Searching){
        m_pieces_map.at(md5).second = Status::NotAcquired;
    }
}
