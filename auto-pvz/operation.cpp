#include "operation.hpp"
SafeClick::SafeClick() {
    originPos = Mouse::getMouseLocation();
    CGPoint point;
    point.x = windowPos.x;
    point.y = windowPos.y;
    Mouse::rightClickCoord(point);
}
SafeClick::~SafeClick() {
    CGPoint point;
    point.x = windowPos.x;
    point.y = windowPos.y;
    Mouse::rightClickCoord(point);
    CGEventRef ref = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved, originPos, kCGMouseButtonRight);
    CGEventPost(kCGSessionEventTap, ref);
    CFRelease(ref);
}
CGPoint PvZOperation::getPointFromCoord(const Coord & coord) {
    CGPoint point;
    point.x = 80 * coord.col;
    if (scene == 2 || scene == 3) {
        point.y = 55 + 85 * coord.row;
    }else if (scene == 4 || scene == 5) {
        if (coord.col >= 6) {
            point.y = 45 + 85 * coord.row;
        }else {
            point.y = 45 + 85 * coord.row + 20 * (6 - coord.col);
        }
    }else {
        point.y = 40 + 100 * coord.row;
    }
    point.x += windowPos.x;
    point.y += windowPos.y;
    return point;
}
void PvZOperation::selectSeed(int slot) {
    CGPoint point;
    point.x = 63 + 51 * slot;
    point.y = 12;
    
    point.x += windowPos.x;
    point.y += windowPos.y;
    Mouse::clickCoord(point);
}
void PvZOperation::clickGrid(const Coord & coord) {
    CGPoint point = getPointFromCoord(coord);
    Mouse::clickCoord(point);
}
void PvZOperation::safePlantSeed(int slot, const Coord & coord) {
    SafeClick safeclick;
    selectSeed(slot);
    CGPoint point = getPointFromCoord(coord);
    Mouse::clickCoord(point);
    Mouse::clickCoord(point);
    Mouse::clickCoord(point);
}
void PvZOperation::safeShovelPlant(const Coord & coord) {
    SafeClick safeclick;
    CGPoint shovel;
    shovel.x = 640 + windowPos.x;
    shovel.y = 36 + windowPos.y;
    Mouse::clickCoord(shovel);
    CGPoint point = getPointFromCoord(coord);
    Mouse::clickCoord(point);
    Mouse::clickCoord(point);
    Mouse::clickCoord(point);
}
void PvZOperation::safeFireCob(const Coord & grid, const Coord & firepos) {
    SafeClick safeclick;
    CGPoint point = getPointFromCoord(grid);
    Mouse::clickCoord(point);
    Mouse::clickCoord(point);
    Mouse::clickCoord(point);
    CGPoint destination = getPointFromCoord(firepos);
    Mouse::clickCoord(destination);
    Mouse::clickCoord(destination);
    Mouse::clickCoord(destination);
}
void PvZOperation::fireCob(const Coord & grid, const Coord & firepos) {
    CGPoint point = getPointFromCoord(grid);
    Mouse::clickCoord(point);
    Mouse::clickCoord(point);
    Mouse::clickCoord(point);
    CGPoint destination = getPointFromCoord(firepos);
    Mouse::clickCoord(destination);
    Mouse::clickCoord(destination);
    Mouse::clickCoord(destination);
}
void PvZOperation::safeDelayedFireCob(const Coord & grid, const Coord & firepos, int ms) {
    SafeClick safeclick;
    CGPoint point = getPointFromCoord(grid);
    Mouse::clickCoord(point);
    Mouse::clickCoord(point);
    Mouse::clickCoord(point);
    usleep(ms);
    CGPoint destination = getPointFromCoord(firepos);
    Mouse::clickCoord(destination);
    Mouse::clickCoord(destination);
    Mouse::clickCoord(destination);
}
