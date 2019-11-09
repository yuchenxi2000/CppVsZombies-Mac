#ifndef auto_pvz_h
#define auto_pvz_h
#include "pvz-class.h"

/*
 * 为了适配pvzscript, cvz的接口
 * 给函数设置了多个名称
 */
/*
 * 函数基本和lmintlcx的python框架一致
 * （当然一些功能未实现）
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
#define Fire cannon.Fire
#define Pao Fire
#define TryPao Pao
#define DelayedFire cannon.DelayedFire
#define Shovel pvz.Shovel

#endif /* auto_pvz_h */
