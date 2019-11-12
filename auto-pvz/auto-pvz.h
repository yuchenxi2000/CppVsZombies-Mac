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
void AutoFillIce(std::initializer_list<Coord> ls);
/*
 * 该函数实现垫材功能
 * 把种植、延迟铲除写在一个函数void DianCai();里
 * 然后使用时RunInThread(DianCai);
 */
void RunInThread(void (*func)());
#define StartAutoFillIceThread AutoFillIce
#define Coffee pvzice.Coffee
#define WaitUntil pvz.WaitUntil
#define Prejudge WaitUntil
#define Until pvz.Until
#define Wait pvz.Wait
#define Delay Wait
#define PlantSeed pvz.PlantSeed
#define Card slot.Card
/*
 * 暂时没有炮序、铲种炮功能
 * Pao, TryPao, Fire 都是程序自动找炮发射
 *
 * 如果出现炮落点在自身附近无法快速发炮请使用 DelayedFire
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
#define Shovel pvz.Shovel
#define Sleep pvz.Sleep
#define StartStopDancerThread dancer.Start
#define CancelStopDancerThread dancer.Pause

#endif /* auto_pvz_h */
