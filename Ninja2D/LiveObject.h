#pragma once
#include "BaseObject.h"
class LiveObject :
    public BaseObject
{
protected:
    int life;
    int clock;
public:
    LiveObject();
    ~LiveObject();


    virtual void MoveLeft();
    virtual void MoveRight();
    virtual void MoveUp();
    virtual void MoveDown();
    virtual bool IsGoLeft();
    virtual bool IsGoRight();
    virtual bool CheckDeath();
    virtual void MakeAnimation();

};

