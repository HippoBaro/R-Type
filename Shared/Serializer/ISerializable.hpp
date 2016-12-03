//
// Created by aguado_e on 11/30/16.
//

#ifndef R_TYPE_SERIALIZER_HPP
#define R_TYPE_SERIALIZER_HPP


#include <string>
#include <assert.h>

namespace RType {

  class ISerializsable {
  private:
      virtual ~ISerializable() {};

    // TODO : determine if this should be done at compile time or at runtime
    constexpr bool IsBigEndian() {
      uint32_t i = 0x01020304; // i = 1234
      char b[4];
      *(uint32_t*)(b) = i; // Put in char* to access each byte
      return b[0] == 1; // if first is biggest => little endian
    }

    constexpr static short int _udpMtu = 508;

    struct {
      char buffer[_udpMtu] = {'\0'};
      int currentSize = 0;
    } _serializationBuffer;

  protected:
    virtual std::string Serialize() = 0;

    void SerializeInt(uint32_t value) final {
      assert(_serializationBuffer.currentSize + sizeof(uint32_t) <= 508);
      if (IsBigEndian())
        *((uint32_t*)(_serializationBuffer.buffer + _serializationBuffer.currentSize)) = __bswap_32(value);
      else
        *((uint32_t*)(_serializationBuffer.buffer + _serializationBuffer.currentSize)) = value;
      _serializationBuffer.currentSize += sizeof(uint32_t);
    };
  };
}


#endif //R_TYPE_SERIALIZER_HPP
