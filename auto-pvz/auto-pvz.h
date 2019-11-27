#ifndef auto_pvz_h
#define auto_pvz_h
#include "pvz-class.h"
/*
 * 为了适配pvzscript, cvz的接口
 * 给函数设置了多个名称
 *
 * 函数基本和lmintlcx的python框架一致。
 *
 * 两个函数同时使用（指之间无Prejudge,Delay等延时）时，鼠标指针不会指向原来的位置。
 * 就算是特性吧。。
 */
/*
 * 该函数实现垫材等功能，以及需要与发炮操作不干扰的操作（结尾冰杀小偷等）
 * 把种植、延迟铲除写在一个函数void DianCai();里
 * 然后使用时RunningInThread(DianCai);
 */
void RunningInThread(void (*func)());
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
 * 等到游戏结束
 * 如果有其他线程运行而主线程退出会导致其他线程一并退出。
 * 改函数防止主线程提前退出导致操作未执行
 */
#define WaitUntilEnd pvz.WaitUntilEnd
#define WaitGameEnd WaitUntilEnd
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
 * 更新炮列表、跳过炮序中n门炮
 * 如果不需要调整炮序的话，UpdatePaoList 无需主动调用，
 * 因为程序会自动寻找场地上的炮
 *
 * 示例：
 * UpdatePaoList(); // 程序自动找炮
 * UpdatePaoList({}); // 程序自动找炮
 * UpdatePaoList({{1,1}, {2,1}}); // 按次序使用列表中的炮
 *
 * SkipPao(2); // 跳过炮列表中两门炮
 */
#define UpdatePaoList cannon.UpdatePaoList
#define SkipPao cannon.SkipPao
/*
 * 发炮
 *
 * 示例：
 * Pao({{2,9}});
 * Pao({{2,9}, {5,9}});
 *
 * 如果发现少发了一门，大多数情况是程序自动选择的炮在落点附近。
 *
 * 如果出现炮落点在自身附近无法快速发炮有以下解决方法：
 * 1. 调整炮序（使用UpdatePaoList）。不用落点附近的炮不就行了。缺点：调整炮序费一点脑子。
 * 2. 使用 DelayedPao。缺点是，函数有内部延时，无法一次发射多门炮，而且需要手动调整时序
 * 3. 使用 SmartPao。缺点是，在极特殊的情况下（详见SmartPao）程序无法通过调整点炮点实现发炮。
 *
 * （解释一下原因：当炮落点和鼠标点炮点相隔100像素之内时无法快速发炮）
 * （泳池场景当炮的落点在炮后轮时，使用该炮或者该炮上面一格、下面一格的炮会导致无法发炮。）
 * （白天场景当炮的落点在炮后轮时，使用该炮会导致无法发炮。）
 * （如，无法使用位于{3,7}, {4,7}, {5,7}处的炮炮击{4,7}）
 * （这是PvZ游戏代码实现的锅。。）
 *
 * 目前为止还没有发现“上界之风”现象，1.0.40版屋顶炮基本准确
 * 所以不会有 RoofPao。
 */
#define Fire cannon.Fire
#define Pao Fire
#define TryPao Pao
/*
 * 该函数确保两次点击像素间隔100以上，从而确保落点在炮附近时能正常发射
 *
 * 不过，当特殊情况，即只有一个炮填装完毕，且炮落点在炮中央附近时（炮身20-100像素），
 * 这时无论怎么调整点炮点都没法保证两次点击像素间隔100以上，所以无法发射。
 *
 * 该函数只适用于非屋顶场景，因为屋顶是斜的，太难写了。。。
 */
#define SmartPao cannon.SmartFire
/*
 * 延迟一段时间点炮（左键炮身->延迟一段时间->左键落点）
 */
#define DelayedFire cannon.DelayedFire
#define DelayedPao DelayedFire
/*
 * 铲植物
 * Shovel({1, 7});
 *
 * 铲南瓜请修改行数。
 * 比如，{2, 2} 有南瓜和豌豆，我想只铲南瓜，则 Shovel({2.1, 2});
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
 * 窗口前置
 */
#define WindowFront pvz.WindowFront
/*
 * 按空格停止游戏/继续游戏
 */
#define PressSpace keyboard.PressSpace
/*
 * 强制停止游戏/继续游戏（无暂停UI，但游戏内部时钟停止）
 * 注意，这个函数如果和女仆秘籍同时使用的话会出错！
 */
#define PauseGame pvz.PauseGame

#endif /* auto_pvz_h */
