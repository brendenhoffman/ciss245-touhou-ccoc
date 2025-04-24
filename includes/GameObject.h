// Brenden Hoffman
// p01
// GameObject.h
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject {
public:
    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
};
#endif
