// Copyright (c) Raphael Prandini Thome de Abrantes 2026

#pragma once
#include <string>


class Piece {
public:
    enum class Status {
        Acquired,
        NotAcquired,
        Searching,
    };
    explicit Piece(const std::string& sha1) {
        this->m_sha1 = sha1;
    };
    explicit Piece(const std::string& sha1, const Status status) {
        this->m_status = status;
        this->m_sha1 = sha1;
    };
    void set_status(const Status status) {
        this->m_status = status;
    };
    [[nodiscard]] Status get_status() const {
        return this->m_status;
    };
    [[nodiscard]] std::string get_sha1() const {
        return this->m_sha1;
    };


private:

    Status m_status = Status::NotAcquired;
    std::string m_sha1;



};

