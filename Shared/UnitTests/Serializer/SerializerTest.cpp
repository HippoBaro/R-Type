//
// Created by aguado_e on 12/6/16.
//

#include <gtest/gtest.h>
#include <ISerializable.hpp>
#include <bitset>

class Player : RType::ISerializable {
public:
  int life = 300;
  std::vector<int> position = {42, -24, 1, 2, 4, 5, 6};

  int score = 12000;
  std::vector<int> high = {1234, 2345};

  std::vector<int> test = {1, 2, 3, 4, 5};

  float damage = 12.45f;

  char letter = 'a';
  std::string name = "this is my name";

  virtual void Serialize(RType::Packer & packer) override {
    packer.Pack(life);
    packer.Pack(position);
    packer.Pack(score);
    packer.Pack(high);
    packer.Pack(test);
    packer.Pack(damage);
    packer.Pack(letter);
    packer.Pack(name);
  }
};


TEST(Tests_Serialization, SerializerTest) {
  Player toto;
  RType::Packer wpacker(RType::WRITE);
  toto.Serialize(wpacker);

  RType::Packer rpacker(RType::READ, wpacker.getBuffer());

  toto.life = 250;
  toto.position[0] = 12;
  toto.position[1] = 32;
  toto.score = 0;
  toto.high[0] = 1;
  toto.high[1] = 2;
  toto.high.push_back(980);
  toto.damage = 0.23f;
  toto.letter = 'T';
  toto.name = "Hello World !";

  toto.Serialize(rpacker);

  ASSERT_EQ(toto.life, 300);
  ASSERT_EQ(toto.position[0], 42);
  ASSERT_EQ(toto.position[1], -24);
  ASSERT_EQ(toto.score, 12000);
  ASSERT_EQ(toto.high[0], 1234);
  ASSERT_EQ(toto.high[1], 2345);
  ASSERT_FLOAT_EQ(toto.damage, 12.45);
  ASSERT_EQ(toto.letter, 'a');
  ASSERT_STREQ(toto.name.c_str(), "this is my name");
}

