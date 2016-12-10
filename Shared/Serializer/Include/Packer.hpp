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
    uint32_t _index = 0;
    SerializationType _type;

  public:
    Packer(RType::SerializationType type) :
      _buffer(new char[1500]),
      _type(type)
    {};

    Packer(SerializationType type, char *to_serialize) : _type(type)
    {
      _buffer = to_serialize;
    };

    char *getBuffer() { return _buffer; };

    // For containers
    template <typename T>
    void Pack(std::vector<T> & v) {
      if (_type == WRITE)
        for (auto&& it : v)
        {
          RType::SerializationHelper::Serialize(_buffer, _index, it);
          _index += sizeof(T);
        }
      else
        for (auto&& it : v)
        {
          RType::SerializationHelper::Deserialize(_buffer, _index, it);
          _index += sizeof(T);
        }
    };

    // The rest
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
      if (_type == WRITE)
        for (auto& it : v) {
          RType::SerializationHelper::Serialize(_buffer, _index, it);
          _index += sizeof(char);
        }
      else
        for (auto&& it : v) {
          RType::SerializationHelper::Deserialize(_buffer, _index, it);
          _index += sizeof(char);
        }
    }
  };
}

#endif //R_TYPE_IPACKER_HPP
