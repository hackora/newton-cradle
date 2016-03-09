#include "scenemodel.h"

#include "../application/gmlibwrapper.h"

// gmlib
#include <gmSceneModule>

// qt
#include <QDebug>






SceneModel::SceneModel(std::shared_ptr<GMlibWrapper> gmlib)
  : _gmlib{gmlib}
{}

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

  // No index evaluates to invalid index
  if( !hasIndex(row, column, parent) )
    return QModelIndex();

  // Create index for all child elements of root
  if( !parent.isValid() and row < scene()->getSize() )
      return createIndex( row, column, scene()->operator[](row) );

  // Create index for all child elements of a child
  auto parent_so = static_cast<GMlib::SceneObject*>(parent.internalPointer());
  if(row < parent_so->getChildren().size())
    return createIndex( row, column, parent_so->getChildren()(row) );

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

  auto parent_so = child->getParent();
  if(!parent_so) return QModelIndex();

  return createIndex(row,0,parent_so);
}

int
SceneModel::rowCount(const QModelIndex& parent) const {

  // Only first column can have children (one-dimensional tree)
  if( parent.column() > 0 ) return 0;

  // If no parent, interpret as root scene item
  if( !parent.isValid() )  return scene()->getSize();

  auto parent_so = static_cast<GMlib::SceneObject*>(parent.internalPointer());
  return parent_so->getChildren().size();
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
    case UserRoles::Identity:       return sceneobject->getIdentity().c_str();
    case UserRoles::Name:           return sceneobject->getName();
    case UserRoles::Visible:        return sceneobject->isVisible();
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
  role_names[int(UserRoles::Identity)]      = "so_identity";
  role_names[int(UserRoles::Name)]          = "so_name";
  role_names[int(UserRoles::Visible)]       = "so_visible";
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

