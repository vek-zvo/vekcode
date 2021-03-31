#include "vekAppAddMT.h"
#include "ui_common.h"

vekAppAddMT::vekAppAddMT(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vekAppAddMT)
{
    ui->setupUi(this);
    pObject::qwidgetGeometry(this);
}

vekAppAddMT::~vekAppAddMT()
{
    emit _unDiyAppAdd();
}
//绑定槽
void vekAppAddMT::vekAppAddConnectObject(DockData* _data,QString _appCID,OBJAPP _objType){
    objType=_objType;
    //检测增加游戏必要的设置
    connect(ui->pushButton_Set,&QPushButton::clicked,this,&vekAppAddMT::objectButton);
    //设置游戏安装目录
    connect(ui->pushButton_SetAppExe,&QPushButton::clicked,this,&vekAppAddMT::objectButton);
    //设置游戏安装目录
    connect(ui->pushButton_workPath,&QPushButton::clicked,this,&vekAppAddMT::objectButton);
    //设置Wine容器目录
    connect(ui->pushButton_SetDockPath,&QPushButton::clicked,this,&vekAppAddMT::objectButton);
    //设置ICO文件路径
    connect(ui->pushButton_setIco,&QPushButton::clicked,this,&vekAppAddMT::objectButton);
    //init Dock
    connect(ui->pushButton_initDock,&QPushButton::clicked,this,&vekAppAddMT::objectButton);
    connect(ui->pushButton_SaveDxvkConfFile,&QPushButton::clicked,this,&vekAppAddMT::objectButton);
    connect(ui->checkBox_dxvkConfigState,&QCheckBox::stateChanged,this,&vekAppAddMT::dxvkOptionLoad);
    connect(ui->checkBox_stateDxvk,&QCheckBox::stateChanged,this,&vekAppAddMT::dxvkOptionLoad);
    //显示当前安装wine
    ui->comboBox_RunWine->clear();
    if(!g_vekLocalData.local_WineData.empty())
    {
        for(auto & x :g_vekLocalData.local_WineData)
        {
            ui->comboBox_RunWine->addItem(x.first);
        }
        for(auto& d:g_vekLocalData.local_WineData){
            for(auto& dx:d.second.IwineDxvk){
                ui->comboBox_dxvkversion->addItem(dx);
            }
        }
    }else{
        pObject::vekTip("请先安装Wine");
        this->close();
    }
    for(auto&y:_dockSystemVersion){
        ui->comboBox_dockSystemVersion->addItem(y);
    }
    for(auto n:_dockVer){
        ui->comboBox_dockbit->addItem(n);
    }
    for(auto m:_dockWineVer){
        ui->comboBox_winebit->addItem(m);
    }
    if(!g_vekLocalData.local_DockerData.empty()){
        for(auto &a:g_vekLocalData.local_DockerData){
            ui->comboBox_DockName->addItem(a.first);
        }
    }
    initAppAndDockData(_data,_appCID);
    //控件缺省设置
    ui->pushButton_setIco->setIconSize(QSize(80,80));
    ui->pushButton_setIco->setIcon(QIcon(tempAppData->app_ICO));
    ui->lineEdit_RunDockPath->setText(tempDockData->docker_Path);
    ui->comboBox_DockName->setCurrentText(tempDockData->docker_Name);
    ui->comboBox_RunWine->setCurrentText(tempDockData->docker_WineVersion);  
    ui->checkBox_Mono->setChecked(tempDockData->docker_MonoState);
    ui->checkBox_Gecko->setChecked(tempDockData->docker_GeckoState);
    ui->comboBox_dockbit->setCurrentText(tempDockData->docker_SystemBitVersion);
    ui->comboBox_winebit->setCurrentText(tempDockData->docker_WineVersion);
    ui->comboBox_dockSystemVersion->setCurrentText(tempAppData->app_SystemVersion);
    ui->checkBox_Ass->setChecked(tempAppData->app_DisableAss);
    ui->lineEdit_AppName->setText(tempAppData->app_Name);
    ui->lineEdit_AppInstallExe->setText(tempAppData->app_Exe);
    ui->lineEdit_workPath->setText(tempAppData->app_WorkPath);
    ui->checkBox_winerunlog->setChecked(tempAppData->app_TaskLog);
    ui->lineEdit_otherAgrs->setText(tempAppData->app_AgrsCode);
    ui->lineEdit_dxvkConfigFIle->setText(tempAppData->app_DxvkConfig);
    ui->checkBox_wineMemorySharing->setChecked(tempAppData->app_SharedMemory);
    ui->checkBox_wineMemoryOptimization->setChecked(tempAppData->app_WriteCopy);
    ui->checkBox_wineRealTimePriority->setChecked(tempAppData->app_RtServer);
    ui->checkBox_stateDxvk->setChecked(tempAppData->app_DxvkState);
    ui->comboBox_dxvkversion->setCurrentText(tempAppData->app_DxvkVersion);
    ui->checkBox_statedxvkhud->setChecked(tempAppData->app_DxvkHUD);
    ui->checkBox_DefaultFonts->setChecked(tempAppData->app_DefaultFonts);
    ui->lineEdit_MainProcName->setText(tempAppData->app_MainProcName);
    ui->checkBox_dxvkConfigState->setChecked(tempAppData->app_DxvkConfigFileState);
    if(objType==SEETING){
        if(tempDockData->docker_Path!=nullptr){
            ui->comboBox_dockbit->setEnabled(false);
            ui->comboBox_DockName->setEnabled(false);
            ui->comboBox_dockSystemVersion->setEnabled(false);
        }
    }
    dxvkOptionLoad();
    loadTableView(ui->tableView_EnvList,tempAppData);
    loadTableView(ui->tableView_ProcList,tempAppData);
    loadTableView(ui->tableView_RegsList,tempAppData);
    plugsLoad();
}
void vekAppAddMT::initAppAndDockData(DockData* _data,QString _appCID){
    //_data nullptr =add
    if(_data->docker_Path==nullptr){
        tempDockData=new DockData;
        tempDockData->docker_Path=QApplication::applicationDirPath()+"/vekDock";
    }else{
        *tempDockData=pObject::getDockerData(_data->docker_Name);
        if(_appCID!=nullptr){
            auto it =tempDockData->docker_Data.find(_appCID);
            *tempAppData=it->second;
        }
    }
}
void vekAppAddMT::plugsLoad(){
    for(auto a:g_vekLocalData.local_WineData){
        if(a.first==ui->comboBox_RunWine->currentText()){
            if(!QFile(a.second.iWinePath+"/plugs/Mono.msi").exists()){
                ui->checkBox_Mono->setEnabled(false);
            }
            if(!QFile(a.second.iWinePath+"/plugs/GeckoX86.msi").exists()&&!QFile(a.second.iWinePath+"/plugs/GeckoX86_64.msi").exists()){
                ui->checkBox_Gecko->setEnabled(false);
            }
            if(a.second.IwineDxvk.empty()){
                ui->checkBox_stateDxvk->setEnabled(false);
                ui->comboBox_dxvkversion->setEnabled(false);
                ui->checkBox_statedxvkhud->setEnabled(false);
                ui->lineEdit_dxvkConfigFIle->setEnabled(false);
            }
        }
    }
}
void vekAppAddMT::dxvkOptionLinkState(bool cState){
    ui->comboBox_dxvkversion->setEnabled(cState);
    ui->checkBox_statedxvkhud->setEnabled(cState);
    ui->checkBox_dxvkConfigState->setEnabled(cState);
    ui->lineEdit_dxvkConfigFIle->clear();
    ui->textEdit_dxvkConfigFileData->clear();
    ui->lineEdit_dxvkConfigFIle->setEnabled(cState);
    ui->textEdit_dxvkConfigFileData->setEnabled(cState);
    ui->pushButton_SaveDxvkConfFile->setEnabled(cState);
}
void vekAppAddMT::dxvkOptionLoad(){
    dxvkOptionLinkState(false);
    if(ui->checkBox_stateDxvk->checkState()){
        dxvkOptionLinkState(true);
        if(ui->checkBox_dxvkConfigState->checkState()){
            QString dxvkPath;
            if(ui->lineEdit_dxvkConfigFIle->text()!=nullptr)
            {
                dxvkPath=ui->lineEdit_dxvkConfigFIle->text();
            }
            else
            {
                auto it=g_vekLocalData.local_WineData.find(ui->comboBox_RunWine->currentText());
                dxvkPath=it->second.iWinePath+"/dxvk/dxvk.conf";
                ui->lineEdit_dxvkConfigFIle->setText(dxvkPath);
            }
            ui->textEdit_dxvkConfigFileData->setText(pObject::getFileStr(dxvkPath));
        }
    }else{
        ui->checkBox_statedxvkhud->setChecked(false);
        ui->checkBox_dxvkConfigState->setChecked(false);
    }
}
//SetTable
void vekAppAddMT::setTableView(QTableView* qtv){
    qtv->setSelectionBehavior(QAbstractItemView::SelectRows);
    qtv->setSelectionMode(QAbstractItemView::SingleSelection);
    qtv->setSortingEnabled(false);
    qtv->verticalHeader()->hide();
    qtv->setWordWrap(false);
    qtv->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    qtv->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    qtv->setShowGrid(false);
    //ui->tableView_WineSrcList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    qtv->setAlternatingRowColors(true);  // alternative colors
    qtv->setFrameShape(QFrame::NoFrame);
    qtv->horizontalHeader()->setStretchLastSection(true);
    qtv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}
//loadTable
void vekAppAddMT::loadTableView(QTableView* qtv,AppData* ePdata){
    tableModel=new QStandardItemModel();
    // set columns
    int i=0;
    QStringList columnTitles;
    if(qtv==ui->tableView_EnvList){
        columnTitles << "环境变量名" << "环境变量值";

        if(ePdata!=nullptr){
            if(!ePdata->app_DockerEnv.empty()){
                for(auto &[k,j]:ePdata->app_DockerEnv){
                    int x=i++;
                    tableModel->setItem(x,0,new QStandardItem(k));
                    tableModel->setItem(x,1,new QStandardItem(j));
                }
            }
        }
    }
    if(qtv==ui->tableView_ProcList){
        columnTitles <<"附加进程名";
        if(ePdata!=nullptr)
        {
            if(!ePdata->app_Attachproc.empty()){
                for(auto j:ePdata->app_Attachproc){
                    int x=i++;
                    tableModel->setItem(x,0,new QStandardItem(j));
                }
            }
        }
    }
    if(qtv==ui->tableView_RegsList){
        columnTitles<<"注册表路径"<<"注册表键"<<"值类型"<<"注册表值";
        if(ePdata!=nullptr){
            if(!ePdata->app_DockerRegs.empty()){
                for(auto j:ePdata->app_DockerRegs){
                    int x=i++;
                    tableModel->setItem(x,0,new QStandardItem(j.rPath));
                    tableModel->setItem(x,1,new QStandardItem(j.rKey));
                    tableModel->setItem(x,2,new QStandardItem(j.rTValue));
                    tableModel->setItem(x,3,new QStandardItem(j.rValue));
                }
            }
        }
    }
    setTableView(qtv);
    qtv->setModel(tableModel);
    tableModel->setHorizontalHeaderLabels(columnTitles);
    qtv->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(qtv,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(clicked_rightMenu(QPoint)));
}
void vekAppAddMT::clicked_rightMenu(const QPoint &/*pos*/)
{
    QTableView* signalSrc = (QTableView*)sender();  // 获取到了发送该信号按钮的指针
    //创建菜单对象
    QMenu *pMenu = new QMenu(this);
    QAction *pNewTask = new QAction(tr("新建"), this);
    QAction *pDeleteTask = new QAction(tr("删除"), this);
    pNewTask->setData(1);
    pDeleteTask ->setData(2);
    pNewTask->setObjectName(signalSrc->objectName());
    pDeleteTask->setObjectName(signalSrc->objectName());
    //把QAction对象添加到菜单上
    pMenu->addAction(pNewTask);
    pMenu->addAction(pDeleteTask);
    //连接鼠标右键点击信号
    connect(pNewTask, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
    connect(pDeleteTask, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
    //在鼠标右键点击的地方显示菜单
    pMenu->exec(QCursor::pos());
    QList<QAction*> list = pMenu->actions();
    foreach (QAction* pAction, list) delete pAction;
    delete pMenu;
}
void vekAppAddMT::onTaskBoxContextMenuEvent()
{
    QAction *pEven = qobject_cast<QAction *>(this->sender());
    int iType = pEven->data().toInt();
    QTableView* _tempQTableView=new QTableView;
    if(pEven->objectName()=="tableView_EnvList"){
        _tempQTableView=ui->tableView_EnvList;
    }else if(pEven->objectName()=="tableView_ProcList"){
        _tempQTableView=ui->tableView_ProcList;
    }else if(pEven->objectName()=="tableView_RegsList"){
        _tempQTableView=ui->tableView_RegsList;
    }
    switch (iType)
    {
    case 1:
        objectAdd(_tempQTableView);
        break;
    case 2:
        objectDelete(_tempQTableView);
        break;
    default:
        break;
    }
}
void vekAppAddMT::objectAdd(QTableView* qTableView){
    QAbstractItemModel *modessl = qTableView->model();
    modessl->insertRow(modessl->rowCount());
    qTableView->setModel(modessl);
}
void vekAppAddMT::objectDelete(QTableView* qTableView){
    int curRow=qTableView->currentIndex().row();
    int curRows = qTableView->model()->rowCount();
    if(curRows==0){
        return;
    }
    if(curRow > -1){
        QAbstractItemModel *modessl = qTableView->model();
        QModelIndex indextemp = modessl->index(curRow,0);
        QString datatemp = modessl->data(indextemp).value<QString>();
        modessl->removeRow(curRow);
        qTableView->setModel(modessl);
    }
}
//控件数据to Class
bool vekAppAddMT::vekAppConfigObj(){  
    if(tempAppData->app_CID==nullptr){
        objectJson _objectJson;
        tempAppData->app_CID=_objectJson.GetRandomCID();
    }
    tempAppData->app_Exe=ui->lineEdit_AppInstallExe->text();
    tempAppData->app_Name=ui->lineEdit_AppName->text();
    tempAppData->app_WorkPath=ui->lineEdit_workPath->text();
    tempAppData->app_AgrsCode=ui->lineEdit_otherAgrs->text();
    //Docker默认参数

    if(ui->lineEdit_RunDockPath->text()!=nullptr){
        tempDockData->docker_Path=ui->lineEdit_RunDockPath->text();
    }else{
        tempDockData->docker_Path=QApplication::applicationDirPath()+"/vekDock";
    }
    if(ui->comboBox_DockName->currentText()!=nullptr){
        tempDockData->docker_Name=ui->comboBox_DockName->currentText();
    }else{
        tempDockData->docker_Name="vekON1";
    }
    tempDockData->docker_WineVersion=ui->comboBox_RunWine->currentText();
    auto it=g_vekLocalData.local_WineData.find(ui->comboBox_RunWine->currentText());
    tempDockData->docker_WinePath=it->second.iWinePath;
    tempDockData->docker_SystemVersion=ui->comboBox_dockSystemVersion->currentText();
    tempDockData->docker_SystemBitVersion=ui->comboBox_dockbit->currentText();
    tempDockData->docker_WineVersion=ui->comboBox_winebit->currentText();
    tempDockData->docker_MonoState=ui->checkBox_Mono->checkState();
    tempDockData->docker_GeckoState=ui->checkBox_Gecko->checkState();
    tempAppData->app_DisableAss=ui->checkBox_Ass->checkState();
    if(ui->lineEdit_dxvkConfigFIle->text()!=nullptr){
        tempAppData->app_DxvkConfig=ui->lineEdit_dxvkConfigFIle->text();
    }
    if(tempAppData->app_ICO==nullptr){
        tempAppData->app_ICO=":/res/img/vek.ico";
    }
    //dxvk参数
    tempAppData->app_SystemVersion=ui->comboBox_dockSystemVersion->currentText();
    tempAppData->app_MainProcName=ui->lineEdit_MainProcName->text();
    tempAppData->app_DxvkState=ui->checkBox_stateDxvk->checkState();
    tempAppData->app_DxvkVersion=ui->comboBox_dxvkversion->currentText();
    tempAppData->app_DxvkHUD=ui->checkBox_statedxvkhud->checkState();
    tempAppData->app_DxvkConfigFileState=ui->checkBox_dxvkConfigState->checkState();
    tempAppData->app_DxvkConfig=ui->lineEdit_dxvkConfigFIle->text();
    //优化参数
    tempAppData->app_TaskLog=ui->checkBox_winerunlog->checkState();
    tempAppData->app_SharedMemory=ui->checkBox_wineMemorySharing->checkState();
    tempAppData->app_WriteCopy=ui->checkBox_wineMemoryOptimization->checkState();
    tempAppData->app_RtServer=ui->checkBox_wineRealTimePriority->checkState();
    tempAppData->app_DefaultFonts=ui->checkBox_DefaultFonts->checkState();
    int envCurRow=ui->tableView_EnvList->model()->rowCount();
    int procCurRow=ui->tableView_ProcList->model()->rowCount();
    int regsCurRow=ui->tableView_RegsList->model()->rowCount();
    if(envCurRow>0){
        tempAppData->app_DockerEnv.clear();
        QAbstractItemModel *modelEnv = ui->tableView_EnvList->model();
        for(int i=0;i<=envCurRow-1;i++){
            QString dataTempA = modelEnv->data(modelEnv->index(i,0)).value<QString>();
            QString dataTempB = modelEnv->data(modelEnv->index(i,1)).value<QString>();
            if(dataTempA!=nullptr&&dataTempB!=nullptr){
                tempAppData->app_DockerEnv.insert(pair<QString,QString>(dataTempA,dataTempB));
            }
        }
    }
    if(procCurRow>0){
        tempAppData->app_Attachproc.clear();
        QAbstractItemModel *modelProc = ui->tableView_ProcList->model();
        for(int i=0;i<=procCurRow-1;i++){
            QString dataTempC = modelProc->data(modelProc->index(i,0)).value<QString>();
            qInfo()<<dataTempC;
            if(dataTempC!=nullptr){
                tempAppData->app_Attachproc.push_back(dataTempC);
            }
        }
    }
    if(regsCurRow>0){
        tempAppData->app_DockerRegs.clear();
        regs _tRegs;
        QAbstractItemModel *modelRegs = ui->tableView_RegsList->model();
        for(int i=0;i<=regsCurRow-1;i++){
            _tRegs.rPath = modelRegs->data(modelRegs->index(i,0)).value<QString>();
            _tRegs.rKey = modelRegs->data(modelRegs->index(i,1)).value<QString>();
            _tRegs.rTValue= modelRegs->data(modelRegs->index(i,2)).value<QString>();
            _tRegs.rValue = modelRegs->data(modelRegs->index(i,3)).value<QString>();
            if(_tRegs.rPath!=nullptr&&_tRegs.rKey!=nullptr&&_tRegs.rTValue!=nullptr){
                tempAppData->app_DockerRegs.push_back(_tRegs);
            }
        }
    }
    return checkAllOption();
}
//检查所有必备参数
bool vekAppAddMT::checkAllOption(){
    if(!checkAppOption()){
        return false;
    }
    if(!checkDocerOption()){
        return false;
    }
    if(!checkDxvkOption()){
        return false;
    }
    return true;
}
//检查dxvk参数
bool vekAppAddMT::checkDxvkOption(){
    bool dxvkState=true;
    if(tempAppData->app_DxvkConfigFileState){
        if(tempAppData->app_DxvkConfig==nullptr){
            pObject::vekError("启用dxvk配置文件功能后,必须指定dxvk配置文件路径");
            dxvkState=false;
        }
    }
    qInfo()<<"dxvk参数"<<dxvkState;
    return dxvkState;
}
//检查App参数
bool vekAppAddMT::checkAppOption(){
    if(tempAppData->app_Name==nullptr)
    {
        pObject::vekError("请填写游戏名");
        return false;
    }
    if(tempAppData->app_Exe==nullptr)
    {
        pObject::vekError("请设置游戏执行文件");
        return false;
    }
    if(tempAppData->app_WorkPath==nullptr)
    {
        pObject::vekError("请设置游戏工作目录");
        return false;
    }

    if(tempAppData->app_MainProcName==nullptr){
        pObject::vekError("主进程名不能为空");
        return false;
    }
    return true;
}
//检查docker参数
//2021-3-18增加对deepin-wine5在64位容器的隔离
bool vekAppAddMT::checkDocerOption(){
    if(tempDockData->docker_WineVersion==nullptr){
        pObject::vekError("请先安装wine");
        return false;
    }
    if(tempDockData->docker_WineVersion.contains("deepin",Qt::CaseSensitive)&tempDockData->docker_SystemBitVersion=="win64"){
        pObject::vekError("Deepin-Wine5不支持64位容器");
        return false;
    }
    if(tempDockData->docker_Path==nullptr)
    {
        pObject::vekError("请设置wine运行容器路径");
        return false;
    }
    if(tempDockData->docker_Name==nullptr){
        pObject::vekError("请设置容器名字");
        return false;
    }
    if(tempDockData->docker_WinePath==nullptr){
        pObject::vekError("请先安装wine");
        return false;
    }
    return true;
}
//按钮事件集中处理
void vekAppAddMT::objectButton(){
    QObject *object = QObject::sender();
    QPushButton *action_obnject = qobject_cast<QPushButton *>(object);
    QWidget *qwidget = new QWidget();
    //设置游戏ico
    if(action_obnject->objectName()=="pushButton_setIco"){
        QString strIco=QFileDialog::getOpenFileName(qwidget,"选择游戏图标","","Ico Files(*.ico);;PNG Files(*.png);;JPEG Files(*.jpeg)");
        if(strIco!=nullptr){
            ui->pushButton_setIco->setIcon(QIcon(strIco));
        }else{
            ui->pushButton_setIco->setIcon(QIcon(":/res/img/vek.ico"));
        }
    }
    //设置游戏exe
    if(action_obnject->objectName()=="pushButton_SetAppExe"){
        QString exePath=QFileDialog::getOpenFileName(qwidget,"选择要添加的程序","","exe Files(*.exe)");
        if(exePath!=nullptr){
            QFileInfo fi = QFileInfo(exePath);
            if(ui->lineEdit_AppName->text()==nullptr){
                ui->lineEdit_AppName->setText(fi.baseName());
            }
            ui->lineEdit_AppInstallExe->setText(exePath);
            ui->lineEdit_workPath->setText(fi.path());
        }
    }
    //设置工作目录
    if(action_obnject->objectName()=="pushButton_workPath"){
        QString workPath=QFileDialog::getExistingDirectory(qwidget,"选择目录","",nullptr);
        if(workPath!=nullptr){
            ui->lineEdit_workPath->setText(workPath);
        }
    }
    //设置DOCK路径
    if(action_obnject->objectName()=="pushButton_SetDockPath"){
        QString dockPath=QFileDialog::getExistingDirectory(qwidget,"选择目录","",nullptr);
        if(dockPath!=nullptr){
            ui->lineEdit_RunDockPath->setText(dockPath);
        }
    }
    //保存Save
    if(action_obnject->objectName()=="pushButton_SaveDxvkConfFile"){
        QString savePath=ui->lineEdit_dxvkConfigFIle->text();
        bool vekMesgDxvkSave=pObject::vekMesg("是否把dxvk配置文件保存到"+savePath);
        if(vekMesgDxvkSave)
        {
            if(QFile(savePath).exists()){
                if(pObject::vekMesg("是否覆盖"+savePath)){
                    QFile(savePath).remove();
                }else{
                    savePath = QFileDialog::getSaveFileName(this,tr("选择保存dxvk.conf路径"),".",tr("DxvkConf Files(*.conf)"));
                }
            }
        }else{
            savePath = QFileDialog::getSaveFileName(this,tr("选择保存dxvk.conf路径"),".",tr("DxvkConf Files(*.conf)"));
        }
        if(savePath!=nullptr){
            ui->lineEdit_dxvkConfigFIle->setText(savePath);
            pObject::saveStrToFile(ui->textEdit_dxvkConfigFileData->toPlainText(),savePath);
            ui->lineEdit_dxvkConfigFIle->setText(savePath);
        }
    }
    //确定事件
    if(action_obnject->objectName()=="pushButton_Set"){
        ui->label_TipsText->setText("保存配置中请稍后!");
        if(vekAppAddObj(false)){
            emit doneAddApp(tempDockData,tempAppData);
            this->close();
        }
    }
    //初始化
    if(action_obnject->objectName()=="pushButton_initDock"){
        if(ui->comboBox_dockbit->isEnabled()){
            if(pObject::vekMesg("强制初始化容器会导致部分软件无法运行和适配请慎重!")){
                ui->label_TipsText->setText("正在初始化容器请稍后!");
                vekAppAddObj(true);
            }
        }else{
            if(pObject::vekMesg("是否解锁初始化功能限制请谨慎操作?")){
                ui->comboBox_dockbit->setEnabled(true);
                ui->comboBox_DockName->setEnabled(true);
                ui->comboBox_dockSystemVersion->setEnabled(true);
            }
        }
    }
}

bool vekAppAddMT::vekAppAddObj(bool _forceState){
    if(!vekAppConfigObj()){
        return false;
    }
    objectAppMT* vappAddObj=new objectAppMT(tempAppData,tempDockData);
    if(!vappAddObj->InitDockObj(_forceState)){
        pObject::vekError("初始化失败!");
        return false;
    }else{
        pObject::addAppDataToJson(*tempDockData,*tempAppData);
    }
    if(objType==SEETING){
        emit _upData(*tempDockData,tempAppData,objType);
    }
    delete vappAddObj;
    vappAddObj=nullptr;
    return true;
}

