#include "scripts.hpp"
void pe_12() {
    for (int i = 1; i <= 20; ++i) {
        if (i == 20) {
            Prejudge(-200, i);
            DelayedFire({4,7}, 30);
        }
        Prejudge(-90, i);
        Pao({{2,9}, {5,9}});
        if (i == 10) {
            Until(373-90-100);
            Card("ytzd", {2,9});
        }
    }
    Until(300);
    Pao({{2,9}, {5,9}});
}

void pe_24() {
    AutoFillIce({{4,9}});
    for (int wave = 1; wave <= 20; ++wave) {
        switch (wave) {
            case 1:
            case 4:
            case 7:
            case 11:
            case 14:
            case 17:
                WaitUntil(-15, wave);
                Fire({{2,9},{5,9}});
                Wait(107);
                Fire({{1,7.7},{5,7.7}});
                break;
                
            case 2:
            case 5:
            case 8:
            case 12:
            case 15:
            case 18:
                WaitUntil(-95, wave);
                Fire({{2,9},{5,9}});
                Wait(373 - 100 - 198);
                Coffee();
                break;
                
            case 3:
            case 6:
            case 9:
            case 13:
            case 16:
            case 19:
                WaitUntil(-95, wave);
                Fire({{2,9},{5,9},{2,9},{5,9}});
                Wait(108);
                Fire({{1,8.8},{5,8.8}});
                if (wave == 9 || wave == 19) {
                    Wait(601 + 95 - 108 - 15);
                    Fire({{2,9},{5,9}});
                }
                break;
                
            case 10:
                WaitUntil(-55, wave);
                Fire({{2,9},{5,9},{2,9},{5,9}});
                Wait(108);
                Fire({{1,8.8},{5,8.8}});
                break;
                
            case 20:
                WaitUntil(-150, wave);
                Fire({{4,6},{4,8}});
                Wait(90);
                Fire({{1,9},{2,9},{5,9},{6,9}});
                Wait(108);
                Fire({{1,9},{2,9},{5,9},{6,9}});
                break;
                
            default:
                break;
        }
        
    }
}

void de_8() {
    AutoFillIce({{2, 1}, {4, 1}, {3, 7}});
    for (int wave = 1; wave <= 20; ++wave) {
        Prejudge(-200, wave);
        switch (wave) {
            case 1:
            case 4:
            case 7:
            case 10:
            case 13:
            case 16:
            case 19:
                if (wave == 10) {
                    Until(-55);
                }else {
                    Until(-95);
                }
                TryPao({{2,9}, {4,9}});
                Until(601+10-298);
                Coffee();
                if (wave == 19) {
                    Until(601 + 1437 - 200 - 373);
                    TryPao({{2,8.7},{4,8.7}});
                    Until(4500-200-373);
                    TryPao({{2,8.4},{4,8.4}});
                }
                break;
                
            case 2:
            case 5:
            case 8:
            case 11:
            case 14:
            case 17:
                if (wave == 2) {
                    Until(10+400);
                    Card("wg", {3,9});
                }else if (wave == 11) {
                    Until(10+400-100);
                    Card("ytzd", {3,8});
                }
                if (wave == 2) {
                    Until(750);
                    Card("xpg", {3,8});
                    Delay(100);
                    Shovel({3,8});
                }
                Until(1437-200-373);
                TryPao({{2,8.7}, {4,8.7}});
                Until(1437+20-298);
                Coffee();
                break;
                
            case 3:
            case 6:
            case 9:
            case 12:
            case 15:
            case 18:
                Until(-150);
                TryPao({{2,8.5}, {4,8.5}});
                Until(1437 - 200 - 373);
                TryPao({{2,8.7}, {4,8.7}});
                if (wave == 9) {
                    Until(1437-95);
                    TryPao({{2,8.7}, {4,8.7}});
                    Until(4500 - 200 - 373);
                    TryPao({{2,8.4}, {4,8.4}});
                }
                break;
                
            case 20:
                Until(-60);
                TryPao({{2,9}, {4,9}, {2,9}, {4,9}});
                Until(601-298);
                Coffee();
                Until(601+10);
                break;
                
            default:
                break;
        }
    }
    //                                    Card("复制冰", (4, 1))  # 最后一个存冰
}

void pe_4() {
    StartAutoFillIceThread({{3, 5}, {1, 4}, {6, 4}});
    for (int wave = 1; wave <= 20; ++wave) {
        std::cout << "wave: " << wave << std::endl;
        Prejudge(-200, wave);
        switch (wave) {
            case 1:
            case 5:
            case 9:
            case 10:
            case 14:
            case 18:
                Until(601 - 200 - 373);
                Pao({{2, 9}, {5, 9}});
                Until(601 + 20 - 298); // 20cs 预判冰
                Coffee();
                break;
                
            case 2:
            case 6:
            case 11:
            case 15:
            case 19:
                Until(1800 - 200 - 373);
                Pao({{2, 8.3}, {5, 8.3}});
                Until(1800 + 20 - 298); // 20cs 预判冰
                Coffee();
                break;
            
            case 3:
            case 7:
            case 12:
            case 16:
                Until(1800 - 200 - 373);
                Pao({{2, 8.3}, {5, 8.3}});
                Until(1800 + 50 - 298); // 50cs 预判冰
                Coffee();
                break;
                
            case 4:
            case 8:
            case 13:
            case 17:
                float row, col;
                if (wave == 4) {
                    row = 3;
                    col = 8;
                }else if (wave == 8) {
                    row = 3;
                    col = 9;
                }else if (wave == 13) {
                    row = 4;
                    col = 8;
                }else { // wave == 17
                    row = 4;
                    col = 9;
                }
                Until(1150 - 200 - 298);
                Card("hy", {row, col});
                Card("hmg", {row, col});
                Card("kfd", {row, col});
                break;
                    
            case 20:
                Until(-55);
                Pao({{2, 9}, {5, 9}});
                Until(300);
                Coffee();
                break;
                
            default:
                break;
        }
    }
    
}

void me_10() {
    for (int i = 1; i <= 20; ++i) {
        if (i == 20) { // 冰消空降
            Prejudge(-100, i);
            Card("hp", {3, 8});
            Card("hbg", {3, 8});
            Delay(100 + 1);
            Shovel({3, 8});
        }
        Prejudge(125, i);
        Pao({{2,9}, {4,9}});
    }
}
void pe_16(bool bungee) {
    for (int i = 1; i <= 20; ++i) {
        if (i == 20) {
            Prejudge(-150-30, i);
            DelayedFire({4,7}, 30);
            Wait(90);
            Fire({{2,9},{2,9},{5,9},{5,9}});
            // 冰杀小偷
            if (!bungee) return;
            Until(200);
            Card("hbg", {1,7});
            Card("kfd", {1,7});
            return;
        }
        Prejudge(-90, i);
        if (i % 3 == 1) {
            Pao({{2,9},{5,9},{2,9},{5,9}});
        }else {
            Pao({{2,9},{5,9}});
        }
        if (i == 10 && bungee) {
            // 冰杀小偷
            Until(200);
            Card("hbg", {1,7});
            Card("kfd", {1,7});
        }
    }
}

void DianCai() {
    Card("xpg", {1, 9});
    Card("ygg", {2, 9});
    Delay(100);
    Shovel({1, 9});
    Shovel({2, 9});
}

void Flame() {
    while (pvz.CurrentWave() < 10) {
        Sleep(1);
    }
    Delay(400);
    Card("hy", {4, 9});
    Card("hblj", {4, 9});
    Delay(100 + 1);
    Shovel({4, 9});
    while (pvz.CurrentWave() < 20) {
        Sleep(1);
    }
    Delay(400);
    Card("hy", {4, 9});
    Card("hblj", {4, 9});
    Delay(100 + 1);
    Shovel({4, 9});
}

void pe_half_12() {
//            SelectCards(["白冰", "冰菇", "咖啡", "荷叶", "南瓜", "樱桃", "辣椒", "倭瓜", "阳光", "小喷"])
    UpdatePaoList({
        {1, 3}, {2, 3}, {3, 3},
        {1, 5}, {2, 5}, {3, 5},
        {1, 7}, {2, 7}, {3, 7},
        {1, 1}, {2, 1}, {3, 1},
    });
    Card("hbg", {5, 5});  // 临时存冰
    Card("hy", {3, 9});  // 临时存冰位
    Card("ngt", {3, 9});  // 其实不需要
    StartAutoFillIceThread({{4, 5}, {4, 6}, {4, 7}, {4, 8}, {3, 9}});
    RunningInThread(Flame);
    for (int wave = 1; wave <= 20; ++wave) {
        printf("wave: %d\n", wave);
        Prejudge(-200, wave);
        if (wave == 1 || wave == 10) {
            Until(-95);
            Pao({{1, 9}});
            Until(-15);
            Pao({{2, 9}, {5, 9}});
            Until(-15 + 110);
            Pao({{5, 7.7}});
            Until(-15 + 110 + 373 - 100); // 368
            Card("ytzd", {1, 9});
        }else if (wave == 20) {
            Until(-150 - 30);
            DelayedPao({4, 7}, 30);
            Until(-60); // 等到刷新前 60cs
            Pao({{2, 9}, {5, 9}, {2, 9}, {5, 9}});
            Until(-60 + 110);
            Pao({{1, 8.8}, {2, 8.8}}); // 炮不够 ==
            Until(-60 + 110 + 373 - 100);
            Card("ytzd", {5, 9});
            // 收尾
        }else {
            Until(-133);
            Pao({{1, 8.0}}); // 拦截上波红眼, 分离部分快速僵尸
            Until(360 - 373);
            Pao({{2, 8.15}}); // "无冰分离."  ----发出日智的声音
            Until(360 - 298); // 360cs 反应冰
            if (wave != 2) {
                Coffee();
            }else {
                Card("kfd", {{5, 5}});
            }
            Until(360 + 500 - 373);
            if (wave != 2 && wave != 11) {
                Pao({{5,3}}); // 下半场尾炸
            }
            Until(1800 - 200 - 373);
            Pao({{2, 9}, {5, 8.1}}); // 激活炸
            Delay(10);
            RunningInThread(DianCai); // 垫撑杆
            Until(1800 - 200 - 373 + 220);
            Pao({{1, 8.2}}); // 秒白眼, 触发红眼投掷
            if (wave == 9 || wave == 19){ // 收尾波次
                Until(1800 - 133);
                Pao({{1, 8.0}});
                Until(1800 + 360 - 373);
                Pao({{2, 9}});
                Until(1800 + 360 + 500 - 373);
                Pao({{5, 2.5}});
                Until(1800 + 1800 - 200 - 373);
                Pao({{5, 6}});
                Delay(110);
                Pao({{5, 6}});
                Delay(110);
                Pao({{5, 3}});
                Until(4500 - 200 - 373);
                Pao({{5, 5}});
                if (wave == 9) {
                    SkipPao(2); // 中场调整
                }
            }
        }
    }
    WaitUntilEnd();
}
