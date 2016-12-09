//
// Created by aguado_e on 12/8/16.
//

#include "Include/ReadPacker.hpp"

RType::ReadPacker::ReadPacker(char * buffer) :
  _buffer(buffer) {}


void RType::ReadPacker::Pack(int32_t & v)
{
  RType::SerializationHelper::Deserialize(_buffer, _index, v);
  _index += sizeof(int32_t);
}
void RType::ReadPacker::Pack(std::vector<int32_t> & v)
{
  for (auto&& it : v)
    this->Pack(it);
}


void RType::ReadPacker::Pack(uint32_t & v)
{
  RType::SerializationHelper::Deserialize(_buffer, _index, v);
  _index += sizeof(uint32_t);
}
void RType::ReadPacker::Pack(std::vector<uint32_t> & v)
{
  for (auto&& it : v)
    this->Pack(it);
}


void RType::ReadPacker::Pack(float & v)
{
  RType::SerializationHelper::Deserialize(_buffer, _index, v);
  _index += sizeof(float);
}
void RType::ReadPacker::Pack(std::vector<float> & v)
{
  for (auto&& it : v)
    this->Pack(it);
}


void RType::ReadPacker::Pack(double & v)
{
  RType::SerializationHelper::Deserialize(_buffer, _index, v);
  _index += sizeof(double);
}
void RType::ReadPacker::Pack(std::vector<double> & v)
{
  for (auto&& it : v)
    this->Pack(it);
}


void RType::ReadPacker::Pack(char & v) {
  RType::SerializationHelper::Deserialize(_buffer, _index, v);
  _index += sizeof(char);
}
void RType::ReadPacker::Pack(std::string & v) {
  for (auto&& it : v)
    this->Pack(it);
}
