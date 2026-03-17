// Copyright (c) Raphael Prandini Thome de Abrantes 2026

#include "AnnounceSynchronizer.h"
#include <cryptopp/sha.h>
#include <iostream>
#include <boost/asio/io_context.hpp>


void AnnounceSynchronizer::sync() {
    for (const auto &tracker: m_trackers){
        retrive_peers(tracker);
    }

}

AnnounceSynchronizer::AnnounceSynchronizer(const BencodeObject &bencodeObject) {
    m_object = bencodeObject.as_dict().values();
    auto main_announcer = m_object.at("announce").as_string();
    m_trackers.insert(main_announcer);
    m_info_hash = generate_hash(m_object.at("info").get_encoded());
    m_escaped_hash = generate_hash_escaped(m_info_hash);
    if(m_object.contains("announce-list")){
        const auto announce_list = m_object.at("announce-list").as_list().values();
        for (auto const &item: announce_list){
            const auto list = item.as_list().values();
            for (const auto &x: list) {
                m_trackers.insert(x.as_string());
            }
        }
    }
    sync();
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

void AnnounceSynchronizer::retrive_peers(const std::string &tracker) {
        BencodeObject bencodeObject = m_tracker_client.get_result(tracker, m_escaped_hash);
        std::list<address> peer_list;
        if(bencodeObject.is_dict() && bencodeObject.as_dict().contains("peers")){
            auto peers = bencodeObject.as_dict().at("peers").as_string();
            for(int i = 0; i < peers.length(); i+=6){
                auto peer = get_peer(peers.substr(i, 6));
                m_addresses.insert(peer);
            }
        }

}

address AnnounceSynchronizer::get_peer(const std::string &peer) const {
    struct in_addr ip_adrr {0};
    ip_adrr.s_addr = ((u_int8_t)peer[0]) |((u_int8_t)peer[1] << 8) |((u_int8_t)peer[2] << 16) |((u_int8_t)peer[3] << 24);
    u_int16_t port_oc =  ((u_int8_t) peer[4] << 8) | (u_int8_t)peer[5];
    address addr {inet_ntoa(ip_adrr), port_oc};
    return addr;
}
