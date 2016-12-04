//
// Created by aguado_e on 11/30/16.
//

#ifndef R_TYPE_SERIALIZER_HPP
#define R_TYPE_SERIALIZER_HPP


#include <string>
#include <assert.h>

namespace RType {

  class ISerializable {
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

    int deserializationIndex = 0; // TODO: find a better way than this. Maybe an InitDeserialization ?

  protected:
    virtual std::string SerializeEntity() = 0;
    virtual std::string DeserializeEntity() = 0;

    template <typename Ttype>
    Ttype Deserialize() final {
      Ttype tmp = *(Ttype*)_serializationBuffer.buffer;
      deserializationIndex += sizeof(Ttype);
      return tmp;
    }

    template <typename Ttype>
    void Serialize(Ttype value) final {
      assert(_serializationBuffer.currentSize + sizeof(Ttype) <= _udpMtu);

      // TODO: this can be done at compile time IMO
      if (IsBigEndian()) {
        if (sizeof(Ttype) == 1) // 1 byte => no swap needed
          *((Ttype*)(_serializationBuffer.buffer + _serializationBuffer.currentSize)) = value;

        else if (sizeof(Ttype) == 2) // 2 bytes
          *((Ttype*)(_serializationBuffer.buffer + _serializationBuffer.currentSize)) = __bswap_16(value);

        else if (sizeof(Ttype) == 4) // 4 bytes
          *((Ttype*)(_serializationBuffer.buffer + _serializationBuffer.currentSize)) = __bswap_32(value);

        else if (sizeof(Ttype) == 8) // 8 bytes => extrem case
          *((Ttype*)(_serializationBuffer.buffer + _serializationBuffer.currentSize)) = __bswap_64(value);
      }

      else
        *((Ttype*)(_serializationBuffer.buffer + _serializationBuffer.currentSize)) = value;
      _serializationBuffer.currentSize += sizeof(Ttype);
    };
  };
}


#endif //R_TYPE_SERIALIZER_HPP
