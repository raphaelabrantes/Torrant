// Copyright (c) Raphael Prandini Thome de Abrantes 2023
#pragma once
#include "bencode/BencodeObject.h"

class TrackerClient {

public:
    TrackerClient() = default;

    BencodeObject get_result(const std::string &tracker, const std::string &escaped_hash) const;
private:
    const std::string request_format = "/%1%?peer_id=%2%&info_hash=%3%&port=%4%&left=%5%&downloaded=%6%&uploaded=%7%&compact=1&event=%8%";

};
