# CppVsZombies-Mac

Plants vs. Zombies v1.0.40 (Mac) 简易键控框架

函数基本上和 lmintlcx 的 python 框架一致

适用系统 macOS < 10.15（PvZ都玩不了键控个啥呦）

## 使用

1. 下载 Xcode，并打开

2. 新建项目（菜单栏 File -> New -> Project），选 macOS -> Command Line Tool，language 选 C++

3. 添加 auto-pvz 文件夹里的文件（菜单栏 File -> Add Files to "你的项目名"）

4. 设置 Build Phases -> Link Binary With Librarys，添加 CoreGraphics、Foundation、AppKit

5. 设置以 root 身份运行：Product -> Scheme -> Edit Scheme -> Debug Process As 选 root

6. 进入 endless 选卡界面，运行程序（在非选卡界面运行不保证鼠标不鬼畜，233）

## 注意事项

见代码注释

建议仔细看 main.cpp, auto-pvz.h, pvz-global.cpp 里的注释

## 致谢

zhoury18/PvZHelper-Mac

lmintlcx/pvzscripts

vector-wlc/CppVsZombies
