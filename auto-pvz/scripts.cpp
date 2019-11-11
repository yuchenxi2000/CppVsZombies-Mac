#include "scripts.hpp"
//void pe_12() {
//    for (int i = 1; i <= 20; ++i) {
//        if (i == 20) {
//            bot.WaitUntil(-200, i);
//            bot.DelayedFire({4,7}, 30);
//        }
//        bot.WaitUntil(-100, i);
//        bot.Fire({{2,9}, {5,9}});
//        if (i == 10) {
//            bot.Wait(373);
//            bot.PlantSeed(2, {2,9});
//        }
//    }
//    bot.WaitUntil(200, 20);
//    bot.Fire({{2,9}, {5,9}});
//}
//
//void pe_8() {
//    for (int wave = 1; wave <= 20; ++wave) {
//        bot.WaitUntil(300, wave);
//        bot.Fire({{2, 8.3}, {5, 8.3}});
//    }
//}
//
//void pe_10() {
//    for (int wave = 1; wave <= 20; ++wave) {
//        bot.WaitUntil(100, wave);
//        bot.Fire({{2, 8.7}, {5, 8.7}});
//    }
//}

void pe_12() {
    for (int i = 1; i <= 20; ++i) {
        if (i == 20) {
            WaitUntil(-200, i);
            DelayedFire({4,7}, 30);
        }
        WaitUntil(-100, i);
        Fire({{2,9}, {5,9}});
        if (i == 10) {
            Wait(373);
            Card("ytzd", {2,9});
        }
    }
    WaitUntil(300, 20);
    Fire({{2,9}, {5,9}});
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
//                if (wave == 9 || wave == 19) {
//                    Wait(601 + 95 - 108 - 15);
//                    Fire({{2,9},{5,9}});
//                }
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
        WaitUntil(-200, wave);
        switch (wave) {
            case 1:
            case 4:
            case 7:
            case 10:
            case 13:
            case 16:
            case 19:
                if (wave == 10) {
                    WaitUntil(-55, wave);
                }else {
                    WaitUntil(-95, wave);
                }
                Fire({{2,9}, {4,9}});
                WaitUntil(601+10-298, wave);
                Coffee();
                if (wave == 19) {
                    WaitUntil(601 + 1437 - 200 - 373, wave);
                    Fire({{2,8.7},{4,8.7}});
                    WaitUntil(4500-200-373, wave);
                    Fire({{2,8.4},{4,8.4}});
                }
                break;

            case 2:
            case 5:
            case 8:
            case 11:
            case 14:
            case 17:
                if (wave == 2) {
                    WaitUntil(10+400, wave);
                    Card("wg", {3,9});
                }else if (wave == 11) {
                    WaitUntil(10+400-100, wave);
                    Card("ytzd", {3,8});
                }
                if (wave == 2) {
                    WaitUntil(750, wave);
                    Card("xpg", {3,8});
                    Wait(100);
                    Shovel({3,8});
                }
                WaitUntil(1437-200-373, wave);
                Fire({{2,8.7}, {4,8.7}});
                WaitUntil(1437+20-298, wave);
                Coffee();
                break;

            case 3:
            case 6:
            case 9:
            case 12:
            case 15:
            case 18:
                WaitUntil(-150, wave);
                Fire({{2,8.5}, {4,8.5}});
                WaitUntil(1437 - 200 - 373, wave);
                Fire({{2,8.7}, {4,8.7}});
                if (wave == 9) {
                    WaitUntil(1437-95, wave);
                    Fire({{2,8.7}, {4,8.7}});
                    WaitUntil(4500 - 200 - 373, wave);
                    Fire({{2,8.4}, {4,8.4}});
                }
                break;

            case 20:
                WaitUntil(-60, wave);
                Fire({{2,9}, {4,9}, {2,9}, {4,9}});
                WaitUntil(601-298, wave);
                Coffee();
                WaitUntil(601+10, wave);
                break;

            default:
                break;
        }
    }
    //                                    Card("复制冰", (4, 1))  # 最后一个存冰
}

void de_8_n() {
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
//                    Until(4500 - 200 - 373);
//                    TryPao({{2,8.4}, {4,8.4}});
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
                }else if (wave == 17) {
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
