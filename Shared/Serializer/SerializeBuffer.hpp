//
// Created by aguado_e on 12/5/16.
//

#ifndef R_TYPE_SERIALIZEBUFFER_HPP
#define R_TYPE_SERIALIZEBUFFER_HPP


#include "ISerializerBuffer.hpp"

namespace RType {
  class SerializeBuffer : public ISerializerBuffer {
  public:
    template <typename Ttype>
    virtual void Pack(Ttype & value) override final;
  };
}


#endif //R_TYPE_SERIALIZEBUFFER_HPP
