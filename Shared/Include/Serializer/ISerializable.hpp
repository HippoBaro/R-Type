//
// Created by aguado_e on 12/6/16.
//

#ifndef R_TYPE_ISERIALIZABLE_HPP
#define R_TYPE_ISERIALIZABLE_HPP

namespace RType {

    class Packer;

    class ISerializable {
    public:
        virtual ~ISerializable() {};

        virtual void Serialize(RType::Packer &packer) = 0;
    };
}

#include "Packer.hpp"

#endif //R_TYPE_ISERIALIZABLE_HPP
