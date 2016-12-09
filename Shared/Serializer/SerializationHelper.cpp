//
// Created by aguado_e on 12/9/16.
//

#include "Include/SerializationHelper.hpp"

bool RType::SerializationHelper::_IsBigEndian()
{
  short int i = 0x0102;
  char b[2];
  *(short int *) (b) = i;
  return b[0] == 1;
}