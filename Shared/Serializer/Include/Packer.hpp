//
// Created by aguado_e on 12/8/16.
//

#ifndef R_TYPE_IPACKER_HPP
#define R_TYPE_IPACKER_HPP

#include <string>
#include <vector>
#include "SerializationHelper.hpp"

namespace RType {
    enum SerializationType {
      WRITE,
      READ
    };

  class Packer {
  private:
    char *_buffer;
    uint16_t _index = 0;
    SerializationType _type;

  public:
    Packer(RType::SerializationType type) :
      _buffer(new char[1500]),
      _type(type)
    {};

    Packer(SerializationType type, char *to_serialize) :
      _type(type)
    {
      _buffer = to_serialize;
    };

    char *getBuffer() { return _buffer; };
    uint16_t getLength() { return _index; };

    template <typename T>
    void Pack(std::vector<T> & v) {
      if (_type == WRITE) {

        // Serialize size so we can get it back later
        size_t len = v.size();
        RType::SerializationHelper::Serialize(_buffer, _index, len);
        _index += sizeof(size_t);

        for (auto&& it : v) {
          RType::SerializationHelper::Serialize(_buffer, _index, it);
          _index += sizeof(T);
        }
      }
      else {
        size_t len;
        RType::SerializationHelper::Deserialize(_buffer, _index, len);
        _index += sizeof(size_t);
        assert(v.size() >= len && "Container is not large enough. This would cause a SIGSEGV.");

        for (size_t i = 0; i < len; i++) {
          RType::SerializationHelper::Deserialize(_buffer, _index, v[i]);
          _index += sizeof(T);
        }
      }
    };

    template <typename T>
    void Pack(T & v) {
      if (_type == WRITE)
        RType::SerializationHelper::Serialize(_buffer, _index, v);
      else
        RType::SerializationHelper::Deserialize(_buffer, _index, v);
      _index += sizeof(T);
    };

    // Special case for strings (which are not vectors but still containers)
    void Pack(std::string & v) {
      if (_type == WRITE) {

        size_t len = v.length();
        RType::SerializationHelper::Serialize(_buffer, _index, len);
        _index += sizeof(size_t);

        for (auto& it : v) {
          RType::SerializationHelper::Serialize(_buffer, _index, it);
          _index += sizeof(char);
        }
      }
      else {
        size_t len = 0;
        RType::SerializationHelper::Deserialize(_buffer, _index, len);
        _index += sizeof(size_t);
        assert(v.length() >= len && "Container is not large enough. This would cause a SIGSEGV.");

        for (size_t i = 0; i < len; i++) {
          RType::SerializationHelper::Deserialize(_buffer, _index, v[i]);
          _index += sizeof(char);
        }
      }
    }
  };
}

#endif //R_TYPE_IPACKER_HPP
