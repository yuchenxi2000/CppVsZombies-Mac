#include "pvz-class.h"

PvZCannon::PvZCannon() {
    GetCannonOnLawn();
};

PvZCannon::~PvZCannon() {
    
}

void PvZCannon::GetCannonOnLawn() {
    int total = pvz.PlantsMaxCount();
    for (int i = 0; i < total; ++i) {
        int id = pvz.GetPlantID(i);
        if (id == 47 && pvz.PlantAlive(i)) {
            Cannon cannon;
            cannon.index = i;
            cannon.position.col = pvz.GetPlantCol(i);
            cannon.position.row = pvz.GetPlantRow(i);
            cannonlist.push_back(cannon);
        }
    }
}

void PvZCannon::GetCannonFromList(std::initializer_list<Coord> ls) {
    int total = pvz.PlantsMaxCount();
    for (const auto & cob : ls) {
        bool cannon_found = false;
        for (int i = 0; i < total; ++i) {
            if (pvz.GetPlantID(i) == 47 && pvz.PlantAlive(i) && cob.col == pvz.GetPlantCol(i) && cob.row == pvz.GetPlantRow(i)) {
                Cannon cannon;
                cannon.position = cob;
                cannon.index = i;
                cannonlist.push_back(cannon);
                cannon_found = true;
                break;
            }
        }
        if (!cannon_found) {
            printf("cannon not exist: row %f col %f\n", cob.row, cob.col);
            exit(666);
        }
    }
}

void PvZCannon::UpdatePaoList() {
    curindex = 0;
    cannonlist.clear();
    GetCannonOnLawn();
}

void PvZCannon::UpdatePaoList(std::initializer_list<Coord> ls) {
    curindex = 0;
    cannonlist.clear();
    if (ls.size() > 0) {
        GetCannonFromList(ls);
    }
}

void PvZCannon::SkipPao(int num) {
    curindex += num;
    curindex %= cannonlist.size();
}

void PvZCannon::DelayedFire(const Coord & firepos, int cs) {
    std::lock_guard<std::mutex> lkg(mouse_lock);
    int previndex = curindex;
    int cobs = (int)cannonlist.size();
    while (true) {
        const Cannon & cannon = cannonlist[curindex];
        if (!pvz.PlantAlive(cannon.index)) {
            std::cout << "Oops! your cannon died!" << std::endl;
            std::cout << "I'd better run away..." << std::endl;
            exit(233);
        }
        if (pvz.GetCannonState(cannon.index) == cob_ready) {
            operation.safeDelayedFireCob(cannon.position, firepos, cs * 10000);
            return;
        }
        
        ++curindex;
        if (curindex >= cobs) {
            curindex = 0;
        }
        if (curindex >= previndex) {
            break;
        }
    }
}

void PvZCannon::Fire(std::initializer_list<Coord> firepos) {
    std::lock_guard<std::mutex> lkg(mouse_lock);
    SafeClick safeclick;
    int previndex = curindex;
    int cobs = (int)cannonlist.size();
    int firecnt = 0;
    std::initializer_list<Coord>::iterator pos = firepos.begin();
    while (true) {
        const Cannon & cannon = cannonlist[curindex];
        if (!pvz.PlantAlive(cannon.index)) {
            std::cout << "Oops! your cannon died!" << std::endl;
            std::cout << "I'd better run away..." << std::endl;
            exit(233);
        }
        if (pvz.GetCannonState(cannon.index) == cob_ready) {
            if (pos == firepos.end()) {
                break;
            }
            CGPoint point;
            point.x = windowPos.x;
            point.y = windowPos.y;
            Mouse::rightClickCoord(point);
            operation.fireCob(cannon.position, *pos);
            Mouse::rightClickCoord(point);
            ++pos;
            ++firecnt;
        }
        
        ++curindex;
        if (curindex >= cobs) {
            curindex = 0;
        }
        if (curindex == previndex) {
            break;
        }
    }
    int left = (int)firepos.size() - firecnt;
    if (left > 0) {
        std::cout << "What? " << left << " cannon(s) should be ready..." << std::endl;
    }
}

void PvZCannon::Fire(const Coord & cob, const Coord & firepos) {
    std::lock_guard<std::mutex> lkg(mouse_lock);
    operation.safeFireCob(cob, firepos);
}
