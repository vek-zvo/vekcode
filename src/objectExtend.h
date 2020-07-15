﻿#ifndef OBJECTEXTEND_H
#define OBJECTEXTEND_H

#include "common.h"
#include "objectJson.h"
#include <QTextCodec>
#include "vekInitObject.h"
#include "objectProcManage.h"
typedef enum{
    object_winecfg,
    object_regedit,
    object_control,
    object_uninstall,
    object_winetricks_gui,
    object_start,
    object_debugstart,
    object_setgame,
    object_forcekill,
    object_deletegame,
    object_regobject,
    object_wineboot,
    object_wineserver,
    object_dockSysver,
    object_disable,
    object_winetricks_libs,
    object_plugs,
    object_default
}objectType;
typedef enum{
    object_wineboot_e,
    object_wineboot_f,
    object_wineboot_i,
    object_wineboot_k,
    object_wineboot_r,
    object_wineboot_s,
    object_wineboot_u,
    object_wineboot_default
}objectWineBoot;
typedef enum{
    object_wineserver_k,
    object_wineserver_p,
    object_wineserver_w,
    object_wineserver_default
}objectWineServer;

class objectExtend :public QThread
{
    Q_OBJECT
public:
    explicit objectExtend(QObject *parent = nullptr);
    ~objectExtend();
    QProcess *m_cmd=nullptr;
protected:
    void run();
private:
    BaseGameData data;
    std::vector<QStringList> argsList;
    objectType objType;
    objectWineBoot objWineBootType;
    objectWineServer objWineServer;
    QString startArgs;
    void optionExtend();
    void extendApp();
    void executeArgsEnv();
    void baseExecuteWineCode(QString code,QStringList codeargs);
    void baseExecuteAppCode(QString code, QStringList codeargs);
    void extendWineRegeditCode(QString);
    void executeWineBoot(objectWineBoot);
    void executeWineServer(objectWineServer);
    void executeWinetricks();
    void executeWinetricksLibs();
    void waitObjectDone(bool);
    void dockEditSystemVersion();
    void extendPlugs();
    void monitorProc();
    void forcekill();
private slots:
    void setDockOptionObjectData(BaseGameData,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer);
};

#endif // VEKSTARTOPTINOBJECT_H