#include "pvz-class.h"
/*
 * 全局变量
 * 请勿改变初始化顺序
 */
std::string seed_name[11][8] =
{
    //豌豆射手，向日葵，樱桃炸弹，坚果，土豆地雷，寒冰射手，大嘴花，双重射手
    {"wdss", "xrk", "ytzd", "jg", "tddl", "hbss", "dzh", "scss"},
    //小喷菇，阳光菇，大喷菇，墓碑吞噬者，魅惑菇，胆小菇，寒冰菇， 毁灭菇
    {"xpg", "ygg", "dpg", "mbtsz", "mhg", "dxg", "hbg", "hmg"},
    //荷叶，倭瓜，三发射手，缠绕海藻，火爆辣椒，地刺，火炬树桩，高坚果
    {"hy", "wg", "sfss", "crhz", "hblj", "dc", "hjsz", "gjg"},
    //水兵菇，路灯花，仙人掌，三叶草， 裂荚射手，杨桃，南瓜头，磁力菇
    {"sbg", "ldh", "xrz", "syc", "ljss", "yt", "ngt", "clg"},
    //卷心菜投手，花盆，玉米投手，咖啡豆，大蒜，叶子保护伞，金盏花，西瓜投手
    {"jxcts", "hp", "ymts", "kfd", "ds", "yzbhs", "jzh", "xgts"},
    //机枪射手，双子向日葵，忧郁菇，香蒲，冰西瓜投手，吸金磁，地刺王，玉米加农炮
    {"jqss", "szxrk", "yyg", "xp", "bxgts", "xjc", "dcw", "ymjnp"},
    
    //以下为模仿者卡片名称
    //豌豆射手，向日葵，樱桃炸弹，坚果，土豆地雷，寒冰射手，大嘴花，双重射手
    {"Mwdss", "Mxrk", "Mytzd", "Mjg", "Mtddl", "vhbss", "Mdzh", "Mscss"},
    //小喷菇，阳光菇，大喷菇，墓碑吞噬者，魅惑菇，胆小菇，寒冰菇，毁灭菇
    {"Mxpg", "Mygg", "Mdpg", "Mmbtsz", "Mmhg", "Mdxg", "Mhbg", "Mhmg"},
    //荷叶，倭瓜，三发射手，缠绕海藻，火爆辣椒，地刺，火炬树桩，高坚果
    {"Mhy", "Mwg", "Msfss", "Mcrhz", "Mhblj", "Mdc", "Mhjsz", "Mgjg"},
    //水兵菇，路灯花，仙人掌，三叶草，裂荚射手，杨桃，南瓜头，磁力菇
    {"Msbg", "Mldh", "Mxrz", "Msyc", "Mljss", "Myt", "Mngt", "Mclg"},
    //卷心菜投手，花盆，玉米投手，咖啡豆，大蒜，叶子保护伞，金盏花，西瓜投手
    {"Mjxcts", "Mhp", "Mymts", "Mkfd", "Mds", "Myzbhs", "Mjzh", "Mxgts"}};

Coord windowPos;
Coord desktopSize;
int scene;
std::mutex mouse_lock;
PvZOperation operation;

PvZ pvz;
PvZSlot slot;
PvZCannon cannon;
PvZIce pvzice;
