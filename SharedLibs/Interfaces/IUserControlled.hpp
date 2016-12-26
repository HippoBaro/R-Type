//
// Created by Hippolyte Barraud on 24/12/2016.
//

#ifndef R_TYPE_IUSERCONTROLLED_HPP
#define R_TYPE_IUSERCONTROLLED_HPP

#include <Messages/UserInputMessage.hpp>

class IUserControlled {
public:
    virtual void Action(std::set<UserEventType> events) = 0;

    virtual ~IUserControlled() {}
};

#endif //R_TYPE_IUSERCONTROLLED_HPP
