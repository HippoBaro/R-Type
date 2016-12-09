//
// Created by aguado_e on 12/6/16.
//

#include <gtest/gtest.h>
#include <ISerializable.hpp>
#include <WritePacker.hpp>
#include <ReadPacker.hpp>

class Player : RType::ISerializable {
public:
  uint32_t life = 300;
  std::vector<int> test = {1, 2, 3, 4};

  virtual void Serialize(RType::IPacker & packer) override {
    packer.Pack(life);
    packer.Pack(test);
  }
};


TEST(Tests_Socket, TCP_Socket) {
  Player toto;

  RType::WritePacker wpacker(50);

  toto.Serialize(wpacker);
  RType::ReadPacker rpacker(wpacker.getBuffer());
  toto.life = 250;
  toto.test = {4, 5, 6, 6};

  toto.Serialize(rpacker);

//  ASSERT_EQ(toto.life, 300);
  ASSERT_EQ(toto.test[0], 1);
}