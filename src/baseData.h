﻿#ifndef BASEDATA_H
#define BASEDATA_H

#include <QString>
#include <iostream>
#include <map>
#include <vector>

typedef struct{
    QString rPath=nullptr;
    QString rKey=nullptr;
    QString rTValue=nullptr;
    QString rValue=nullptr;
}BaseDockRegs;

typedef struct {
    //CID
    QString gameCID=nullptr;
    //游戏名字
    QString gameName=nullptr;
    //游戏图标
    QString gameIco=nullptr;
    //游戏路径
    QString gameExe=nullptr;
    //运行参数
    QString gameOtherAgrs=nullptr;
    //Wine路径
    QString winePath=nullptr;
    //wine版本
    QString wineVersion=nullptr;
    //游戏运行Dock地址
    QString dockPath=nullptr;
    //容器名
    QString dockName=nullptr;
    //容器系统版本
    QString dockSystemVersion=nullptr;
    //工作路径
    QString workPath=nullptr;
    //DXVK状态
    bool dxvkState=false;
    //DXVK版本
    QString dxvkVerson=nullptr;
    //DxvkHUD
    bool dxvkHUD=false;
    //DxvkConfig
    QString dxvkConfigFile=nullptr;
    bool dxvkConfigFileState=false;
    //wine运行日志
    bool taskLog=false;
    //多任务内存优化
    bool taskMemoryOptimization=false;
    //内存共享
    bool taskMemorySharing=false;
    //实时优先级
    bool taskRealTimePriority=false;
    //默认字体
    bool defaultFonts=false;
    bool monoState=false;
    bool geckoState=false;
    QString mainPrcoName=nullptr;
    std::vector<QString> attachProc={};
    std::map<QString,QString> dockEnv={};
    std::vector<QString> dockLibs={};
    std::vector<BaseDockRegs> dockRegs={};
}BaseGameData;


typedef struct{
    //Wine安装名字
    QString WineInstallName=nullptr;
    //Wine安装版本
    QString wineInstallVer=nullptr;
    //Wine安装路径
    QString wineInstallPath=nullptr;
    //Wine Url
    QString wineInstallUrl=nullptr;
    QString wineInstallSrc=nullptr;
    QString wineInstallMono=nullptr;
    QString wineInstallGeckoX86=nullptr;
    QString wineInstallGeckoX86_64=nullptr;
    std::vector<QString> wineInstallDxvk={};
}BaseWineData;

typedef struct {
    QString wineName=nullptr;
    QString wineVersion=nullptr;
    QString wineGit=nullptr;
    QString Mono=nullptr;
    QString GeckoX86=nullptr;
    QString GeckoX86_64=nullptr;
    std::vector<QString> wineDxvk={};
}BaseWineGit;

typedef struct {
    QString dockPath=nullptr;
    QString dockName=nullptr;
    QString winePath=nullptr;
    QString mainProc=nullptr;
    std::vector<QString> attachProc={};
}procInfo;

typedef struct {
    std::map<QString,QString> Option={};
    //附加进程设定列表
    //std::map<QString,std::vector<QString>> attachProc;
    std::vector<QString> AttachProc={};
    std::map<QString,QString> Env={};
    std::vector<QString> Libs={};
    std::map<QString,QString> Dxvk={};
    std::vector<BaseDockRegs> Regs={};
    QString Args=nullptr;
}BaseAutoSetJson;

typedef struct {
    std::map<QString,std::map<QString,BaseGameData>> dockerVec={};
    std::map<QString,BaseWineData> wineVec={};
    std::map<QString,QString> gameScrSource={};
    std::map<QString,std::map<QString,QString>> gameJsonList={};
    std::map<QString,QString> wineSource={};
    std::map<QString,std::map<QString,BaseWineGit>> wineJsonList={};
}BaseLocalData;

extern BaseLocalData g_vekLocalData;
extern std::map<QString,std::map<QString,QString>> fontRes;
extern std::map<QString,std::map<QString,QString>> dxvkResCof;
extern std::map<QString,std::map<QString,QString>> dxvkResHUD;
extern std::map<QString,std::map<QString,QString>> dxvkRes;
static QString vekIPAPI="http://ip-api.com/json/";
#endif // BASEDATA_H