//
// Created by aguado_e on 12/8/16.
//

#ifndef R_TYPE_IPACKER_HPP
#define R_TYPE_IPACKER_HPP

#include <string>
#include <vector>

namespace RType {

  class IPacker {
  protected:
    virtual ~IPacker() {};

  public:

    // Since those methods are virtual, we can't use templates
    virtual void Pack(int32_t & v) = 0;
    virtual void Pack(std::vector<int32_t> & v) = 0;

    virtual void Pack(uint32_t & v) = 0;
    virtual void Pack(std::vector<uint32_t> & v) = 0;

    virtual void Pack(float & v) = 0;
    virtual void Pack(std::vector<float> & v) = 0;

    virtual void Pack(double & v) = 0;
    virtual void Pack(std::vector<double> & v) = 0;

    virtual void Pack(char & v) = 0;
    virtual void Pack(std::string & v) = 0;
  };
}

#endif //R_TYPE_IPACKER_HPP
