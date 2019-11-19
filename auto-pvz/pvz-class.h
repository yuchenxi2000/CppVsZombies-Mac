#ifndef pvz_class_h
#define pvz_class_h
#include <iostream>
#include "mouse.hpp"
#include "keyboard.hpp"
#include "operation.hpp"
#include "memory.h"
#include <thread>
#include <map>
#include <string>
/*
 * 所有类的定义
 */
class PvZOperation;

extern Coord windowPos;
extern Coord desktopSize;
extern int scene;
extern std::mutex mouse_lock;

typedef uint8_t byte;

struct Cannon {
    int index;
    Coord position;
};

enum CannonState {
    cob_preparing = 35,
    cob_ready = 37,
    cob_firing = 38
};

/*
 * 所有和游戏有关的接口
 * （寻找游戏窗口，读取内存）
 */
class PvZ {
public:
    template<typename T, typename... Args>
    T ReadMemory(Args... address);
    
    template<typename T, size_t size, typename... Args>
    std::array<T, size> ReadMemory(Args... address);
    
    template<typename T, typename... Args>
    void WriteMemory(T value, Args... address);
    
    template<typename T, size_t size, typename... Args>
    void WriteMemory(std::array<T, size> value, Args... address);
    
    void WriteMemory(std::initializer_list<byte> il, uintptr_t address);
    
    // game info
    void FindProcessByWindowName();
    
    pid_t pid;
    const uint32_t base = 0x35EE64;
    uint32_t plantOffset;
    uint32_t slotOffset;
    Memory memory;
public:
    // game, internal timer
    bool GamePaused();
    void PauseGame(bool);
    int CurGameUI();
    int CurGameTime();
    int CurrentWave();
    int PlantsCount();
    int PlantsMaxCount();
    int ZombiesCount();
    int RefreshCountdown();
    int HugeWaveCountdown();
    int CurScene();
    int WaveInterval();
    
    // plant
    void PrintAllPlants();
    bool PlantAlive(int index);
    int GetPlantID(int index);
    int GetPlantRow(int index);
    int GetPlantCol(int index);
    CannonState GetCannonState(int index);
    
    // slot
    void PrintAllSlots();
    int GetSlotID(int num);
    int GetSlotImitatorID(int num);
    int GetSlotCount();
    int GetSlotCD(int num); // 0x4C
    int GetSlotTotalCD(int num); // 0x50
    
    // zombie refresh
    int refresh_point;
    void UntilCountDown(int cs, bool isHugeWave);
public:
    PvZ();
    ~PvZ();
    // 窗口前置
    void WindowFront();
    // 简单地睡眠cs厘秒
    void Sleep(int cs);
    // 等到相对特定波cs厘秒到位置
    // 简单地，WaitUntil(-15)预判，WaitUntil(30)反应
    void WaitUntil(int cs, int wave);
    // 等游戏刻前进cs厘秒
    void Wait(int cs);
    // 等到距本波刷新点cs位置
    void Until(int cs);
    // 手动种植物
    void PlantSeed(int slot, const Coord & pos);
    // 铲植物
    void Shovel(const Coord & plant);
};

class PvZCannon {
    void GetCannonOnLawn();
    void GetCannonFromList(std::initializer_list<Coord> ls);
    std::vector<Cannon> cannonlist;
    int curindex;
public:
    PvZCannon();
    ~PvZCannon();
    // 更新炮列表
    void UpdatePaoList();
    void UpdatePaoList(std::initializer_list<Coord> ls);
    // 跳过炮列表中一门炮
    void SkipPao(int num);
    // 手动发炮
    void Fire(const Coord & cob, const Coord & firepos);
    // 程序自动找炮发射
    void Fire(std::initializer_list<Coord> firepos);
    // 程序自动找炮发射，延迟cs点炮
    void DelayedFire(const Coord & firepos, int cs);
};

void AutoFillIce(std::initializer_list<Coord> ls);
enum GridIceInfo {
    CANPLANTICE,
    HASPLANT,
    HASICE
};
struct Ice {
    Coord position;
    GridIceInfo gridinfo;
};
class PvZIce {
    std::vector<int> iceSlot;
    int coffeeSlot;
    std::vector<Ice> icePos;
    void GetIceSlot();
public:
    PvZIce();
    ~PvZIce();
    
    friend void _AutoFillIce();
    
    void SetIcePos(std::initializer_list<Coord> ls);
    void Coffee();
};

class PvZSlot {
    std::map<std::string, int> name_id_map;
    int slot_length;
    int slot_id[11];
    bool slot_imitator[11];
    
    void LoadPlantName();
    void GetPlantSlot();
    int GetPlantSlotByName(const std::string & name);
public:
    PvZSlot() {
        LoadPlantName();
        GetPlantSlot();
    }
    void Card(const std::string & name, const Coord & pos);
};

class PvZDancer {
    std::thread th;
    pthread_t handle;
    bool running;
public:
    uint32_t addr;
    PvZDancer();
    ~PvZDancer();
    void Start();
    void Pause();
};

extern std::string seed_name[11][8];
extern KeyBoard keyboard;
extern PvZOperation operation;
extern PvZ pvz;
extern PvZSlot slot;
extern PvZCannon cannon;
extern PvZIce pvzice;
extern PvZDancer dancer;

#endif /* pvz_class_h */
