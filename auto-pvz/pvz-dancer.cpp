#include "pvz-class.h"
PvZDancer::PvZDancer() {
    addr = pvz.ReadMemory<int>(pvz.base) + 0x800;
    running = false;
}

void _Dancer() {
    while (pvz.CurGameUI() != 3) {
        usleep(100000);
    }
    while (true) {
        while ((((pvz.ReadMemory<int>(dancer.addr) + 10) % (20 * 23)) / 20) > 11)
            pvz.Sleep(1);
        //模拟敲击空格
        pvz.PauseGame(true);
        pvz.Sleep(50);
        while (((pvz.ReadMemory<int>(dancer.addr) % (20 * 23)) / 20) <= 11)
            pvz.Sleep(1);
        pvz.PauseGame(false);
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
    pvz.PauseGame(false);
}

PvZDancer::~PvZDancer() {
    if (running) {
        pthread_cancel(handle);
        pvz.PauseGame(false);
    }
}
