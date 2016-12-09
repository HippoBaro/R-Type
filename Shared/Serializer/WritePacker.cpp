//
// Created by aguado_e on 12/8/16.
//

#include <cstring>
#include "Include/WritePacker.hpp"

RType::WritePacker::WritePacker(uint32_t bufferSize) :
  _buffer(new char[bufferSize]),
  _capacity(bufferSize)
{}

RType::WritePacker::~WritePacker()
{
  delete _buffer;
}

char *RType::WritePacker::getBuffer()
{
  return _buffer;
};


void RType::WritePacker::Pack(int32_t & v) {
  assert(_index + sizeof(int32_t) < _capacity);
  RType::SerializationHelper::Serialize(_buffer, _index, v);
  _index += sizeof(int32_t);
}
void RType::WritePacker::Pack(std::vector<int32_t> & v)
{
  for (auto&& it : v)
    this->Pack(it);
}


void RType::WritePacker::Pack(uint32_t & v) {
  assert(_index + sizeof(uint32_t) < _capacity);
  RType::SerializationHelper::Serialize(_buffer, _index, v);
  _index += sizeof(uint32_t);
}
void RType::WritePacker::Pack(std::vector<uint32_t> & v)
{
  for (auto&& it : v)
    this->Pack(it);
}


void RType::WritePacker::Pack(float & v) {
  assert(_index + sizeof(float) < _capacity);
  RType::SerializationHelper::Serialize(_buffer, _index, v);
  _index += sizeof(float);
}
void RType::WritePacker::Pack(std::vector<float> & v)
{
  for (auto&& it : v)
    this->Pack(it);
}


void RType::WritePacker::Pack(double & v) {
  assert(_index + sizeof(double) < _capacity);
  RType::SerializationHelper::Serialize(_buffer, _index, v);
  _index += sizeof(double);
}
void RType::WritePacker::Pack(std::vector<double> & v)
{
  for (auto&& it : v)
    this->Pack(it);
}


void RType::WritePacker::Pack(char & v) {
  assert(_index + sizeof(char) < _capacity);
  RType::SerializationHelper::Serialize(_buffer, _index, v);
  _index += sizeof(char);
}
void RType::WritePacker::Pack(std::string & v) {
  for (auto&& it : v)
    this->Pack(it);
}
