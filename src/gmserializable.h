#ifndef GMSERIALIZABLE_H
#define GMSERIALIZABLE_H

#include <string>
#include "gmobject.h"
class GMSerializable: public GMObject
{
public:
    virtual std::string serialize()=0;
    virtual GMObject* deserialize(std::string str)=0;
};
#endif // GMSERIALIZABLE_H
