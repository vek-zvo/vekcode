﻿#include "vekAppPanel.h"
#include <QGridLayout>
vekAppPanel::vekAppPanel(QWidget *parent)
    : QWidget(parent)
{   
    vek_InitTabWidgetListApp();
    //vekLoadJsonData();
}

vekAppPanel::~vekAppPanel()
{

}
int cTab=0;
//初始化容器列表
void vekAppPanel::vek_InitTabWidgetListApp(){
    QGridLayout *gridLayout = new QGridLayout(this);
    m_pBox = new QTabWidget(this);
    gridLayout->addWidget(m_pBox);
    gridLayout->setContentsMargins(0,0,0,0);
    m_pBox->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    m_pListMap = new std::map<QString,vekAppListView*>();
    std::map<QString,BaseDockData>::iterator it;
    std::map<QString,BaseAppData>::reverse_iterator its;
    for(it=g_vekLocalData.dockerVec.begin();it!=g_vekLocalData.dockerVec.end();it++){
        vekAppListView *pListView = new vekAppListView();
        pListView->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
        pListView->setViewMode(QListView::IconMode);
        pListView->setFlow(QListView::LeftToRight);
        pListView->setResizeMode(QListView::Adjust);
        m_pBox->addTab(pListView,it->first);
        if(it->second.DockerVer=="win32"){
            QIcon icon(":/res/img/32.png");
            m_pBox->setTabIcon(cTab,icon);
            cTab+=1;
        }else{
            QIcon icon(":/res/img/64.png");
            m_pBox->setTabIcon(cTab,icon);
            cTab+=1;
        }
        if(!it->second.dData.empty()){
            for(its=it->second.dData.rbegin();its!=it->second.dData.rend();its++){
                BaseAppData *LID=new BaseAppData();
                *LID=its->second;
                connect(pListView, SIGNAL(_startTray()), this->parentWidget()->parentWidget(), SLOT(startTray()));
                pListView->addItem(LID);
            }
        }
        m_pListMap->insert(std::pair<QString,vekAppListView*>(it->first,pListView));
        pListView->setListMap(m_pListMap,m_pBox);
    }

}
//读取数据to容器列表
void vekAppPanel::vekLoadJsonData(){
    if(g_vekLocalData.dockerVec.empty()){
        return;
    }else{
        for(auto& y:g_vekLocalData.dockerVec){
            for(auto z:y.second.dData){
                vekAppListView* pList= new vekAppListView();
                QString nowTabName=y.first;
                BaseAppData *LID=new BaseAppData();
                *LID=z.second;
                for(std::map<QString,vekAppListView*>::iterator it = m_pListMap->begin();it!=m_pListMap->end();it++)
                {
                    if(it->first==nowTabName){
                        pList=it->second;
                        break;
                    }
                }
                pList->setViewMode(QListView::IconMode);
                pList->setFlow(QListView::LeftToRight);
                connect(pList, SIGNAL(_startTray()), this->parentWidget()->parentWidget(), SLOT(startTray()));
                pList->addItem(LID);
            }
        }
    }
}
void vekAppPanel::addAppSlot(){
    if(vek_app_multi_add==nullptr){
        vek_app_multi_add=new vekAppAddMulti();
        vek_app_multi_add->setAttribute(Qt::WA_DeleteOnClose,true);
        vek_app_multi_add->setWindowFlags(Qt::WindowStaysOnTopHint);
        vek_app_multi_add->setWindowTitle("Vek游戏增加方式选择");
        connect(vek_app_multi_add,&vekAppAddMulti::_unMultAppAdd,this,&vekAppPanel::unMultAppAdd);
        connect(vek_app_multi_add,&vekAppAddMulti::_MultiAppDiy,this,&vekAppPanel::addAppDiy);
        connect(vek_app_multi_add,&vekAppAddMulti::_MultiAppAuto,this,&vekAppPanel::addAppAuto);
        vek_app_multi_add->show();
    }
}
void vekAppPanel::addAppDiy(){
    if(vek_app_add==nullptr){
        vek_app_add=new vekAppAddMT();
        vek_app_add->setAttribute(Qt::WA_DeleteOnClose,true);
        vek_app_add->setWindowFlags(Qt::WindowStaysOnTopHint);
        vek_app_add->setWindowTitle("Vek软件增加");
        BaseDockData tmpData=GetDockerData(m_pBox->tabText(m_pBox->currentIndex()));
        vek_app_add->vekAppAddConnectObject(&tmpData,nullptr,object_addApp);
        vek_app_add->show();
        connect(vek_app_add,&vekAppAddMT::_unDiyAppAdd,this,&vekAppPanel::unDiyAppAdd);
        connect(vek_app_add,SIGNAL(doneAddApp(BaseDockData*,BaseAppData*)), this, SLOT(addAppObject(BaseDockData*,BaseAppData*)));
    }
}
void vekAppPanel::addAppAuto(){
    if(vek_app_add_auto==nullptr){
        vek_app_add_auto=new vekAppAddAT();
        vek_app_add_auto->setAttribute(Qt::WA_DeleteOnClose,true);
        vek_app_add_auto->setWindowFlags(Qt::WindowStaysOnTopHint);
        vek_app_add_auto->setWindowTitle("自动配置容器");
        vek_app_add_auto->connectDockObject();
        vek_app_add_auto->show();
        connect(vek_app_add_auto,&vekAppAddAT::_unAutoDock,this,&vekAppPanel::unAutoDock);
        connect(vek_app_add_auto,SIGNAL(autoObjDock(BaseDockData*,BaseAppData*)),this,SLOT(addAppObject(BaseDockData*,BaseAppData*)));
    }
}
void vekAppPanel::objAppInstall(){
    bool dState=false;
    if(g_vekLocalData.wineVec.empty()){
        vekTip("未发现您的电脑上装有wine请安装wine后重试");
        return;
    }
    if(g_vekLocalData.dockerVec.empty()){
        dState=vekMesg("您的电脑上未发现容器无法安装软件,是否初始化一个容器用于软件安装");
        if(!dState){
            return;
        }
    }
    BaseDockData baseDockerData;
    BaseAppData  baseAppData;
    objectAppMT* objNewDock=new objectAppMT(&baseAppData,&baseDockerData);
    QString dockName="vekON1";
    baseAppData.DefaultFonts=true;
    //判断当前容器数量是否为0;
    if(m_pBox->count()!=0){
        //当前容器目标
        dockName =m_pBox->tabText(m_pBox->currentIndex());
    }else{
        dState=true;
    }
    //dState=true表示容器数量为0,无容器需初始化
    if(dState){
        //涉及一个问题：当容器列表为0
        QString sName;
        if(g_vekLocalData.wineVec.size()>1){
            QStringList items;
            for(auto wName:g_vekLocalData.wineVec){
                items<<wName.second.IwineName;
            }
            QString dlgTitle="Wine版本选择";
            QString txtLabel="当前Wine版本列表";
            int     curIndex=0;
            bool    editable=false;
            bool    ok=false;
            sName = QInputDialog::getItem(this, dlgTitle,txtLabel,items,curIndex,editable,&ok);
            for(auto wName:g_vekLocalData.wineVec){
                if(wName.second.IwineName==sName){
                    baseDockerData.WinePath=g_vekLocalData.wineVec[sName].IwinePath;
                }
            }
        }else{
            baseDockerData.WinePath=g_vekLocalData.wineVec.begin()->second.IwinePath;
            sName=g_vekLocalData.wineVec.begin()->second.IwineName;
        }
        dState=vekMesg("确认安装程序类型!Yes->32位,NO->64位");
        if(!dState){
            baseDockerData.DockerVer="win64";
        }
        if(g_vekLocalData.wineVec[sName].IwineName.contains("deepin",Qt::CaseSensitive)&baseDockerData.DockerVer=="win64"){
            vekError("deepin-wine5不支持64位容器,默认强行以32位初始化容器!");
            baseDockerData.DockerVer="win32";
        }
        for(auto a:g_vekLocalData.dockerVec){
            if(a.first==dockName){
                dState=vekMesg("发现相同容器如继续执行将重置该容器,是否覆盖容器创建?");
                break;
            }
        }
        if(!dState){
            addGroupSlot(&baseDockerData);
        }else{
            return;
        }
        baseDockerData.DockerPath=QDir::currentPath()+"/vekDock";
        baseDockerData.DockerName=dockName;
        baseDockerData.MonoState=true;
        baseDockerData.GeckoState=true;
        objNewDock->newDock();
    }
    else//否则从全局本地配置文件提取容器参数
    {
        if(g_vekLocalData.dockerVec.empty()){
            return;
        }else{
            //通过容器名定位当前容器名对应调用当前容器相应功能包含安装软件界面等。
            baseDockerData=g_vekLocalData.dockerVec.at(dockName);
        }
    }
    if(baseDockerData.WineVersion.contains("deepin",Qt::CaseSensitive)){
        vekError("deepin-wine5不支持64位容器,可能部分64位软件软件安装程序无法运行!");
    }
    objectExtend* _objectExtend=new objectExtend();
    objectType _objType=object_uninstall;
    std::vector<QStringList> _codeAgrs;
    _objectExtend->setDockOptionObjectData(baseDockerData,baseAppData.AppCID,_codeAgrs,_objType,objectWineBoot::object_wineboot_default,objectWineServer::object_wineserver_default);
    _objectExtend->start();
    delete objNewDock;
    objNewDock=nullptr;
}
void vekAppPanel::objInitDock(){
    bool dState=false;
    QString dockName;
    QString dockBit="win32";
    if(g_vekLocalData.wineVec.empty()){
        vekTip("未发现您的电脑上装有wine请安装wine后重试");
        return;
    }
    BaseDockData baseDockerData;
    BaseAppData  baseAppData;
    objectAppMT* objNewDock=new objectAppMT(&baseAppData,&baseDockerData);
    baseAppData.DefaultFonts=true;
    QString sName;
    QStringList items;
    QStringList itemsbit;
    //选择wine版本
    for(auto wName:g_vekLocalData.wineVec){
        items<<wName.second.IwineName;
    }
    QString wTitle="选择Wine版本";
    QString wLabel="当前Wine版本列表";
    int     wIndex=0;
    bool    wtable=false;
    bool    w_ok=false;
    sName = QInputDialog::getItem(this, wTitle,wLabel,items,wIndex,wtable,&w_ok);
    //选择容器系统版本
    if(sName.contains("deepin",Qt::CaseSensitive)){
        vekError("deepin-wine5不支持64位容器,默认强行以32位初始化容器!");
        itemsbit<<"win32";
    }else{
        itemsbit<<"win32"<<"win64";
    }
    QString dTitle="选择容器系统版本";
    QString dLabel="支持容器列表";
    int     dIndex=0;
    bool    dtable=false;
    bool    dok=false;
    dockBit = QInputDialog::getItem(this, dTitle,dLabel,itemsbit,dIndex,dtable,&dok);
    //输入容器名
    QString dnTitle="容器名";
    QString dnLabel="建议采用英文名字";
    dockName="vekON1";
    QLineEdit::EchoMode echoMode=QLineEdit::Normal;//正常文字输入
    bool dn_ok=false;
    dockName = QInputDialog::getText(nullptr, dnTitle,dnLabel, echoMode,dockName, &dn_ok);
    for(auto wName:g_vekLocalData.wineVec){
        if(wName.second.IwineName==sName){
            baseDockerData.WinePath=g_vekLocalData.wineVec[sName].IwinePath;
            break;
        }
    }
    if(dockName==nullptr){
        vekTip("容器名不能为空!");
        return;
    }
    if(baseDockerData.WinePath==nullptr){
        vekTip("找不到选用对应Wine");
        return;
    }
    for(auto a:g_vekLocalData.dockerVec){
        if(a.first==dockName){
            dState=true;
            break;
        }
    }
    if(dState){
        dState=vekMesg("发现相同容器如继续执行将重置该容器,是否覆盖容器创建?");
        if(!dState){
            return;
        }
    }
    if(!dState){
       addGroupSlot(&baseDockerData);
    }
    baseDockerData.DockerVer=dockBit;
    baseDockerData.DockerPath=QDir::currentPath()+"/vekDock";
    baseDockerData.DockerName=dockName;
    baseDockerData.MonoState=true;
    baseDockerData.GeckoState=true;
    objNewDock->newDock();
    objNewDock=nullptr;
}
void vekAppPanel::objectRunApp(){
    if(m_pListMap!=nullptr){
        m_pListMap->at(m_pBox->tabText(m_pBox->currentIndex()))->ObjectRun();
    }
}
void vekAppPanel::unAutoDock(){
    vek_app_add_auto=nullptr;
}
void vekAppPanel::unMultAppAdd(){
    vek_app_multi_add=nullptr;
}
void vekAppPanel::unDiyAppAdd(){
    vek_app_add=nullptr;
}
void vekAppPanel::addAppObject(BaseDockData* dcokData,BaseAppData* appData){
    vekAppListView* pList=new vekAppListView();
    BaseAppData* _tempBaseData=new BaseAppData;
    _tempBaseData=appData;
    QString nowTabName=dcokData->DockerName;
    bool tabState=false;
    if(m_pListMap->count(nowTabName)>0){
        tabState=true;
    }
    if(!tabState){
        addGroupSlot(dcokData);
    }
    for(std::map<QString,vekAppListView*>::iterator it = m_pListMap->begin();it!=m_pListMap->end();it++)
    {
        if(it->first==nowTabName){
            pList=it->second;
            break;
        }
    }
    pList->setViewMode(QListView::IconMode);
    pList->setFlow(QListView::LeftToRight);
    connect(pList, SIGNAL(_startTray()), this->parentWidget()->parentWidget(), SLOT(startTray()));
    pList->addItem(_tempBaseData);
}
void vekAppPanel::upTabIco(){
    cTab=0;
    for(auto a:g_vekLocalData.dockerVec){
        if(a.second.DockerVer=="win32"){
            QIcon icon(":/res/img/32.png");
            m_pBox->setTabIcon(cTab,icon);
            cTab+=1;
        }else{
            QIcon icon(":/res/img/64.png");
            m_pBox->setTabIcon(cTab,icon);
            cTab+=1;
        }
    }
}
void vekAppPanel::addGroupSlot(BaseDockData* dcokData)
{
    if (!dcokData->DockerName.isEmpty())
    {
        vekAppListView *pListView1 = new vekAppListView(this);
        pListView1->setViewMode(QListView::IconMode);
        pListView1->setFlow(QListView::LeftToRight);
        m_pBox->addTab(pListView1,dcokData->DockerName);
        m_pListMap->insert(std::pair<QString,vekAppListView*>(dcokData->DockerName,pListView1));
    }
    upTabIco();
    //要确保每个MyListView钟的m_pListMap都是一致的，不然就会有错了。
    //因为弹出的菜单进行转移的时候需要用到
    std::map<QString,vekAppListView*>::iterator it;
    for (it=m_pListMap->begin(); it != m_pListMap->end(); ++it)
    {
        vekAppListView* pList = it->second;
        pList->setListMap(m_pListMap,m_pBox);
    }
}
