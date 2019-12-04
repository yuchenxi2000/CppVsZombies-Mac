#include "pvz-class.h"
#include <CoreGraphics/CoreGraphics.h>
/*
 find process by window name
 */
void PvZ::FindProcessByWindowName() {
    CFArrayRef windows = CGWindowListCopyWindowInfo(kCGWindowListOptionAll, kCGNullWindowID);
    
    // game window name
    // game window owner name
    CFStringRef pvz = CFStringCreateWithCString(kCFAllocatorDefault, "Plants vs. Zombies 1.0.40", kCFStringEncodingASCII);
    CFStringRef pvzowner = CFStringCreateWithCString(kCFAllocatorDefault, "Plants vs. Zombies", kCFStringEncodingASCII);
    
    CFStringRef desktop_name = CFStringCreateWithCString(kCFAllocatorDefault, "Desktop", kCFStringEncodingASCII);
    
    bool pvz_found = false, desktop_found = false;
    
    CFIndex cnt = CFArrayGetCount(windows);
    for (CFIndex i = 0; i < cnt; ++i) {
        CFDictionaryRef dic = (CFDictionaryRef)CFArrayGetValueAtIndex(windows, i);
        // window name
        // window owner name
        const CFStringRef name = (const CFStringRef)CFDictionaryGetValue(dic, kCGWindowName);
        const CFStringRef ownername = (const CFStringRef)CFDictionaryGetValue(dic, kCGWindowOwnerName);
        
        if ((name != 0 && CFStringCompare(name, pvz, kCFCompareNonliteral) == kCFCompareEqualTo) || (ownername != 0 && CFStringCompare(ownername, pvzowner, kCFCompareNonliteral) == kCFCompareEqualTo)) {
            // check if is real window
            CFBooleanRef onscreen = (CFBooleanRef)CFDictionaryGetValue(dic, kCGWindowIsOnscreen);
            if (onscreen == 0 || !CFBooleanGetValue(onscreen)) {
                continue;
            }
            
            // pid
            const CFNumberRef num = (const CFNumberRef)CFDictionaryGetValue(dic, kCGWindowOwnerPID);
            if (num == 0) {
                std::cerr << "cannot get game pid!" << std::endl;
                exit(EXIT_FAILURE);
            }
            CFNumberGetValue(num, kCFNumberIntType, &pid);
            std::cout << "pid: " << pid << std::endl;
            
            // window position
            const CFDictionaryRef rectdic = (const CFDictionaryRef)CFDictionaryGetValue(dic, kCGWindowBounds);
            if (rectdic == 0) {
                std::cerr << "cannot get game window position!" << std::endl;
                exit(EXIT_FAILURE);
            }
            CGRect rect;
            CGRectMakeWithDictionaryRepresentation(rectdic, &rect);
            
            // full screen
            if (rect.size.height == 600.0f) {
                windowPos.row = rect.origin.y;
                windowPos.col = rect.origin.x;
            }else {
                windowPos.row = rect.origin.y + rect.size.height - 600;
                windowPos.col = rect.origin.x;
            }
            
            std::cout << "window position: x " << windowPos.x << " y " << windowPos.y << std::endl;
            
            pvz_found = true;
        }else if (name != 0 && CFStringCompare(name, desktop_name, kCFCompareNonliteral) == kCFCompareEqualTo) {
            // desktop size
            const CFDictionaryRef rectdic = (const CFDictionaryRef)CFDictionaryGetValue(dic, kCGWindowBounds);
            if (rectdic == 0) {
                std::cerr << "cannot get desktop size!" << std::endl;
                exit(EXIT_FAILURE);
            }
            CGRect rect;
            CGRectMakeWithDictionaryRepresentation(rectdic, &rect);
            
            desktopSize.x = rect.size.width;
            desktopSize.y = rect.size.height;
            std::cout << "desktop size: x " << desktopSize.x << " y " << desktopSize.y << std::endl;
            
            desktop_found = true;
        }
    }
    
    CFRelease(pvz);
    CFRelease(pvzowner);
    CFRelease(windows);
    CFRelease(desktop_name);
    
    if (!pvz_found) {
        std::cerr << "cannot find game!" << std::endl;
    }
    if (!desktop_found) {
        std::cerr << "cannot get desktop size!" << std::endl;
    }
    if (!(pvz_found && desktop_found)) {
        std::cerr << "exit" << std::endl;
        exit(EXIT_FAILURE);
    }
}
PvZ::PvZ() {
    FindProcessByWindowName();
    memory.Attach(pid);
    scene = CurScene();
    while (CurGameUI() != 3) {
        usleep(100000); // 0.1 s
    }
    plantOffset = ReadMemory<uint32_t>(base, 0x780, 0xA0);
    slotOffset = ReadMemory<uint32_t>(base, 0x780, 0x138);
    itemOffset = ReadMemory<uint32_t>(base, 0x780, 0xD8);
    mouseOffset = ReadMemory<uint32_t>(base, 0x780, 0x12C);
    std::cout << "game start!" << std::endl;
    
    // 窗口前置
    WindowFront();
    // 取消暂停
    if (pvz.GamePaused()) {
        usleep(1000000);
        if (pvz.GamePaused()) {
            keyboard.PressSpace();
        }
    }
}
PvZ::~PvZ() {
    memory.Detach();
    std::cout << "done. exit" << std::endl;
}

void PvZ::WriteMemory(std::initializer_list<byte> il, uintptr_t address) {
    memory.Write(address, il.size(), (void *) il.begin());
}

bool PvZ::GamePaused() {
    return pvz.ReadMemory<bool>(base, 0x780, 0x158);
}

void PvZ::PauseGame(bool pause) {
    uint32_t addr = ReadMemory<int>(base, 0x780) + 0x158;
    memory.Write<uint8_t>(pause, addr);
}

int PvZ::CurGameUI() {
    return ReadMemory<int>(base, 0x7C4);
}

int PvZ::CurGameMode() {
    int gameui = CurGameUI();
    if (gameui == 2 || gameui == 3)
        return ReadMemory<int>(base, 0x7C0);
    else return 0;
}

int PvZ::CurGameTime() {
    return ReadMemory<int>(base, 0x780, 0x5560);
}

int PvZ::CurrentWave() {
    return ReadMemory<int>(base, 0x780, 0x5570);
}

int PvZ::PlantsCount() {
    return ReadMemory<int>(base, 0x780, 0xB0);
}

int PvZ::PlantsMaxCount() {
    return ReadMemory<int>(base, 0x780, 0xA4);
}

int PvZ::ZombiesCount() {
    return ReadMemory<int>(base, 0x780, 0x94);
}

int PvZ::RefreshCountdown() {
    return ReadMemory<int>(base, 0x780, 0x5590);
}

int PvZ::HugeWaveCountdown() {
    return ReadMemory<int>(base, 0x780, 0x5598);
}

int PvZ::CurScene() {
    return ReadMemory<int>(base, 0x780, 0x5540);
}
int PvZ::WaveInterval() {
    return ReadMemory<int>(base, 0x780, 0x5594);
}

int main_precision = 10000;

void PvZ::Sleep(int cs) {
    usleep(cs * 10000);
}
void PvZ::Wait(int cs) {
    int start = CurGameTime();
    while (true) {
        if (CurGameTime() - start >= cs) {
            return;
        }
        usleep(main_precision);
    }
}

void PvZ::UntilCountDown(int cs, bool isHugeWave) {
    if (!isHugeWave) {
        while (RefreshCountdown() > cs)
            usleep(main_precision);
    }else {
        while (RefreshCountdown() > 5) {
            usleep(main_precision);
        }
        while (HugeWaveCountdown() > cs) {
            usleep(main_precision);
        }
    }
}

int refresh_time[] = {
    599, 200, 200, 200, 200,
    200, 200, 200, 200, 750,
    200, 200, 200, 200, 200,
    200, 200, 200, 200, 750
};

void PvZ::WaitUntil(int cs, int wave) {
    int curwave = CurrentWave();
    int count_down;
    if (curwave < wave) {
        while (CurrentWave() < wave - 1) {
            usleep(main_precision);
        }
        bool isHugeWave = (wave == 10 || wave == 20);
        UntilCountDown(refresh_time[wave - 1], isHugeWave);
        
        int refreshRemain = RefreshCountdown();
        int hugewaveRemain = HugeWaveCountdown();
        if (isHugeWave) {
            if (refreshRemain == 4 || refreshRemain == 5) {
                count_down = hugewaveRemain;
            }else {
                count_down = hugewaveRemain-5+750;
            }
        }else {
            count_down = refreshRemain;
        }
        int clock = CurGameTime();
        refresh_point = clock + count_down;
        
        int waittime = cs + count_down;
        if (waittime >= 0) {
            Wait(waittime);
        }
    }else if (curwave == wave) {
        int curtime = CurGameTime();
        int refreshRemain = RefreshCountdown();
        int initcountdown = WaveInterval();
        refresh_point = curtime - (initcountdown - refreshRemain);
        int waittime = cs - (initcountdown - refreshRemain);
        if (waittime >= 0) {
            Wait(waittime);
        }
    }
}

void PvZ::Until(int cs) {
    int waittime = cs - (CurGameTime() - refresh_point);
    if (waittime >= 0) {
        Wait(waittime);
    }
}

void PvZ::WaitUntilEnd() {
    while (CurGameUI() == 3) {
        usleep(100000); // 0.1 s
    }
}

void PvZ::PlantSeed(int slot, const Coord & pos) {
    std::lock_guard<std::mutex> lkg(mouse_lock);
    operation.safePlantSeed(slot, pos);
}

void PvZ::Shovel(const Coord & plant) {
    std::lock_guard<std::mutex> lkg(mouse_lock);
    operation.safeShovelPlant(plant);
}

//debug
void PvZ::PrintAllPlants() {
    uint32_t offset = ReadMemory<uint32_t>(base, 0x780, 0xA0);
    uint32_t cnt = ReadMemory<uint32_t>(base, 0x780, 0xA4);
    for (int i = 0; i < cnt; ++i) {
        std::cout << "plant " << i << std::endl;
        for (int j = 0; j < 83; ++j) {
            int res = ReadMemory<int>(offset + 0x14C * i + j * 4);
            std::cout << res << std::endl;
        }
        std::cout << std::endl;
    }
}

bool PvZ::PlantAlive(int index) {
    bool disappear = ReadMemory<bool>(plantOffset + 0x141 + 0x14C * index);
    bool crushed = ReadMemory<bool>(plantOffset + 0x142 + 0x14C * index);
    return !(disappear || crushed);
}

CannonState PvZ::GetCannonState(int index) {
    return (CannonState)ReadMemory<int>(plantOffset + 0x3C + 0x14C * index);
}

int PvZ::GetPlantID(int index) {
    return ReadMemory<int>(plantOffset + 0x24 + 0x14C * index);
}

int PvZ::GetPlantRow(int index) {
    return ReadMemory<int>(plantOffset + 0x1C + 0x14C * index) + 1;
}

int PvZ::GetPlantCol(int index) {
    return ReadMemory<int>(plantOffset + 0x28 + 0x14C * index) + 1;
}

int PvZ::GetSlotID(int num) {
    return ReadMemory<int>(slotOffset + 0x5C + (num - 1) * 0x50);
}

int PvZ::GetSlotImitatorID(int num) {
    return ReadMemory<int>(slotOffset + 0x60 + (num - 1) * 0x50);
}


void PvZ::PrintAllSlots() {
    int slotCnt = GetSlotCount();
    for (int i = 1; i <= slotCnt; ++i) {
        std::cout << GetSlotID(i) << std::endl;
    }
}

int PvZ::GetSlotCount() {
    return ReadMemory<int>(slotOffset + 0x24);
}

int PvZ::GetSlotCD(int num) {
    return ReadMemory<int>(slotOffset + 0x4C + (num - 1) * 0x50);
}

int PvZ::GetSlotTotalCD(int num) {
    return ReadMemory<int>(slotOffset + 0x50 + (num - 1) * 0x50);
}

int PvZ::ItemCount() {
    return pvz.ReadMemory<uint32_t>(pvz.base, 0x780, 0xE8);
}

int PvZ::ItemMaxCount() {
    return pvz.ReadMemory<uint32_t>(pvz.base, 0x780, 0xDC);
}

bool PvZ::ItemDisappeared(int index) {
    return pvz.ReadMemory<bool>(itemOffset + 0x38 + 0xB4 * index);
}

bool PvZ::ItemCollected(int index) {
    return pvz.ReadMemory<bool>(itemOffset + 0x50 + 0xB4 * index);
}

float PvZ::GetItemX(int index) {
    return pvz.ReadMemory<float>(itemOffset + 0x24 + 0xB4 * index);
}

float PvZ::GetItemY(int index) {
    return pvz.ReadMemory<float>(itemOffset + 0x28 + 0xB4 * index);
}

int PvZ::CursorX() {
    return ReadMemory<int>(mouseOffset + 0x8);
}

int PvZ::CursorY() {
    return ReadMemory<int>(mouseOffset + 0xC);
}

int PvZ::CursorInWindow() {
    return ReadMemory<int>(mouseOffset + 0x18);
}

int PvZ::SelectedSlot() {
    return ReadMemory<int>(mouseOffset + 0x24);
}

int PvZ::SelectedCardID() {
    return ReadMemory<int>(mouseOffset + 0x28);
}

int PvZ::SelectType() { // 0: none, 1:card, 6: shovel, 8: cannon
    return ReadMemory<int>(mouseOffset + 0x30);
}

// cheat
void PvZ::NoFog(bool on) {
    if (on)
        WriteMemory({0x90, 0x90}, 0x1086B);
    else
        WriteMemory({0x74, 0x09}, 0x1086B);
}

void PvZ::ModifyEndlessLevel(int level) {
    int gameui = CurGameUI();
    if (gameui == 60 || gameui == 70 || (gameui >= 11 && gameui <= 15))
        WriteMemory<int>(level, base, 0x780, 0x154, 0x6C);
}

void PvZ::ModifySun(int sun) {
    WriteMemory<int>(sun, base, 0x780, 0x5554);
}

void PvZ::ModifyMoney(int money) {
    WriteMemory<int>(money, base, 0x7F4, 0x38);
}

void PvZ::LockSun(bool on) {
    if (on) {
        WriteMemory({0x90, 0x90, 0x90, 0x90, 0x90, 0x90}, 0x1C72F);
        WriteMemory({0x90, 0x90, 0x90, 0x90, 0x90, 0x90}, 0x18E8F);
    } else {
        WriteMemory({0x89, 0x90, 0x54, 0x55, 0x00, 0x00}, 0x1C72F);
        WriteMemory({0x89, 0x90, 0x54, 0x55, 0x00, 0x00}, 0x18E8F);
    }
}

void PvZ::LockMoney(bool on) {
    if (on)
        WriteMemory({0x90, 0x90, 0x90}, 0x43148);
    else
        WriteMemory({0x89, 0x50, 0x38}, 0x43148);
}

void RunningInThread(void (*func)()) {
    std::thread th(func);
    th.detach();
}
