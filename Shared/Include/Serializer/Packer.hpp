//
// Created by aguado_e on 12/8/16.
//

#ifndef R_TYPE_IPACKER_HPP
#define R_TYPE_IPACKER_HPP

#include <string>
#include <vector>
#include <stdexcept>
#include <cstring>
#include <set>
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
        Packer(RType::SerializationType type) :
                _buffer(new char[udpMtu]),
                _type(type)
        {}

        Packer(RType::SerializationType type, char *to_serialize) :
                _type(type)
        {
            _buffer = to_serialize;
        }

        Packer(const RType::Packer & copy) :
                _buffer(new char[udpMtu]),
                _type(copy._type),
                _index(copy._index)
        {
            std::memcpy(this->_buffer, copy._buffer, udpMtu);
        }

        Packer &operator=(const RType::Packer & rhs)
        {
            this->_type = rhs._type;
            this->_index = rhs._index;
            this->_buffer = new char[udpMtu];
            std::memcpy(this->_buffer, rhs._buffer, udpMtu);
            return *this;
        }

        ~Packer()
        {
            if (_type == WRITE)
                delete[] _buffer;
        }

        SerializationType getType() const {
            return _type;
        }

        char *getBuffer() const
        {
            return _buffer;
        }

        uint16_t getLength() const
        {
            return _index;
        }

        template<typename T>
        void Pack(std::vector<T> &v, bool append = false) {
            if (_type == WRITE) {

                // Serialize size so we can get it back later
                uint32_t len = (uint32_t) v.size();
                RType::SerializationHelper::Serialize(_buffer, _index, len);
                _index += sizeof(uint32_t);

                for (auto &it : v) {
                    RType::SerializationHelper::Serialize(_buffer, _index, it);
                    _index += sizeof(T);
                }
            } else {
                uint32_t len;
                RType::SerializationHelper::Deserialize(_buffer, _index, len);
                _index += sizeof(uint32_t);

                if (!append)
                    v.clear();

                for (size_t i = 0; i < len; i++) {
                    T val;

                    RType::SerializationHelper::Deserialize(_buffer, _index, val);
                    v.push_back(val);
                    _index += sizeof(T);
                }
            }
        }

        template<typename T>
        void Pack(std::set<T> &v, bool append = false) {
            if (_type == WRITE) {

                // Serialize size so we can get it back later
                uint32_t len = (uint32_t) v.size();
                RType::SerializationHelper::Serialize(_buffer, _index, len);
                _index += sizeof(uint32_t);

                for (auto &it : v) {
                    RType::SerializationHelper::Serialize(_buffer, _index, it);
                    _index += sizeof(T);
                }
            } else {
                uint32_t len;
                RType::SerializationHelper::Deserialize(_buffer, _index, len);
                _index += sizeof(uint32_t);

                if (!append) v.clear();

                for (size_t i = 0; i < len; i++) {
                    T val;

                    RType::SerializationHelper::Deserialize(_buffer, _index, val);
                    v.insert(val);
                    _index += sizeof(T);
                }
            }
        }

        template<typename T>
        void PackSerializables(std::vector<T> &v) {
            if (_type == WRITE) {

                // Serialize size so we can get it back later
                size_t len = v.size();
                RType::SerializationHelper::Serialize(_buffer, _index, len);
                _index += sizeof(size_t);

                for (auto &&it : v)
                    it.Serialize(*this);
            } else {
                size_t len;
                RType::SerializationHelper::Deserialize(_buffer, _index, len);
                _index += sizeof(size_t);
                if (v.size() < len)
                    v.resize(len);

                for (size_t i = 0; i < len; i++)
                    v[i].Serialize(*this);
            }
        }

        template<typename T>
        void Pack(T &v) {
            if (_type == WRITE)
                RType::SerializationHelper::Serialize(_buffer, _index, v);
            else
                RType::SerializationHelper::Deserialize(_buffer, _index, v);
            _index += sizeof(T);
        }

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
