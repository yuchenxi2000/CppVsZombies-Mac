#ifndef auto_pvz_h
#define auto_pvz_h
#include "pvz-class.h"
/*
 * 为了适配pvzscript, cvz的接口
 * 给函数设置了多个名称
 *
 * 函数基本和lmintlcx的python框架一致
 * （当然一些功能未实现）
 *
 * 两个函数同时使用（指之间无Prejudge延时）时，鼠标指针不会指向原来的位置。
 * 因为macOS的鼠标点击事件会自动调用位置移动的callback。。我也很无奈
 */
/*
 * 该函数实现垫材等功能
 * 把种植、延迟铲除写在一个函数void DianCai();里
 * 然后使用时RunInThread(DianCai);
 *
 * 以及需要与发炮操作不干扰的操作（结尾冰杀小偷等）
 */
void RunInThread(void (*func)());
/*
 * 存冰
 * 示例：
 * StartAutoFillIceThread({{3, 5}, {1, 4}, {6, 4}}); // 开始存冰
 * StartAutoFillIceThread({{3, 5}}); // 开始存冰
 * Coffee(); // 唤醒一个冰蘑菇
 */
void AutoFillIce(std::initializer_list<Coord> ls);
#define StartAutoFillIceThread AutoFillIce
#define Coffee pvzice.Coffee
/*
 * 精确计时，与游戏内部时钟有关
 * Prejude = WaitUntil = 等待直至与设定波次刷新时间点的差值达到指定值
 * Until = 等待直至当前时间戳与本波刷新时间点的差值达到指定值
 * Delay = Wait = 游戏内部时钟延时
 *
 * 示例：
 * Prejudge(-90, 1); // 第一波前 90 cs
 * Until(100); // 当前波刷新后 100 cs
 * Delay(200); // 延迟 200 cs
 */
#define WaitUntil pvz.WaitUntil
#define Prejudge WaitUntil
#define Until pvz.Until
#define Wait pvz.Wait
#define Delay Wait
/*
 * 需要指定卡槽位置的用卡
 * 示例：
 * PlantSeed(1, {1,7});
 * 将卡槽1中的植物种到1行7列
 *
 * （你为什么不用 Card ？）
 */
#define PlantSeed pvz.PlantSeed
/*
 * 用卡
 * 示例：
 * Card("hbg", {1,7});
 * 卡片名称缩写请见 pvz-global.cpp
 */
#define Card slot.Card
/*
 * 暂时没有炮序、铲种炮功能
 * Pao, TryPao, Fire 都是程序自动找炮发射
 *
 * 如果出现炮落点在自身附近无法快速发炮请使用 DelayedFire
 *
 * 示例：
 * Pao({{2,9}});
 * Pao({{2,9}, {5,9}});
 *
 * Pao 函数调用必须有间隔（之间有 Sleep, Delay, Prejudge）。
 * 如果 Pao 连续无间隔两次调用会导致无法发射。
 * 如果要同时发射两门炮，请这样写：
 * Pao({{2,9}, {5,9}});
 *
 * 目前为止还没有发现“上界之风”现象，1.0.40版屋顶炮基本准确
 * 所以不会有 RoofPao。
 */
#define Fire cannon.Fire
#define Pao Fire
#define TryPao Pao
#define DelayedFire cannon.DelayedFire
#define DelayedPao DelayedFire
/*
 * 铲植物
 * Shovel({1, 7});
 */
#define Shovel pvz.Shovel
/*
 * 睡眠一段时间（厘秒）
 * 该函数不与游戏内部时钟挂钩，等待现实中一段时间
 */
#define Sleep pvz.Sleep
/*
 * 女仆秘籍
 */
#define StartStopDancerThread dancer.Start
#define CancelStopDancerThread dancer.Pause
/*
 * 暂停时有没有GUI（防挡视线）
 */
#define PauseNoGui dancer.nogui

#endif /* auto_pvz_h */
