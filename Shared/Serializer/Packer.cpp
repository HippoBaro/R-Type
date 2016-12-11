//
// Created by aguado_e on 12/11/16.
//

#include "Serializer/Packer.hpp"

RType::Packer::Packer(RType::SerializationType type) :
  _buffer(new char[1500]),
  _type(type)
{}

RType::Packer::Packer(RType::SerializationType type, char *to_serialize) :
  _type(type)
{
  _buffer = to_serialize;
}

RType::Packer::~Packer()
{
  if (_type == WRITE)
    delete _buffer;
}

char *RType::Packer::getBuffer()
{
  return _buffer;
}

uint16_t RType::Packer::getLength()
{
  return _index;
}

