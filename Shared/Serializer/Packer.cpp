//
// Created by aguado_e on 12/11/16.
//

#include <cstring>
#include "Serializer/Packer.hpp"

RType::Packer::Packer(RType::SerializationType type) :
  _buffer(new char[udpMtu]),
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

RType::Packer::Packer(const RType::Packer & copy) :
  _buffer(new char[udpMtu]),
  _type(copy._type),
  _index(copy._index)
{
  std::memcpy(this->_buffer, copy._buffer, udpMtu);
}

RType::Packer & RType::Packer::operator=(const RType::Packer & rhs)
{
  this->_type = rhs._type;
  this->_index = rhs._index;
  this->_buffer = new char[udpMtu];
  std::memcpy(this->_buffer, rhs._buffer, udpMtu);
  return *this;
}

