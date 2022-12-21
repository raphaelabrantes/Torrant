// Copyright (c) Raphael Prandini Thome de Abrantes 2022

#pragma once
#include <string>
#include <memory>
#include "BencodeList.h"
#include "BencodeDict.h"

class BencodeList;
class BencodeDict;

class BencodeObject {
public:

    explicit BencodeObject() = default;
    explicit BencodeObject(const BencodeDict&);
    explicit BencodeObject(const BencodeList&);
    explicit BencodeObject(int64_t);
    explicit BencodeObject(const std::string &);

    BencodeObject(BencodeObject const&);
    BencodeObject(BencodeObject&&);

    BencodeObject& operator=(BencodeObject const&);
    BencodeObject& operator=(BencodeObject&&);

    ~BencodeObject();

    enum class Type{
        UNKOWN,
        String,
        Integer,
        List,
        Dict,
    };
    static BencodeObject from_string(const std::string &);

    Type type() const { return m_type; }
    bool is_string() const { return m_type == Type::String; }
    bool is_integer() const { return m_type == Type::Integer; }
    bool is_list() const { return  m_type == Type::List; }
    bool is_dict() const { return  m_type == Type::Dict; }
    std::string as_string() const;
    int64_t as_integer() const;
    BencodeList as_list() const;
    BencodeDict as_dict() const;
    std::string get_encoded() const;
    std::string get_beautiful() const;


private:
    void clear();
    void copy_from(BencodeObject const&);
    Type m_type {};
    union {
        std::string* as_string {nullptr};
        int64_t as_integer;
        BencodeList* as_list;
        BencodeDict* as_dict;
    } m_value;
};
