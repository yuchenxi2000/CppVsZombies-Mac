#include "operation.hpp"
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
void PvZOperation::safeClick() {
    CGPoint point;
    point.x = windowPos.x;
    point.y = windowPos.y;
    Mouse::rightClickCoord(point);
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
void PvZOperation::plantSeed(int slot, const Coord & coord) {
    safeClick();
    selectSeed(slot);
    clickGrid(coord);
    clickGrid(coord);
    clickGrid(coord);
    safeClick();
}
void PvZOperation::fireCob(const Coord & grid, const Coord & firepos) {
    safeClick();
    CGPoint point = getPointFromCoord(grid);
    Mouse::clickCoord(point);
    Mouse::clickCoord(point);
    Mouse::clickCoord(point);
    
    CGPoint destination = getPointFromCoord(firepos);
    Mouse::clickCoord(destination);
    Mouse::clickCoord(destination);
    Mouse::clickCoord(destination);
    safeClick();
}
void PvZOperation::delayedFireCob(const Coord & grid, const Coord & firepos, int ms) {
    safeClick();
    CGPoint point = getPointFromCoord(grid);
    Mouse::clickCoord(point);
    Mouse::clickCoord(point);
    Mouse::clickCoord(point);
    usleep(ms);
    CGPoint destination = getPointFromCoord(firepos);
    Mouse::clickCoord(destination);
    Mouse::clickCoord(destination);
    Mouse::clickCoord(destination);
    safeClick();
}
