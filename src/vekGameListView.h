﻿#ifndef VEKGAMELISTVIEW_H
#define VEKGAMELISTVIEW_H

#include "vekGameData.h"
#include "vekGameAddMT.h"
#include "objectExtend.h"
#include "vekInitObject.h"
#include "vekExtendDebug.h"
#include "vekExportJson.h"
#include "common.h"
using namespace std;
using json = nlohmann::json;

class vekGameListView:public QListView
{
        Q_OBJECT
public:
        vekGameListView(QWidget *parent = NULL);
        ~vekGameListView();
        void setListMap(std::map<QString,vekGameListView*> *pListMap,QTabWidget*);
        void addItem(BaseGameData*);
        void objectExtendGame();
protected:
        void contextMenuEvent ( QContextMenuEvent * event );
private slots:
        void moveSlot();
        void setItemSlot();
        void unGameAdd();
        void setUpDelData(BaseGameData*,objectTypeView);
        void unExportJson();
public slots:
        void ObjectRun();
signals:
        void toObjectArgs(BaseGameData,std::vector<QStringList>,objectType,objectWineBoot,objectWineServer);
        void toObjectArgs_ptr(BaseGameData*,objectTypeView);
        void toObjectArgs_cl(BaseGameData);
        void _startTray();
        void setUpDelDataSignal(BaseGameData* cGameData);
private:
        vekGameAddMT *_vek_Game_Add=nullptr;
        vekExtendDebug* _vExtendDebug=nullptr;
        vekExportJson* _vExportJson=nullptr;
        int  m_hitIndex;
        vekGameData* m_pModel;
        QTabWidget* mBox;
        //这里还有一个用处就是在弹出的菜单需要分组的名称
        std::map<QString,vekGameListView*> *m_pListMap;
        //记录每个菜单项对应的列表，才能知道要转移到那个分组
        std::map<QAction*,vekGameListView*> m_ActionMap;
        void vekLoadJsonData();
        void vekWriteJsonData();
        void vekReadJsonData(QString jsonPath);
        void vekInitJsonData();
        void ExportJson();
        std::vector<QString> objectTypeStr={"容器设置","容器注册表","容器控制面板","容器软件删除|增加","winetricks","运行程序","调试运行(测试功能)","修改程序设置","导出自动配置文件","强行关闭本程序","删除本程序"};
        QMenu *pMenu=nullptr;
};
#endif // VEKGAMELISTVIEW_H
