//
// Created by aguado_e on 12/6/16.
//

#ifndef R_TYPE_ISERIALIZABLE_HPP
#define R_TYPE_ISERIALIZABLE_HPP

#include "IPacker.hpp"

namespace RType {

  class ISerializable {
  public:
    virtual ~ISerializable() {};

    virtual void Serialize(RType::IPacker & packer) = 0;
  };
}

#endif //R_TYPE_ISERIALIZABLE_HPP
