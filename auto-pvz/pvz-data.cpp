#include "pvz-class.h"

void PvZSlot::LoadPlantName() {
    for (int i = 0; i < 88; ++i) {
        name_id_map.insert(std::make_pair(seed_name[0][i], i));
    }
}

void PvZSlot::GetPlantSlot() {
    slot_length = pvz.GetSlotCount();
    int i;
    for (i = 1; i <= slot_length; ++i) {
        slot_id[i] = pvz.GetSlotID(i);
        if (slot_id[i] == 48) {
            slot_id[i] = pvz.GetSlotImitatorID(i);
            slot_imitator[i] = true;
        }else {
            slot_imitator[i] = false;
        }
    }
    for (; i <= 10; ++i) {
        slot_id[i] = -1;
        slot_imitator[i] = false;
    }
}

int PvZSlot::GetPlantSlotByName(const std::string & name) {
    int id;
    bool imitator;
    auto p = name_id_map.find(name);
    if (p != name_id_map.end()) {
        if (p->second < 48) {
            imitator = false;
            id = p->second;
        }else {
            imitator = true;
            id = p->second - 48;
        }
        for (int i = 1; i <= slot_length; ++i) {
            if (id == slot_id[i] && imitator == slot_imitator[i]) {
                return i;
            }
        }
    }else {
        std::cout << "What's this??? --- " << name << std::endl;
    }
    return 0;
}

void PvZSlot::Card(const std::string & name, const Coord & pos) {
    int slot = GetPlantSlotByName(name);
    if (slot != 0) {
        pvz.PlantSeed(slot, pos);
    }
}
