#ifndef keyboard_hpp
#define keyboard_hpp

#include <iostream>
#include <CoreGraphics/CoreGraphics.h>
#include <Carbon/Carbon.h>
class KeyBoard {
    CGEventRef eventkeyup;
    CGEventRef eventkeydown;
public:
    KeyBoard();
    void PressSpace();
};

#endif /* keyboard_hpp */
