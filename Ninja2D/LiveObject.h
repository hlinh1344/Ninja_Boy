#pragma once
#include "BaseObject.h"
class LiveObject :
    public BaseObject
{
protected:

    bool isDead;
    int life;

public:
    LiveObject();
    ~LiveObject();


    virtual void MoveLeft();
    virtual void MoveRight();
    virtual void MoveUp();
    virtual void MoveDown();
    virtual bool IsGoLeft();
    virtual bool IsGoRight();
    virtual int GetWidth();
    virtual int GetHeight();
    virtual void SetDeath(bool a_isDead);
    virtual bool CheckDeath();

};

