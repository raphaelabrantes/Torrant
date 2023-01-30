// Copyright (c) Raphael Prandini Thome de Abrantes 2023

#pragma once

#include <boost/asio/thread_pool.hpp>
#include <set>
#include "TrackerClient.h"

struct address {
    std::string ip;
    u_int16_t port;
};

inline bool operator<(const address& lhs, const address& rhs){
    return lhs.ip < rhs.ip || lhs.port < rhs.port;
}

class AnnounceSynchronizer {

public:
    explicit AnnounceSynchronizer(const BencodeObject &bencodeObject);

    std::string add_peer(const std::string &basicString);

    void exec();

private:
    static std::string generate_hash(const std::string &info_encoded);

    static std::string generate_hash_escaped(const std::string &hash_info);

    std::list<address> retrive_peers(const std::string &tracker) const;

    address get_peer(const std::string& peer) const;

    std::map<std::string,BencodeObject>object;
    boost::asio::thread_pool *pool;
    TrackerClient tracker_client;
    std::set<std::string> trackers;
    std::set<address> addresses;
    std::string info_hash;
    std::string escaped_hash;
};
