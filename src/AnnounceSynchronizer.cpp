// Copyright (c) Raphael Prandini Thome de Abrantes 2023

#include "AnnounceSynchronizer.h"
#include <cryptopp/sha.h>
#include <boost/asio/post.hpp>
#include <iostream>

std::string AnnounceSynchronizer::add_peer(const std::string &basicString) {
    return std::string();
}

void AnnounceSynchronizer::exec() {
    for (const auto &tracker: trackers){
        std::list<address> retrived_peers = retrive_peers(tracker);
        for (const auto &item: retrived_peers){
            addresses.insert(item);
        }
    }
    pool = new boost::asio::thread_pool(addresses.size());
    for (auto &address: addresses){
        boost::asio::post(*pool, [&address]() {
            // TODO: Implement peer worker
        });
    }

}

AnnounceSynchronizer::AnnounceSynchronizer(const BencodeObject &bencodeObject) {
    object = bencodeObject.as_dict().values();
    auto main_announcer = object.at("announce").as_string();
    trackers.insert(main_announcer);
    info_hash = generate_hash(object.at("info").get_encoded());
    escaped_hash = generate_hash_escaped(info_hash);
    if(object.contains("announce-list")){
        const auto announce_list = object.at("announce-list").as_list().values();
        for (auto const &item: announce_list){
            const auto list = item.as_list().values();
            for (const auto &x: list) {
                trackers.insert(x.as_string());
            }
        }
    }
}

std::string AnnounceSynchronizer::generate_hash(const std::string &info_encoded) {
    CryptoPP::SHA1 hash;
    hash.Update((const unsigned char*)info_encoded.data(), info_encoded.size());
    std::string digest;
    digest.resize(hash.DigestSize());
    hash.Final((unsigned char *)&digest[0]);
    return digest;
}

std::string AnnounceSynchronizer::generate_hash_escaped(const std::string &hash_info) {
    std::string meta_hash_escaped;
    for (auto item: hash_info){
        if(std::isalnum(item, std::locale::classic())){
            meta_hash_escaped+=item;
        }else{
            char x [2];
            sprintf(x, "%x", (uint8_t)item);
            meta_hash_escaped+= "%" + (x[1]? std::string(x): std::string("0") + std::string(x));
        }
    }
    return meta_hash_escaped;
}

std::list<address> AnnounceSynchronizer::retrive_peers(const std::string &tracker) const {
        BencodeObject bencodeObject = tracker_client.get_result(tracker, escaped_hash);
        std::list<address> peer_list;
        if(bencodeObject.is_dict() && bencodeObject.as_dict().contains("peers")){
            auto peers = bencodeObject.as_dict().at("peers").as_string();
            for(int i = 0; i < peers.length(); i+=6){
                auto peer = get_peer(peers.substr(i, 6));
                peer_list.push_back(peer);
            }
        }
    return peer_list;

}

address AnnounceSynchronizer::get_peer(const std::string &peer) const {
    struct in_addr ip_adrr {0};
    ip_adrr.s_addr = ((u_int8_t)peer[0]) |((u_int8_t)peer[1] << 8) |((u_int8_t)peer[2] << 16) |((u_int8_t)peer[3] << 24);
    u_int16_t port_oc =  ((u_int8_t) peer[4] << 8) | (u_int8_t)peer[5];
    address addr {inet_ntoa(ip_adrr), port_oc};
    return addr;
}
