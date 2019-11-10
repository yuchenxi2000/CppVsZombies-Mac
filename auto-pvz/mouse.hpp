#ifndef mouse_hpp
#define mouse_hpp

#include <iostream>
#include <CoreGraphics/CoreGraphics.h>
struct Coord {
    union {
        struct {
            float row, col;
        };
        struct {
            float y, x;
        };
    };
};
class Mouse {
public:
    static CGPoint getMouseLocation();
    static void clickCoord(const CGPoint & point);
    static void rightClickCoord(const CGPoint & point);
    static void delayedClickCoord(const CGPoint & point, int ms);
    static void delayedRightClickCoord(const CGPoint & point, int ms);
};

#endif /* mouse_hpp */
