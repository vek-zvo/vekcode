﻿#ifndef VEKAPPLISTVIEW_H
#define VEKAPPLISTVIEW_H

#include "vekAppData.h"
#include "../../vekAppAddMT.h"
#include "../../obj/objectExtend.h"
#include "../../obj/pObject.h"
#include "../../vekExtendDebug.h"
#include "../../vekExportJson.h"
#include "../../obj/common.h"
class vekAppListView:public QListView
{
        Q_OBJECT
public:
        vekAppListView(QWidget *parent = NULL);
        ~vekAppListView();
        void setListMap(std::map<QString,vekAppListView*> *pListMap,QTabWidget*);
        void addItem(BaseAppData*);
        void objectExtendApp();
protected:
        void contextMenuEvent ( QContextMenuEvent * event );
        void mouseDoubleClickEvent ( QMouseEvent * event );
private slots:
        void moveSlot();
        void setItemSlot();
        void unAppAdd();
        void setUpDelData(BaseDockData,BaseAppData*,objectTypeView);
        void unExportJson();
        void unDebugApp();
public slots:
        void ObjectRun();
signals:
        void toObjectArgs_ptr(BaseAppData*,objectTypeView);
        void toObjectArgs_cl(BaseAppData);
        void _startTray();
        void setUpDelDataSignal(BaseDockData*,BaseAppData*);
        void setUpGroupTabIcoSignal();
private:
        vekAppAddMT *_vek_App_Add=nullptr;
        vekExtendDebug* _vExtendDebug=nullptr;
        vekExportJson* _vExportJson=nullptr;
        int  m_hitIndex;
        vekAppData* m_pModel;
        QTabWidget* mBox;
        //这里还有一个用处就是在弹出的菜单需要分组的名称
        std::map<QString,vekAppListView*> *m_pListMap;
        //记录每个菜单项对应的列表，才能知道要转移到那个分组
        std::map<QAction*,vekAppListView*> m_ActionMap;
        void vekWriteJsonData();
        void vekReadJsonData(QString jsonPath);
        void vekInitJsonData();
        void ExportJson();
        void startApp(objectType);
        void deleteDockerTab(QString,QString);
        std::vector<QString> objectTypeStr={"容器设置","容器注册表","容器控制面板","容器软件删除|增加","winetricks","运行程序","调试运行(测试功能)","修改程序设置","导出自动配置文件","强行关闭本程序","删除本程序"};
        QMenu *pMenu=nullptr;
};
#endif // vekAppListView_H