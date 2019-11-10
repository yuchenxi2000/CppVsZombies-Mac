#ifndef operation_hpp
#define operation_hpp

#include <iostream>
#include "mouse.hpp"
#include "pvz-class.h"

class SafeClick {
    CGPoint originPos;
public:
    SafeClick();
    ~SafeClick();
};

class PvZOperation {
    CGPoint getPointFromCoord(const Coord & coord);
public:
    void selectSeed(int slot);
    void clickGrid(const Coord & coord);
    void plantSeed(int slot, const Coord & coord);
    void safeFireCob(const Coord & grid, const Coord & firepos);
    void fireCob(const Coord & grid, const Coord & firepos);
    void delayedFireCob(const Coord & grid, const Coord & firepos, int ms);
};

#endif /* operation_hpp */
