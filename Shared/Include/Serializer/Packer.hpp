//
// Created by aguado_e on 12/8/16.
//

#ifndef R_TYPE_IPACKER_HPP
#define R_TYPE_IPACKER_HPP

#include <string>
#include <vector>
#include <stdexcept>
#include "SerializationHelper.hpp"

namespace RType {

    enum SerializationType {
        WRITE,
        READ
    };

    constexpr short int udpMtu = 1500;

    class Packer {
    private:
        char *_buffer = nullptr;
        SerializationType _type;
        uint16_t _index = 0;

    public:
        Packer(RType::SerializationType type);

        Packer(SerializationType type, char *to_serialize);

        Packer(const RType::Packer &);

        Packer &operator=(const RType::Packer &);

        ~Packer();

        char *getBuffer() const;

        uint16_t getLength() const;

        template<typename T>
        void Pack(std::vector<T> &v) {
            if (_type == WRITE) {

                // Serialize size so we can get it back later
                size_t len = v.size();
                RType::SerializationHelper::Serialize(_buffer, _index, len);
                _index += sizeof(size_t);

                for (auto &&it : v) {
                    RType::SerializationHelper::Serialize(_buffer, _index, it);
                    _index += sizeof(T);
                }
            } else {
                size_t len;
                RType::SerializationHelper::Deserialize(_buffer, _index, len);
                _index += sizeof(size_t);
                if (v.size() < len)
                    v.resize(len);

                for (size_t i = 0; i < len; i++) {
                    RType::SerializationHelper::Deserialize(_buffer, _index, v[i]);
                    _index += sizeof(T);
                }
            }
        };

        template<typename T>
        void PackSerializables(std::vector<T> &v) {
            if (_type == WRITE) {

                // Serialize size so we can get it back later
                size_t len = v.size();
                RType::SerializationHelper::Serialize(_buffer, _index, len);
                _index += sizeof(size_t);

                for (auto &&it : v) {
                    it.Serialize(*this);
                }
            } else {
                size_t len;
                RType::SerializationHelper::Deserialize(_buffer, _index, len);
                _index += sizeof(size_t);
                if (v.size() < len)
                    v.resize(len);

                for (size_t i = 0; i < len; i++) {
                    v[i].Serialize(*this);
                }
            }
        };

        template<typename T>
        void Pack(T &v) {
            if (_type == WRITE)
                RType::SerializationHelper::Serialize(_buffer, _index, v);
            else
                RType::SerializationHelper::Deserialize(_buffer, _index, v);
            _index += sizeof(T);
        };

        void Pack(std::string &v) {
            if (_type == WRITE) {

                size_t len = v.length();
                RType::SerializationHelper::Serialize(_buffer, _index, len);
                _index += sizeof(size_t);

                for (auto &it : v) {
                    RType::SerializationHelper::Serialize(_buffer, _index, it);
                    _index += sizeof(char);
                }
            } else {
                size_t len = 0;
                RType::SerializationHelper::Deserialize(_buffer, _index, len);
                _index += sizeof(size_t);
                if (v.length() < len)
                    v.resize(len);

                for (size_t i = 0; i < len; i++) {
                    RType::SerializationHelper::Deserialize(_buffer, _index, v[i]);
                    _index += sizeof(char);
                }
            }
        }
    };
}

#endif //R_TYPE_IPACKER_HPP
