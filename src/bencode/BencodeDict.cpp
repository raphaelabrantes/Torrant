#include "BencodeDict.h"
#include "BencodeObject.h"

void BencodeDict::set(string key, BencodeObject &becodeObject) {
    m_values[key] = std::move(becodeObject);
}

BencodeDict::BencodeDict(std::map<string, BencodeObject> becode_map) {
    m_values.merge(becode_map);

}
