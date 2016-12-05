//
// Created by aguado_e on 12/5/16.
//

#ifndef R_TYPE_ISERIALIZERBUFFER_HPP
#define R_TYPE_ISERIALIZERBUFFER_HPP

#include <cstdint>

namespace RType {
  template <uint32_t size>
  class ISerializerBuffer {
  protected:
    char _buffer[size];
    uint32_t _index = 0;

  public:
    template<typename Ttype>
    virtual void Pack(Ttype & value) = 0;
  };
}

#endif //R_TYPE_ISERIALIZERBUFFER_HPP
