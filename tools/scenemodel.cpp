#include "scenemodel.h"

#include "../application/gmlibwrapper.h"

// gmlib
#include <gmSceneModule>

// qt
#include <QDebug>

SceneModel::SceneModel(std::shared_ptr<GMlibWrapper> gmlib) : _gmlib{gmlib} {}

QModelIndex
SceneModel::index(int row, int column, const QModelIndex& parent) const {

  if( !hasIndex(row, column, parent) ) return QModelIndex();

  auto parent_so = static_cast<GMlib::SceneObject*>(!parent.isValid() ? nullptr : parent.internalPointer());
  if( !parent_so and row < scene()->getSize() )
    return createIndex(row,column, scene()->operator[](row));
  else if( parent_so and row < parent_so->getChildren().size() )
    return createIndex(row,column, parent_so->getChildren()(row));
  else
    return QModelIndex();
}

QModelIndex
SceneModel::parent(const QModelIndex& index) const {

  // If invalid, return empty QModelIndex (which evaluates to top-level)
  if(!index.isValid())  return QModelIndex();

  auto child = static_cast<GMlib::SceneObject*>(index.internalPointer());
  auto parent = child->getParent();

  // If no parent, return empty QModelIndex (which evaluates to top-level)
  if(!parent) return QModelIndex();

  // Find child index
  const auto& pchildren = parent->getChildren();
  int row;
  for( row = 0; row < pchildren.size() or pchildren(row) == child; ++row );
  createIndex(row,0,child->getParent());
}

int
SceneModel::rowCount(const QModelIndex& parent) const {

  // Only first column can have children (one-dimensional tree)
  if( parent.column() > 0 ) return 0;

  // If no parent, interpret as root scene item
  if( !parent.isValid() )   return scene()->getSize();

  // else return number of children
  auto parent_so = static_cast<GMlib::SceneObject*>(!parent.isValid() ? nullptr : parent.internalPointer());
  if(parent_so) return parent_so->getChildren().size();
  else scene()->getSize();
}

int
SceneModel::columnCount(const QModelIndex& parent) const {

  return 1;
}

QVariant
SceneModel::data(const QModelIndex& index, int role) const {

  if( !index.isValid() )         return QVariant("INVALID");

  auto sceneobject = static_cast<GMlib::SceneObject*>(index.internalPointer());

  switch(UserRoles(role)) {
    case UserRoles::Name:     return sceneobject->getName();
    case UserRoles::Identity: return sceneobject->getIdentity().c_str();
    case UserRoles::Pointer:  return qulonglong(sceneobject);
    default:                  return QVariant("DEFAULT");
  }

}

Qt::ItemFlags
SceneModel::flags(const QModelIndex& index) const {

  if(!index.isValid()) return Qt::NoItemFlags;

  return QAbstractItemModel::flags(index);
}

QHash<int, QByteArray> SceneModel::roleNames() const {

  QHash<int, QByteArray> role_names;
  role_names[int(UserRoles::Name)]     = "name";
  role_names[int(UserRoles::Identity)] = "identity";
  role_names[int(UserRoles::Pointer)]  = "pointer";

  return role_names;
}

const std::shared_ptr<GMlib::Scene>&
SceneModel::scene() const {

  return _gmlib->scene();
}

