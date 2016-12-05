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
    enum SerializationType {
      SERIALIZE,
      DESERIALIZE
    };


    // TODO : Needs to be done at compile time instead of run time
    bool IsBigEndian() {
      short int i = 0x010;
      char b[4];
      *(short int *) (b) = i;
      return b[0] == 1;
    }

    static const int _udpMtu = 508;

    struct { // TODO: this is used by the both serialization AND the deserialization
             // TODO: There must be a better way
      char buffer[_udpMtu] = {'\0'};
      int currentSize = 0;
    } _serializationBuffer;

    int deserializationIndex = 0; // TODO: find a better way than this. Maybe an InitDeserialization ?

  protected:
    virtual std::string SerializeEntity() = 0;

    template <typename Ttype>
    Ttype Deserialize() final {
      Ttype tmp = *(Ttype*)_serializationBuffer.buffer;
      deserializationIndex += sizeof(Ttype);
      return tmp;
    }

    // TODO: read shouldn't read on the class' values. Should have a char[508] parameter

    /*
     * TODO : There will be only one serialize function with a ActionType
     * This function will call e.g  SerializeInt(ActionType::Serialize, value)
     * Each function will implement the 2 behaviors (read and write) and will choose upon ActionType
    */
    template <typename Ttype, SerializationType type>
    void SerializeBis(Ttype value) final {
      if (type == SERIALIZE)
        Serialize<Ttype>(value);
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

        else if (sizeof(Ttype) == 8) // 8 bytes => extreme case
          *((Ttype*)(_serializationBuffer.buffer + _serializationBuffer.currentSize)) = __bswap_64(value);
      }

      else
        *((Ttype*)(_serializationBuffer.buffer + _serializationBuffer.currentSize)) = value;
      _serializationBuffer.currentSize += sizeof(Ttype);
    };
  };
}


#endif //R_TYPE_SERIALIZER_HPP
