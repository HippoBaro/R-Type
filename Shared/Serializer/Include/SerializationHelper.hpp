//
// Created by aguado_e on 12/5/16.
//

#ifndef R_TYPE_SERIALIZATIONHELPER_HPP
#define R_TYPE_SERIALIZATIONHELPER_HPP

#include <iostream>
#include <assert.h>

namespace RType {
  namespace SerializationHelper {
    bool _IsBigEndian();

    template <typename Ttype>
    void Serialize(char *buffer, uint32_t index, Ttype & value)
    {
      if (RType::SerializationHelper::_IsBigEndian()) {
        if (sizeof(Ttype) == 1) // 1 byte => no swap needed
          *((Ttype*)(buffer + index)) = value;

        else if (sizeof(Ttype) == 2) // 2 bytes
          *((Ttype*)(buffer + index)) = __bswap_16(value);

        else if (sizeof(Ttype) == 4) // 4 bytes
          *((Ttype*)(buffer + index)) = __bswap_32(value);

        else if (sizeof(Ttype) == 8) // 8 bytes
          *((Ttype*)(buffer + index)) = __bswap_64(value);
      }
      else
        *((Ttype*)(buffer + index)) = value;
    }

    template <typename Ttype>
    void Deserialize(char *buffer, uint32_t index, Ttype & value)
    {
      value = *((Ttype*)(buffer + index));
    }
  }
}


#endif //R_TYPE_SERIALIZATIONHELPER_HPP
