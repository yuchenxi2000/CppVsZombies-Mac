#include "pvz-class.h"

GridIceInfo GetGridInfo(const Coord & pos) {
    int total_plant = pvz.PlantsMaxCount();
    bool hasIce = false, hasCoffee = false;
    for (int i = 0; i < total_plant; ++i) {
        if (pvz.GetPlantRow(i) == pos.row && pvz.GetPlantCol(i) == pos.col && pvz.PlantAlive(i)) {
            int id = pvz.GetPlantID(i);
            if (id == 14) {
                hasIce = true;
            }else if (id == 35) {
                hasCoffee = true;
            }else if (id != 16 && id != 33 && id != 30) {
                return HASPLANT;
            }
        }
    }
    if (hasIce) {
        if (hasCoffee) {
            return HASPLANT;
        }else {
            return HASICE;
        }
    }else {
        return CANPLANTICE;
    }
}

PvZIce::PvZIce() {
    GetIceSlot();
}

PvZIce::~PvZIce() {
    
}

void PvZIce::GetIceSlot() {
    coffeeSlot = 0;
    int slotCnt = pvz.GetSlotCount();
    for (int i = 1; i <= slotCnt; ++i) {
        int id = pvz.GetSlotID(i);
        if (id == 14 || (id == 48 && pvz.GetSlotImitatorID(i) == 14)) {
            iceSlot.push_back(i);
        }else if (id == 35 || (id == 48 && pvz.GetSlotImitatorID(i) == 35)) {
            coffeeSlot = i;
        }
    }
}

void PvZIce::SetIcePos(std::initializer_list<Coord> ls) {
    for (const Coord & pos : ls) {
        Ice ice;
        ice.position = pos;
        ice.gridinfo = GetGridInfo(pos);
        icePos.push_back(ice);
    }
}

int ice_precision = 100000;

void _AutoFillIce() {
    // coffee->ice : 298
    if (pvzice.iceSlot.empty() || pvzice.icePos.empty() || pvzice.coffeeSlot == 0) {
        return;
    }
    while (true) {
        for (int slot : pvzice.iceSlot) {
            int cd = pvz.GetSlotCD(slot);
            if (cd == 0) {
                for (Ice & ice : pvzice.icePos) {
                    ice.gridinfo = GetGridInfo(ice.position);
                    if (ice.gridinfo == CANPLANTICE) {
                        while (pvz.GamePaused() || !pvz.CursorInWindow() || pvz.SelectType() != 0) {
                            usleep(ice_precision);
                        }
                        pvz.PlantSeed(slot, ice.position);
                    }
                }
            }
        }
        // accuracy: 0.1s
        usleep(ice_precision);
    }
}

void PvZIce::Coffee() {
    for (std::vector<Ice>::reverse_iterator ice = icePos.rbegin(); ice != icePos.rend(); ++ice) {
        ice->gridinfo = GetGridInfo(ice->position);
        if (ice->gridinfo == HASICE) {
            pvz.PlantSeed(coffeeSlot, ice->position);
            return;
        }
    }
//    for (Ice & ice : icePos) {
//        ice.gridinfo = GetGridInfo(ice.position);
//        if (ice.gridinfo == HASICE) {
//            pvz.PlantSeed(coffeeSlot, ice.position);
//            return;
//        }
//    }
}

void AutoFillIce(std::initializer_list<Coord> ls) {
    pvzice.SetIcePos(ls);
    std::thread th(_AutoFillIce);
    th.detach();
}
