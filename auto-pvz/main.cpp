#include "auto-pvz.h"
#include "scripts.hpp" // 非必须，一些键控脚本
/*
 * 24炮，自动存冰、自动找炮发射
 * 游戏版本PvZ Mac v1.0.40
 *
 * 程序不能在进入选卡前运行。
 * 键控程序启动后不能移动窗口，窗口不能被遮挡。
 * （因为macOS貌似不能把鼠标事件传给一个特定的进程，我试了CGEventPostToPid但失败了，
 * 所以鼠标事件是全局鼠标事件，运行时请小心谨慎！）
 *
 * 为键控精度，读取内存决定发炮时机，所以请以root权限运行。
 * Xcode内调root运行：
 * Product->Scheme->Edit Scheme->Debug Process As选root
 *
 * 函数基本和lmintlcx的python框架一致
 * （当然一些功能未实现。macOS 10.15废了32位程序，搞得我不想认真弄了。。。）
 *
 * 改出怪、修改阳光、自动收集请配合Mac版修改器使用。
 * Mac版修改器：https://github.com/zhoury18/PvZHelper-Mac
 */
int main(int argc, const char * argv[]) {
    // 二十四炮键控脚本
//    pe_24();
    pe_4();
    return 0;
}
