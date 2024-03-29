#ifndef scripts_hpp
#define scripts_hpp
#include "auto-pvz.h"
/*
 * lmintlcx 的二十四炮、白昼前置八炮、四炮、半场十二炮
 * 其余本人写的
 *
 * 这些脚本不保证能应对所有出怪组合，但极限慢速是可行的
 */
/*
 * 24炮建议极限出怪使用
 * 另，如果10、20波前残余僵尸血量不够，可能会导致提前刷新。
 */
void pe_24();
/*
 * 白昼前置八炮（有一些问题）
 * 节奏有问题，13波有两门炮没发射。
 * 不知道怎么解决。。
 */
void de_8();
/*
 * 经典十二炮
 * 刷新一波炸一波，20波前炸珊瑚
 * 比较稳定
 */
void pe_12();
/*
 * 经典四炮
 * lmintlcx的脚本，把9/19波收尾去了，因为非极限出怪提前刷新的原因
 */
void pe_4();
/*
 * 月夜十炮
 */
void me_10();
/*
 * 纯爷们十六炮
 */
void pe_16(bool bungee);
/*
 * 半场十二炮
 */
void pe_half_12();
/*
 * 双冰十六炮
 */
void pe_16_ice();

#endif /* scripts_hpp */
