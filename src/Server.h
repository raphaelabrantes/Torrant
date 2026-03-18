// Copyright (c) Raphael Prandini Thome de Abrantes 2026

#pragma once
#include <boost/asio/io_context.hpp>

#include "AnnounceSynchronizer.h"
#include "PieceManager.h"





class Server {
public:
    Server() = default;
    Server(const PieceManager & piece_manager, const AnnounceSynchronizer & announce_synchronizer): m_piece_manager(piece_manager), m_announce_synchronizer(announce_synchronizer) {};
    void exec();
private:
    PieceManager m_piece_manager;
    AnnounceSynchronizer m_announce_synchronizer;
    boost::asio::io_context m_io_context;
};

