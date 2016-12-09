//
// Created by aguado_e on 12/8/16.
//

#ifndef R_TYPE_WRITEPACKER_HPP
#define R_TYPE_WRITEPACKER_HPP

#include "IPacker.hpp"
#include "SerializationHelper.hpp"

namespace RType {
  class WritePacker : public RType::IPacker {
  private:
    char *_buffer;
    uint32_t _index = 0;
    uint32_t _capacity;

  public:
    WritePacker(uint32_t bufferSize);
    ~WritePacker();

    char *getBuffer();

    virtual void Pack(int32_t & v) override final;
    virtual void Pack(std::vector<int32_t> & v) override final;

    virtual void Pack(uint32_t & v) override final;
    virtual void Pack(std::vector<uint32_t> & v) override final;

    virtual void Pack(float & v) override final;
    virtual void Pack(std::vector<float> & v) override final;

    virtual void Pack(double & v) override final;
    virtual void Pack(std::vector<double> & v) override final;

    virtual void Pack(char & v) override final;
    virtual void Pack(std::string & v) override final;

  };
}


#endif //R_TYPE_WRITEPACKER_HPP
