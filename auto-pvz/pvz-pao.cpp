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

void PvZCannon::DelayedFire(const Coord & firepos, int cs) {
    std::lock_guard<std::mutex> lkg(mouse_lock);
    
    int i = 0;
    int cobs = cannonlist.size();
    while (i < cobs) {
        const Cannon & cannon = cannonlist[i];
        if (!pvz.PlantAlive(cannon.index)) {
            std::cout << "Oops! your cannon died!" << std::endl;
            std::cout << "I'd better run away..." << std::endl;
            exit(233);
        }
        if (pvz.GetCannonState(cannon.index) == cob_ready) {
            printf("fire!\n");
            std::cout << "row: " << cannon.position.row << " col: " << cannon.position.col << std::endl;
            operation.delayedFireCob(cannon.position, firepos, cs * 10000);
            return;
        }else {
            ++i;
            continue;
        }
    }
}

void PvZCannon::Fire(std::initializer_list<Coord> firepos) {
    std::lock_guard<std::mutex> lkg(mouse_lock);
    SafeClick safeclick;
    int i = 0;
    int cobs = cannonlist.size();
    int firecnt = 0;
    for (const Coord & pos : firepos) {
        while (i < cobs) {
            const Cannon & cannon = cannonlist[i];
            if (!pvz.PlantAlive(cannon.index)) {
                std::cout << "Oops! your cannon died!" << std::endl;
                std::cout << "I'd better run away..." << std::endl;
                exit(233);
            }
            if (pvz.GetCannonState(cannon.index) == cob_ready) {
                ++firecnt;
                operation.fireCob(cannon.position, pos);
//                Fire(cannon.position, pos);
                ++i;
                break;
            }else {
                ++i;
                continue;
            }
        }
    }
    int left = firepos.size() - firecnt;
    if (left > 0) {
        std::cout << "What? " << left << " cannon(s) should be ready..." << std::endl;
    }
}

void PvZCannon::Fire(const Coord & cob, const Coord & firepos) {
    std::lock_guard<std::mutex> lkg(mouse_lock);
    operation.safeFireCob(cob, firepos);
}
