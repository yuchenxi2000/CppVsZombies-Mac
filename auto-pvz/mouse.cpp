#include "mouse.hpp"
void Mouse::clickCoord(const CGPoint & point) {
    CGEventRef ref = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, point, kCGMouseButtonLeft);
    CGEventSetIntegerValueField(ref, kCGMouseEventClickState, 1);
    CGEventPost(kCGSessionEventTap, ref);
    CGEventSetType(ref, kCGEventLeftMouseUp);
    CGEventPost(kCGSessionEventTap, ref);
    CFRelease(ref);
}
void Mouse::rightClickCoord(const CGPoint & point) {
    CGEventRef ref = CGEventCreateMouseEvent(NULL, kCGEventRightMouseDown, point, kCGMouseButtonRight);
    CGEventPost(kCGSessionEventTap, ref);
    CGEventSetType(ref, kCGEventRightMouseUp);
    CGEventPost(kCGSessionEventTap, ref);
    CFRelease(ref);
}
void Mouse::delayedClickCoord(const CGPoint & point, int ms) {
    CGEventRef ref = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, point, kCGMouseButtonLeft);
    CGEventSetIntegerValueField(ref, kCGMouseEventClickState, 1);
    CGEventPost(kCGSessionEventTap, ref);
    usleep(ms);
    CGEventSetType(ref, kCGEventLeftMouseUp);
    CGEventPost(kCGSessionEventTap, ref);
    CFRelease(ref);
}
void Mouse::delayedRightClickCoord(const CGPoint & point, int ms) {
    CGEventRef ref = CGEventCreateMouseEvent(NULL, kCGEventRightMouseDown, point, kCGMouseButtonRight);
    CGEventSetIntegerValueField(ref, kCGMouseEventClickState, 1);
    CGEventPost(kCGSessionEventTap, ref);
    usleep(ms);
    CGEventSetType(ref, kCGEventLeftMouseUp);
    CGEventPost(kCGSessionEventTap, ref);
    CFRelease(ref);
}
