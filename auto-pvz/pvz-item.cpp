#include "mouse.hpp"
#include "pvz-class.h"
int collect_interval = 6;
void _autoCollect() {
    while (pvz.CurGameUI() != 3) {
        pvz.Wait(collect_interval);
    }
    while (true) {
        int item_collected = 0;
        int item_max = pvz.ItemMaxCount();
        int item_on_lawn = pvz.ItemCount();
        
        while (item_on_lawn == 0) {
            pvz.Wait(collect_interval*2);
            item_on_lawn = pvz.ItemCount();
        }
        for (int index = 0; index < item_max && item_collected < item_on_lawn; ++index) {
            while (pvz.GamePaused() || !pvz.CursorInWindow() || pvz.SelectType() != 0)
                pvz.Wait(collect_interval);
            if (!pvz.ItemDisappeared(index) && !pvz.ItemCollected(index)) {
                float x = pvz.GetItemX(index);
                float y = pvz.GetItemY(index);
                if (x < 0 || y < 70) {
                    continue;
                }
                item_collected++;
                std::lock_guard<std::mutex> lkd(mouse_lock);
                SafeClick safeclick;
                Mouse::clickCoord(CGPointMake(x+windowPos.x+30, y+windowPos.y+30));
            }
            pvz.Wait(collect_interval);
        }
        
    }
}
void StartAutoCollectThread() {
    std::thread th(_autoCollect);
    th.detach();
}
