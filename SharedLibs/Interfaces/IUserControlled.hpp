//
// Created by Hippolyte Barraud on 24/12/2016.
//

#ifndef R_TYPE_IUSERCONTROLLED_HPP
#define R_TYPE_IUSERCONTROLLED_HPP

#include <Messages/UserInputMessage.hpp>

class IUserControlled {
public:
    virtual void Action(UserEventType event) = 0;
};

#endif //R_TYPE_IUSERCONTROLLED_HPP
