// Copyright (c) Raphael Prandini Thome de Abrantes 2026


#include "Server.h"

#include <iostream>
#include <boost/asio/connect.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/ip/tcp.hpp>


std::string get_handshake(std::string hash_info, std::string host_id) {
    std::string data;
    data.push_back(0x13);
    data += "BitTorrent protocol";
    data.append(8, 0x0);
    data.append(hash_info);
    data.append(host_id);
    return data;
}


void Server::exec() {
    try {
        auto [ip, port] = m_announce_synchronizer.get_peers().at(0);

        boost::asio::ip::tcp::acceptor acceptor(m_io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 6881));
        boost::asio::ip::tcp::socket socket(m_io_context);
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address(ip), port);
        boost::asio::ip::tcp::resolver resolver(m_io_context);
        boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(endpoint);

        boost::system::error_code error;
        boost::asio::connect(socket, endpoints);

        auto handshake = get_handshake(m_announce_synchronizer.get_info_hash(), "-RP0001-EEJs5CQi7kyN");

        socket.write_some(boost::asio::buffer(handshake), error);

        std::array<char, 68> buf;
        size_t len = socket.read_some(boost::asio::buffer(buf), error);
        std::string connected(buf.data(), len);
        std::cout << "connected to: " << connected.substr(48) << std::endl;

    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

}


