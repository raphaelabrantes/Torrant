// Copyright (c) Raphael Prandini Thome de Abrantes 2026


#include "Server.h"

#include <iostream>
#include <boost/asio/connect.hpp>
#include <boost/asio/write.hpp>


std::string Server::generate_handshake_package(const std::string& hash_info, const std::string& host_id) {
    std::string data;
    data.push_back(0x13);
    data += "BitTorrent protocol";
    data.append(8, 0x0);
    data.append(hash_info);
    data.append(host_id);
    return data;
}

char keep_alive[4]  = { 0, 0, 0, 0 };
char choke [5] = {0, 0, 0, 1, 0};
char unchoke [5] = {0, 0, 0, 1, 1};
char interested [5] = {0, 0, 0, 1, 2};
char not_interested [5] = {0, 0, 0, 1, 3};
char have [5] = {0, 0, 0, 5, 4};


boost::optional<connection> Server::create_connection(const std::string &handshake_package, const std::string &ip, u_int16_t port) {
    try {
        boost::asio::ip::tcp::socket socket(m_io_context);
        const boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address(ip), port);
        boost::asio::ip::tcp::resolver resolver(m_io_context);
        boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(endpoint);

        boost::asio::connect(socket, endpoints);
        socket.write_some(boost::asio::buffer(handshake_package));

        std::array<char, 68> buf{};
        size_t len = socket.read_some(boost::asio::buffer(buf));
        std::string connected(buf.data(), len);
        const std::string client = connected.substr(48);
        std::cout << "connected to: "  << std::endl;

        return std::move(connection{&socket, client});

    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return boost::none;
    }
}


void Server::start_file_distribution(connection &connection) {
    // auto wanted_piece = m_piece_manager.get_wanted_piece();
    // boost::optional<> piece = ask_piece(connection, wanted_piece);
    // if (piece) {
    //     save(piece);
    //     m_piece_manager.set_piece_acquired(wanted_piece);
    // } else {
    //     m_piece_manager.return_piece_to_queue(piece);
    // }

}

void Server::exec() {
    const auto handshake = generate_handshake_package(m_announce_synchronizer.get_info_hash(), "-RP0001-EEJs5CQi7kyN");

    for (const auto& [ip, port]: m_announce_synchronizer.get_peers()) {
        auto connection = create_connection(handshake, ip, port);
        if (connection.is_initialized()) {
            start_file_distribution(*connection);
        }
    }


}


