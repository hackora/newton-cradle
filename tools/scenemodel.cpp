#include "scenemodel.h"

#include "../application/gmlibwrapper.h"

// gmlib
#include <gmSceneModule>

// qt
#include <QDebug>



namespace priv {

  class PlaceHolder {};

  class SceneModelRoot {};







}





SceneModel::SceneModel(std::shared_ptr<GMlibWrapper> gmlib)
  : _gmlib{gmlib}, _root{std::make_shared<priv::SceneModelRoot>()} {}

QModelIndex SceneModel::indexFromSceneObject(GMlib::SceneObject* so_to_find ) {

  for( int row = 0; row < scene()->getSize(); ++row ) {

    auto so = scene()->operator[](row);
    if( so == so_to_find ) return createIndex(row,0,so_to_find);

    return findQmiFromSo( so->getChildren(), so_to_find );
  }

  return QModelIndex();


}

QModelIndex
SceneModel::index(int row, int column, const QModelIndex& parent) const {

//  qDebug() << "Index on (" << row << "," << column << ") p -> " << parent.internalPointer();

  if( !hasIndex(row, column, parent) )  {

    auto qmi = QModelIndex();
//    qDebug() << "    " << qmi;
    return qmi;
  }

  if( !parent.isValid() and row == 0 and column == 0) {

    auto qmi = createIndex(0, 0, _root.get());
//    qDebug() << "    " << qmi;
    return qmi;
  }

  auto parent_so = static_cast<GMlib::SceneObject*>(!parent.isValid() ? nullptr : parent.internalPointer());
  if( parent.internalPointer() == _root.get() and row < scene()->getSize() ) {

    auto qmi = createIndex( row, column, scene()->operator[](row) );
//    qDebug() << "    " << qmi;
    return  qmi;
  }
  else if(parent_so and row < parent_so->getChildren().size()) {

    auto qmi = createIndex( row, column, parent_so->getChildren()(row) );
//    qDebug() << "    " << qmi;
    return qmi;
  }
  else {

    auto qmi = QModelIndex();
//    qDebug() << "    " << qmi;
    return qmi;
  }


//  auto parent_so = static_cast<GMlib::SceneObject*>(!parent.isValid() ? nullptr : parent.internalPointer());
//  if( !parent_so and row < scene()->getSize() )
//    return createIndex(row,column, scene()->operator[](row));
//  else if( parent_so and row < parent_so->getChildren().size() )
//    return createIndex(row,column, parent_so->getChildren()(row));
//  else
//    return QModelIndex();
}

QModelIndex
SceneModel::parent(const QModelIndex& index) const {

//  qDebug() << "Parent for index(" << index.internalPointer() << ") on (" << index.row() << "," << index.column() << ")";

  // If invalid, return empty QModelIndex (which evaluates to top-level)
  if(!index.isValid())  return QModelIndex();

  // check if index is root
  if( index.internalPointer() == _root.get()) return QModelIndex();

  auto child = static_cast<GMlib::SceneObject*>(index.internalPointer());
  auto parent = child->getParent();

  // If no parent, return empty QModelIndex (which evaluates to top-level)
//  if(!parent) return QModelIndex();
  if(!parent) return createIndex(0,0,_root.get());

  // Find child index
  const auto& pchildren = parent->getChildren();
  int row;
  for( row = 0; row < pchildren.size() or pchildren(row) == child; ++row );
  createIndex(row,0,child->getParent());
}

int
SceneModel::rowCount(const QModelIndex& parent) const {

//  qDebug() << "Row count for index(" << parent.internalPointer() << ") on (" << parent.row() << "," << parent.column() << ")";

  // Only first column can have children (one-dimensional tree)
  if( parent.column() > 0 ) {
//    qDebug() << "    " << 0;
    return 0;
  }

  // If no parent, interpret as root scene item
  if( !parent.isValid() ) {
//    qDebug() << "    " << 1;
    return 1;
  }

  if( parent.internalPointer() == _root.get() ) {
//    qDebug() << "    " << scene()->getSize();
    return scene()->getSize();
  }

  auto parent_so = static_cast<GMlib::SceneObject*>(!parent.isValid() ? nullptr : parent.internalPointer());
  if(!parent_so) return 0;

  return parent_so->getChildren().size();

//  if( scene()->getSize();

//  // else return number of children
//  auto parent_so = static_cast<GMlib::SceneObject*>(!parent.isValid() ? nullptr : parent.internalPointer());
//  if(parent_so) return parent_so->getChildren().size();
//  else scene()->getSize();
}

int
SceneModel::columnCount(const QModelIndex& parent) const {

  return 1;
}

QVariant
SceneModel::data(const QModelIndex& index, int role) const {

//  qDebug() << "data for index ("<< index.isValid() << ") on ("<< index.row() << "," << index.column() << ")";

  if( !index.isValid() )         return QVariant("INVALID");

  if( index.internalPointer() == _root.get() ) {
    if( UserRoles(role) == UserRoles::Identity ) return QVariant("Scene");
    else                              return QVariant();
  }



//  qDebug() << "internal ptr: " << qulonglong(index.internalPointer());
//  qDebug() << "internal id:  " << index.internalId();

  auto sceneobject = static_cast<GMlib::SceneObject*>(index.internalPointer());

  switch(UserRoles(role)) {
    case UserRoles::Name:           return sceneobject->getName();
    case UserRoles::Identity:       return sceneobject->getIdentity().c_str();
    case UserRoles::Visible:        return sceneobject->isVisible();
    case UserRoles::Selected:       return sceneobject->isSelected();
    case UserRoles::MemoryAddress:  return qulonglong(sceneobject);
    default:                        return QVariant("DEFAULT");
  }

}

Qt::ItemFlags
SceneModel::flags(const QModelIndex& index) const {

  if(!index.isValid()) return Qt::NoItemFlags;

  return QAbstractItemModel::flags(index);
}

QHash<int, QByteArray> SceneModel::roleNames() const {

  QHash<int, QByteArray> role_names;
  role_names[int(UserRoles::Name)]          = "so_name";
  role_names[int(UserRoles::Identity)]      = "so_identity";
  role_names[int(UserRoles::Visible)]       = "so_visible";
  role_names[int(UserRoles::Selected)]      = "so_selected";
  role_names[int(UserRoles::MemoryAddress)] = "so_memory_address";

  return role_names;
}

void SceneModel::stupidForceModelUpdate() {

  beginResetModel(); {
    // This is what happens
  }
  endResetModel();
}

const std::shared_ptr<GMlib::Scene>&
SceneModel::scene() const {

  return _gmlib->scene();
}

QModelIndex
SceneModel::findQmiFromSo(const GMlib::Array<GMlib::SceneObject*>& children, GMlib::SceneObject* obj_to_find) const {

  for( int row = 0; row < children.size(); ++row ) {

    auto so = children(row);
    if(so == obj_to_find) return createIndex(row,0,obj_to_find);

    return findQmiFromSo(so->getChildren(),obj_to_find);
  }

  return QModelIndex();
}

