// Copyright (c) Raphael Prandini Thome de Abrantes 2026

#pragma once
#include <unordered_set>
#include <boost/asio/io_context.hpp>
#include <boost/optional.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "AnnounceSynchronizer.h"
#include "PieceManager.h"


struct connection {
    boost::asio::ip::tcp::socket *socket;
    std::string client;
    bool isConnected;
    connection(boost::asio::ip::tcp::socket *socket, const std::string &client) : socket(socket), client(client), isConnected(false) {};
    bool operator==(const connection& other) const { return client == other.client; };
};


template<>
struct std::hash<connection> {
    std::size_t operator()(const connection &c) const noexcept {
        return std::hash<std::string>()(c.client);
    }
};

class Server {
public:
    Server() = delete;
    Server(const PieceManager & piece_manager, const AnnounceSynchronizer & announce_synchronizer):
        m_piece_manager(piece_manager),
        m_announce_synchronizer(announce_synchronizer) {};

    void start_file_distribution(connection &connection);

    void exec();
private:
    static std::string generate_handshake_package(const std::string &hash_info, const std::string &host_id);
    boost::optional<connection> create_connection(const std::string & handshake, const std::string & ip, u_int16_t port);

    PieceManager m_piece_manager;
    AnnounceSynchronizer m_announce_synchronizer;
    boost::asio::io_context m_io_context;
    std::unordered_set<connection> m_connections = std::unordered_set<connection>();

};

