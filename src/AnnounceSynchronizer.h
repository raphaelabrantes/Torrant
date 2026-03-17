// Copyright (c) Raphael Prandini Thome de Abrantes 2026

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

    std::set<address> get_announced_addresses();

    void sync();

private:
    static std::string generate_hash(const std::string &info_encoded);

    static std::string generate_hash_escaped(const std::string &hash_info);

    void retrive_peers(const std::string &tracker);

    address get_peer(const std::string& peer) const;

    std::map<std::string,BencodeObject>m_object;
    TrackerClient m_tracker_client;
    std::set<std::string> m_trackers;
    std::set<address> m_addresses;
    std::string m_info_hash;
    std::string m_escaped_hash;
};
