#include "mouse.hpp"
#include "pvz-class.h"
#include <AppKit/AppKit.h>
CGPoint Mouse::getMouseLocation() {
    NSPoint p = [NSEvent mouseLocation];
    return {p.x, desktopSize.y-p.y};
}
