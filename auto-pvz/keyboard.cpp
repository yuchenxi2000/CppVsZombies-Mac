#include "keyboard.hpp"
KeyBoard::KeyBoard() {
    eventkeyup = CGEventCreateKeyboardEvent(0, (CGKeyCode)kVK_Space, true);
    eventkeydown = CGEventCreateKeyboardEvent(0, (CGKeyCode)kVK_Space, false);
}
void KeyBoard::PressSpace() {
    CGEventPost(kCGSessionEventTap, eventkeyup);
    CGEventPost(kCGSessionEventTap, eventkeydown);
}
