﻿#include "objectJson.h"

objectJson::objectJson()
{

}
objectJson::~objectJson()
{

}
//增加游戏
json objectJson::DataSerialize(json jsonData,const BaseLocalData _baseLocalData){
    //序列化容器列表
    //ax.first->容器名
    for(auto ax:g_vekLocalData.dockerVec){
        //bx.first->游戏CID
        for(auto bx:ax.second){
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(gameCID)]=bx.second.gameCID.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(gameName)]=bx.second.gameName.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(gameIco)]=bx.second.gameIco.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(gameExe)]=bx.second.gameExe.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(winePath)]=bx.second.winePath.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(wineVersion)]=bx.second.wineVersion.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(gameOtherAgrs)]=bx.second.gameOtherAgrs.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(dockSystemVersion)]=bx.second.dockSystemVersion.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(dxvkHUD)]=bx.second.dxvkHUD;
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(dxvkVerson)]=bx.second.dxvkVerson.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(dxvkConfigFile)]=bx.second.dxvkConfigFile.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(dockPath)]=bx.second.dockPath.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(dockName)]=bx.second.dockName.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(workPath)]=bx.second.workPath.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(mainPrcoName)]=bx.second.mainPrcoName.toStdString();
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(taskLog)]=bx.second.taskLog;
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(dxvkState)]=bx.second.dxvkState;
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(taskMemoryOptimization)]=bx.second.taskMemoryOptimization;
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(taskMemorySharing)]=bx.second.taskMemorySharing;
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(taskRealTimePriority)]=bx.second.taskRealTimePriority;
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(defaultFonts)]=bx.second.defaultFonts;
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(monoState)]=bx.second.monoState;
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(geckoState)]=bx.second.geckoState;
            jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(dxvkConfigFileState)]=bx.second.dxvkConfigFileState;
            if(!bx.second.dockEnv.empty()){
                for(auto&[fa,yz]:bx.second.dockEnv){
                    jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(dockEnv)][fa.toStdString()]=yz.toStdString();
                }
            }else{
                jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(dockEnv)]={};
            }
            if(!bx.second.dockLibs.empty()){
                for(auto&ya:bx.second.dockLibs){
                    jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(dockLibs)].push_back(ya.toStdString());
                }
            }else{
                jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(dockLibs)]={};
            }
            if(!bx.second.dockRegs.empty()){
                int i=-1;
                for(auto a:bx.second.dockRegs){
                    i+=1;
                    jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(dockRegs)][i][toStr(rPath)]=a.rPath.toStdString();
                    jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(dockRegs)][i][toStr(rKey)]=a.rKey.toStdString();
                    jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(dockRegs)][i][toStr(rTValue)]=a.rTValue.toStdString();
                    jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(dockRegs)][i][toStr(rValue)]=a.rValue.toStdString();
                }
            }else{
                jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(dockRegs)]={};
            }
            if(!bx.second.attachProc.empty()){
                for(auto rs:bx.second.attachProc){
                    jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(attachProc)].push_back(rs.toStdString());
                }
            }else{
                jsonData["Docker"][ax.first.toStdString()][bx.second.gameCID.toStdString()][toStr(attachProc)]={};
            }
        }
    }
    //禁止修改
    for(auto &k : _baseLocalData.wineVec){
        jsonData["Wine"][k.second.WineInstallName.toStdString()][toStr(WineInstallName)]=k.second.WineInstallName.toStdString();
        jsonData["Wine"][k.second.WineInstallName.toStdString()][toStr(wineInstallPath)]=k.second.wineInstallPath.toStdString();
        jsonData["Wine"][k.second.WineInstallName.toStdString()][toStr(wineInstallVer)]=k.second.wineInstallVer.toStdString();
        jsonData["Wine"][k.second.WineInstallName.toStdString()][toStr(wineInstallUrl)]=k.second.wineInstallUrl.toStdString();
        jsonData["Wine"][k.second.WineInstallName.toStdString()][toStr(wineInstallSrc)]=k.second.wineInstallSrc.toStdString();
        jsonData["Wine"][k.second.WineInstallName.toStdString()][toStr(wineInstallMono)]=k.second.wineInstallMono.toStdString();
        jsonData["Wine"][k.second.WineInstallName.toStdString()][toStr(wineInstallGeckoX86)]=k.second.wineInstallGeckoX86.toStdString();
        jsonData["Wine"][k.second.WineInstallName.toStdString()][toStr(wineInstallGeckoX86_64)]=k.second.wineInstallGeckoX86_64.toStdString();
        for(auto dx:k.second.wineInstallDxvk){
            jsonData["Wine"][k.second.WineInstallName.toStdString()][toStr(wineInstallDxvk)].push_back(dx.toStdString());
        }
    }
    for(auto &[x,y]: _baseLocalData.gameScrSource){
        jsonData["GameScrSource"][x.toStdString()]=y.toStdString();
        for(auto &[a,b]: _baseLocalData.gameJsonList){
            for(auto&[u,i]:b){
                jsonData["GameJsonList"][x.toStdString()][u.toStdString()]=i.toStdString();
            }
        }
    }
    /* x a 源名字
     *
     */
    for(auto &[x,y]: _baseLocalData.wineSource){
        jsonData["WineScrSource"][x.toStdString()]=y.toStdString();
        for(auto&[a,b]:_baseLocalData.wineJsonList){
            if(a==x){
                for(auto& [d,e]:b){
                    jsonData["WineJsonList"][x.toStdString()][e.wineName.toStdString()][toStr(wineName)]=e.wineName.toStdString();
                    jsonData["WineJsonList"][x.toStdString()][e.wineName.toStdString()][toStr(wineVersion)]=e.wineVersion.toStdString();
                    jsonData["WineJsonList"][x.toStdString()][e.wineName.toStdString()][toStr(wineGit)]=e.wineGit.toStdString();
                    jsonData["WineJsonList"][x.toStdString()][e.wineName.toStdString()][toStr(Mono)]=e.Mono.toStdString();
                    jsonData["WineJsonList"][x.toStdString()][e.wineName.toStdString()][toStr(GeckoX86)]=e.GeckoX86.toStdString();
                    jsonData["WineJsonList"][x.toStdString()][e.wineName.toStdString()][toStr(GeckoX86_64)]=e.GeckoX86_64.toStdString();
                    for(auto dy:e.wineDxvk){
                        jsonData["WineJsonList"][x.toStdString()][e.wineName.toStdString()][toStr(wineDxvk)].push_back(dy.toStdString());
                    }
                }
            }
        }
    }
    return jsonData;
}

//反序列化到结构
bool objectJson::unDataSerializeLocalData(){
    //解析srt为json
    try
    {
        QString jsonPath=QDir::currentPath()+"/data.json";
        QFile file(jsonPath);
        if(!file.exists())
        {
            return false;
        }
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        string temp = file.readAll().toStdString();
        file.close();
        json j3=json::parse(temp);
        if(j3==nullptr){

            return false;
        }
        for (auto& [k, v] : j3.items())
        { 
            BaseWineData _base_wine_data={};
            //反序列化容器表内数据
            if(k=="Docker"){
                //ax->容器名 bx->容器下的游戏列表
                for(auto [ax,bx]:v.items()){
                    //cx->游戏CID bx->游戏数据
                    for(auto [cx,dx]:bx.items()){
                        BaseGameData _base_game_data={};
                        _base_game_data.gameCID=QString::fromStdString(dx.at("gameCID"));
                        _base_game_data.gameName=QString::fromStdString(dx.at("gameName"));
                        _base_game_data.gameExe=QString::fromStdString(dx.at("gameExe"));
                        _base_game_data.gameIco=QString::fromStdString(dx.at("gameIco"));
                        _base_game_data.winePath=QString::fromStdString(dx.at("winePath"));
                        _base_game_data.wineVersion=QString::fromStdString(dx.at("wineVersion"));
                        _base_game_data.gameOtherAgrs=QString::fromStdString(dx.at("gameOtherAgrs"));
                        _base_game_data.dockPath=QString::fromStdString(dx.at("dockPath"));
                        _base_game_data.dxvkVerson=QString::fromStdString(dx.at("dxvkVerson"));
                        _base_game_data.dockName=QString::fromStdString(dx.at("dockName"));
                        _base_game_data.dockSystemVersion=QString::fromStdString(dx.at("dockSystemVersion"));
                        _base_game_data.workPath=QString::fromStdString(dx.at("workPath"));
                        _base_game_data.dxvkConfigFile=QString::fromStdString(dx.at("dxvkConfigFile"));
                        _base_game_data.mainPrcoName=QString::fromStdString(dx.at("mainPrcoName"));
                        _base_game_data.dxvkState=dx.at("dxvkState");
                        _base_game_data.dxvkHUD=dx.at("dxvkHUD");
                        _base_game_data.taskLog=dx.at("taskLog");
                        _base_game_data.taskMemoryOptimization=dx.at("taskMemoryOptimization");
                        _base_game_data.taskMemorySharing=dx.at("taskMemorySharing");
                        _base_game_data.taskRealTimePriority=dx.at("taskRealTimePriority");
                        _base_game_data.defaultFonts=dx.at("defaultFonts");
                        _base_game_data.monoState=dx.at("monoState");
                        _base_game_data.geckoState=dx.at("geckoState");
                        _base_game_data.dxvkConfigFileState=dx.at("dxvkConfigFileState");
                        _base_game_data.attachProc.clear();
                        if(dx.at("attachProc")!=NULL){
                            for(auto idx:dx.at("attachProc")){
                                _base_game_data.attachProc.push_back(QString::fromStdString(idx));
                            }
                        }else{
                            _base_game_data.attachProc={};
                        }
                        _base_game_data.dockEnv.clear();
                        if(dx.at("dockEnv")!=NULL){
                            for(auto&[vx,vy]:dx.at("dockEnv").items()){
                                _base_game_data.dockEnv.insert(pair<QString,QString>(QString::fromStdString(vx),QString::fromStdString(vy)));
                            }
                        }else{
                            _base_game_data.dockEnv={};
                        }
                        _base_game_data.dockRegs.clear();
                        if(dx.at("dockRegs")!=NULL){
                            for(auto&wy:dx.at("dockRegs")){
                                BaseDockRegs _rbaseRegs;
                                _rbaseRegs.rPath=QString::fromStdString(wy.at("rPath"));
                                _rbaseRegs.rKey=QString::fromStdString(wy.at("rKey"));
                                _rbaseRegs.rTValue=QString::fromStdString(wy.at("rTValue"));
                                _rbaseRegs.rValue=QString::fromStdString(wy.at("rValue"));
                                _base_game_data.dockRegs.push_back(_rbaseRegs);
                            }
                        }
                     g_vekLocalData.dockerVec[QString::fromStdString(ax)].insert(pair<QString,BaseGameData>(_base_game_data.gameCID,_base_game_data));
                    }
                }
            //禁止修改
            }else if(k=="Wine"){
                for(auto& [x,y]: v.items()){
                    _base_wine_data.WineInstallName=QString::fromStdString(y.at("WineInstallName"));
                    _base_wine_data.wineInstallPath=QString::fromStdString(y.at("wineInstallPath"));
                    _base_wine_data.wineInstallVer=QString::fromStdString(y.at("wineInstallVer"));
                    _base_wine_data.wineInstallUrl=QString::fromStdString(y.at("wineInstallUrl"));
                    _base_wine_data.wineInstallSrc=QString::fromStdString(y.at("wineInstallSrc"));
                    _base_wine_data.wineInstallMono=QString::fromStdString(y.at("wineInstallMono"));
                    _base_wine_data.wineInstallGeckoX86=QString::fromStdString(y.at("wineInstallGeckoX86"));
                    _base_wine_data.wineInstallGeckoX86_64=QString::fromStdString(y.at("wineInstallGeckoX86_64"));
                    _base_wine_data.wineInstallDxvk.clear();
                    for(auto yz:y.at("wineInstallDxvk")){
                        _base_wine_data.wineInstallDxvk.push_back(QString::fromStdString(yz));
                    }
                    g_vekLocalData.wineVec.insert(pair<QString,BaseWineData>(_base_wine_data.WineInstallName,_base_wine_data));
                }
            }else if(k=="GameScrSource"){
                for(auto &[b, c] :v.items())
                {
                    g_vekLocalData.gameScrSource.insert(pair<QString,QString>(QString::fromStdString(b),QString::fromStdString(c)));
                    for (auto& [d, j] : j3.items())
                    {
                        if(d=="GameJsonList"){
                            for(auto&[u,i]:j.items()){
                                if(u==b){
                                    for(auto&[w,o]:i.items()){
                                        g_vekLocalData.gameJsonList[QString::fromStdString(u)].insert(pair<QString,QString>(QString::fromStdString(w),QString::fromStdString(o)));
                                    }
                                }
                            }
                        }
                        continue;
                    }
                }
            }
            else if(k=="WineScrSource"){
                /* b u 源名字
                 * i 源下wine版本
                 * kj 版本信息
                 * ix dxvk版本
                */
                for(auto &[b, c] :v.items())
                {
                    g_vekLocalData.wineSource.insert(pair<QString,QString>(QString::fromStdString(b),QString::fromStdString(c)));
                    for (auto& [d, j] : j3.items())
                    {
                        if(d=="WineJsonList"){
                            for(auto&[u,i]:j.items())
                            {
                                if(u==b)
                                {
                                    for(auto& kj:i)
                                    {
                                        //qDebug()<<QString::fromStdString(kj);
                                        g_vekLocalData.wineJsonList[QString::fromStdString(u)][QString::fromStdString(kj.at("wineName"))].wineName=QString::fromStdString(kj.at("wineName"));
                                        g_vekLocalData.wineJsonList[QString::fromStdString(u)][QString::fromStdString(kj.at("wineName"))].wineVersion=QString::fromStdString(kj.at("wineVersion"));
                                        g_vekLocalData.wineJsonList[QString::fromStdString(u)][QString::fromStdString(kj.at("wineName"))].wineGit=QString::fromStdString(kj.at("wineGit"));
                                        g_vekLocalData.wineJsonList[QString::fromStdString(u)][QString::fromStdString(kj.at("wineName"))].Mono=QString::fromStdString(kj.at("Mono"));
                                        g_vekLocalData.wineJsonList[QString::fromStdString(u)][QString::fromStdString(kj.at("wineName"))].GeckoX86=QString::fromStdString(kj.at("GeckoX86"));
                                        g_vekLocalData.wineJsonList[QString::fromStdString(u)][QString::fromStdString(kj.at("wineName"))].GeckoX86_64=QString::fromStdString(kj.at("GeckoX86_64"));
                                        g_vekLocalData.wineJsonList[QString::fromStdString(u)][QString::fromStdString(kj.at("wineName"))].wineDxvk.clear();
                                        for(auto ix:kj.at("wineDxvk"))
                                        {
                                            g_vekLocalData.wineJsonList[QString::fromStdString(u)][QString::fromStdString(kj.at("wineName"))].wineDxvk.push_back(QString::fromStdString(ix));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return true;
    }
    catch (nullptr_t)
    {
        return false;
    }

}

//脚本反序列化
BaseAutoSetJson* objectJson::unDataSerializeScriptData(BaseAutoSetJson* _baseAutoSetJson,QString autoJsonData){
    try {
        json js3=json::parse(autoJsonData.toStdString());
        for(auto&[k,j]:js3.items()){
            if(QString::fromStdString(k)=="Option"){
                for(auto&[iu,zu]:j.items()){
                    _baseAutoSetJson->Option.insert(pair<QString,QString>(QString::fromStdString(iu),QString::fromStdString(zu)));
                }
            }
            if(QString::fromStdString(k)=="AttachProc"){
                for(auto&zu:j.items()){
                    _baseAutoSetJson->AttachProc.push_back(QString::fromStdString(zu.value()));
                }
            }
            if(QString::fromStdString(k)=="Env"){
                for(auto&[iu,zu]:j.items()){
                    _baseAutoSetJson->Env.insert(pair<QString,QString>(QString::fromStdString(iu),QString::fromStdString(zu)));
                }
            }
            if(QString::fromStdString(k)=="Libs"){
                for(auto& d:j.items()){
                    _baseAutoSetJson->Libs.push_back(QString::fromStdString(d.value()));
                }
            }
            if(QString::fromStdString(k)=="Dxvk"){
                for(auto&[iy,zy]:j.items()){
                    _baseAutoSetJson->Dxvk.insert(pair<QString,QString>(QString::fromStdString(iy),QString::fromStdString(zy)));
                }
            }
            if(QString::fromStdString(k)=="Regs"){
                for(auto ad:j.items()){
                    BaseDockRegs rbaseRegs;
                    rbaseRegs.rPath=QString::fromStdString(ad.value().at("rPath"));
                    rbaseRegs.rKey=QString::fromStdString(ad.value().at("rKey"));
                    rbaseRegs.rTValue=QString::fromStdString(ad.value().at("rTValue"));
                    rbaseRegs.rValue=QString::fromStdString(ad.value().at("rValue"));
                    _baseAutoSetJson->Regs.push_back(rbaseRegs);
                }

            }
            if(QString::fromStdString(k)=="Args"){
                _baseAutoSetJson->Args=QString::fromStdString(j);
            }
        }
    } catch (nullptr_t) {
        _baseAutoSetJson=nullptr;
    }
    return _baseAutoSetJson;
}
//反序列化列表
bool objectJson::unSerializeLocalWineGame(QString key,QString urlData,UNJSONTYPE jsonType){
    json jdata=json::parse(urlData.toStdString());
    try {
        switch (jsonType) {
        case unJsonWineList:
            for(auto &[x, y] :jdata.items())
            {
                g_vekLocalData.wineJsonList[key][QString::fromStdString(y.at("wineName"))].wineName=QString::fromStdString(y.at("wineName"));
                g_vekLocalData.wineJsonList[key][QString::fromStdString(y.at("wineName"))].wineVersion=QString::fromStdString(y.at("wineVersion"));
                g_vekLocalData.wineJsonList[key][QString::fromStdString(y.at("wineName"))].wineGit=QString::fromStdString(y.at("wineGit"));
                g_vekLocalData.wineJsonList[key][QString::fromStdString(y.at("wineName"))].Mono=QString::fromStdString(y.at("Mono"));
                g_vekLocalData.wineJsonList[key][QString::fromStdString(y.at("wineName"))].GeckoX86=QString::fromStdString(y.at("GeckoX86"));
                g_vekLocalData.wineJsonList[key][QString::fromStdString(y.at("wineName"))].GeckoX86_64=QString::fromStdString(y.at("GeckoX86_64"));
                g_vekLocalData.wineJsonList[key][QString::fromStdString(y.at("wineName"))].wineDxvk.clear();
                for(auto xz:y.at("wineDxvk")){
                    g_vekLocalData.wineJsonList[key][QString::fromStdString(y.at("wineName"))].wineDxvk.push_back(QString::fromStdString(xz));
                }
            }
            break;
        case unJsonGameList:
            for(auto &[x, y] :jdata.items())
            {
                g_vekLocalData.gameJsonList[key][QString::fromStdString(x)]=QString::fromStdString(y);
            }
            break;
        }

    } catch (nullptr_t) {
        return false;
    }
    return true;
}
//写入文件
void objectJson::WriteJsonToFile(QString filePath,json jsonData){
    ofstream out;
    out.open(filePath.toStdString(),fstream::in | fstream::out | fstream::trunc);
    out<<jsonData;
    cout<<"Json Output:"<<jsonData<<endl;
    out.close();
}

//写入全局文件
void objectJson::WriteLocalData(){
    QString localDataFilePath=QDir::currentPath()+"/data.json";
    json jsonData=nullptr;
    jsonData=DataSerialize(jsonData,g_vekLocalData);
    WriteJsonToFile(localDataFilePath,jsonData);
}
//删除游戏节点
void objectJson::deleteGameNodeData(QString nGameCID){
    for(auto& h:g_vekLocalData.dockerVec){
        for(auto &w:h.second){
            if(w.second.gameCID==nGameCID){
                h.second.erase(nGameCID);
                break;
            }
        }
    }
    WriteLocalData();
}
//删除Wine节点
void objectJson::deleteWineNodeData(QString nWineName){
    for(auto &h : g_vekLocalData.wineVec){
        if(h.first==nWineName){
            g_vekLocalData.wineVec.erase(nWineName);
            break;
        }
    }
    WriteLocalData();
}
//更新或者增加Game节点
void objectJson::updateGameNodeData(QString dockName,BaseGameData _base_game_data){
    if(_base_game_data.gameCID!=nullptr){
        deleteGameNodeData(_base_game_data.gameCID);
    }
    g_vekLocalData.dockerVec[dockName].insert(pair<QString,BaseGameData>(_base_game_data.gameCID,_base_game_data));
    WriteLocalData();
}
//更新Wine节点
void objectJson::updateWineNodeData(BaseWineData _base_wine_data){
    if(_base_wine_data.WineInstallName!=nullptr){
        deleteWineNodeData(_base_wine_data.WineInstallName);
    }
    g_vekLocalData.wineVec.insert(pair<QString,BaseWineData>(_base_wine_data.WineInstallName,_base_wine_data));
    WriteLocalData();
}
//生成CID
QString objectJson::GetRandomCID()
{
    int max = 32;
    QString tmp = QString("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWZYZ");
    QString str;
    QTime t;
    t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    for(int i=0;i<max;i++) {
        int ir = qrand()%tmp.length();
        str[i] = tmp.at(ir);
    }
    qDebug()<<str;
    return str;
}
