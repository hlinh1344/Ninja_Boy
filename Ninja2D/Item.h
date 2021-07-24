#pragma once
#include "BaseObject.h"
class Item : public BaseObject
{
protected:
    int typeOfWeapn;
    bool isDead;
public:
    Item();
    ~Item();

    int GetTypeOfWeapn();
    bool CheckDeath();
   
};

