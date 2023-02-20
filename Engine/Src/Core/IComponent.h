//
// Created by wiktor on 04.02.23.
//

#ifndef WIKENGINE_ICOMPONENT_H
#define WIKENGINE_ICOMPONENT_H


#include <string>

class IComponent {
public:
    virtual std::string GetComponentType() = 0;
};


#endif //WIKENGINE_ICOMPONENT_H
