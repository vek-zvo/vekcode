#include "vekATJsonModel.h"

vekATJsonModel::vekATJsonModel(QObject *parent) : QAbstractListModel(parent)
{

}
vekATJsonModel::~vekATJsonModel(){

}
QVariant vekATJsonModel::data( const QModelIndex & index, int role ) const
{
    if (index.row() > m_ItemDataVec.size())
    {
        return QVariant();
    }
    else
    {
       switch (role)
       {
       case Qt::DisplayRole:
           {
               return m_ItemDataVec[index.row()]->appName;
           }
        break;
       case Qt::DecorationRole:
           {
               return QIcon(m_ItemDataVec[index.row()]->appIco);
           }
           break;
       case Qt::SizeHintRole:
           {
               return QSize(127,100);

           }
       }
    }
    return QVariant();
}



int vekATJsonModel::rowCount( const QModelIndex & parent ) const
{
    UNUSED(parent);
    return m_ItemDataVec.size();
}
