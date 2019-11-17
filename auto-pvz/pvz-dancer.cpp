#include "pvz-class.h"
PvZDancer::PvZDancer() {
    addr = pvz.ReadMemory<int>(pvz.base) + 0x800;
    running = false;
    nogui = false;
}

void _Dancer() {
    while (pvz.CurGameUI() != 3) {
        usleep(100000);
    }
    while (true) {
        while ((((pvz.ReadMemory<int>(dancer.addr) + 10) % (20 * 23)) / 20) > 11)
            pvz.Sleep(1);
        
        if (dancer.nogui) {
            // 写内存
            pvz.PauseGame(true);
        }else {
            //模拟敲击空格
            keyboard.PressSpace();
        }
        
        pvz.Sleep(50);
        while (((pvz.ReadMemory<int>(dancer.addr) % (20 * 23)) / 20) <= 11)
            pvz.Sleep(1);
        
        if (dancer.nogui) {
            // 写内存
            pvz.PauseGame(false);
        }else {
            //模拟敲击空格
            keyboard.PressSpace();
        }
        
        pvz.Sleep(10);
    }
}

void PvZDancer::Start() {
    th = std::thread(_Dancer);
    handle = th.native_handle();
    th.detach();
    running = true;
}

void PvZDancer::Pause() {
    pthread_cancel(handle);
    running = false;
    if (dancer.nogui) {
        // 写内存
        pvz.PauseGame(false);
    }else {
        //模拟敲击空格
        keyboard.PressSpace();
    }
}

PvZDancer::~PvZDancer() {
    if (running) {
        pthread_cancel(handle);
        if (dancer.nogui) {
            // 写内存
            pvz.PauseGame(false);
        }else {
            //模拟敲击空格
            keyboard.PressSpace();
        }
    }
}
