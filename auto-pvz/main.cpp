#include "auto-pvz.h"
#include "scripts.hpp" // 非必须，一些键控脚本
/*
 * PvZ 键控框架 by Chenxi Yu
 * 游戏版本PvZ Mac v1.0.40
 *
 * 建议在选卡界面或战斗界面运行。
 * 键控程序启动后不能移动窗口，窗口不能被遮挡。
 * （因为macOS貌似不能把鼠标事件传给一个特定的进程，我试了CGEventPostToPid但失败了，
 * 所以鼠标事件是全局鼠标事件，运行时请小心谨慎！）
 *
 * 为键控精度，读取内存决定发炮时机，所以请以root权限运行。
 * Xcode内调root运行：
 * Product->Scheme->Edit Scheme->Debug Process As选root
 *
 * 函数基本和lmintlcx的python框架一致，一些功能暂未实现。
 * 具体函数接口见 auto-pvz.h 的注释
 *
 * 植物缩写见 pvz-global.cpp
 *
 * 改出怪、修改阳光、自动收集请配合Mac版修改器使用。
 * Mac版修改器：https://github.com/zhoury18/PvZHelper-Mac
 */
int main(int argc, const char * argv[]) {
    // 二十四炮键控脚本
    pe_24();
    return 0;
}
