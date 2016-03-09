#include "gmopenglproxymodel.h"

// gmlib
#include <gmOpenglModule>



GMOpenGLProxyModel::GMOpenGLProxyModel() {}

QModelIndex
GMOpenGLProxyModel::index(int row, int column, const QModelIndex& parent) const {

  if(!hasIndex(row,column,parent)) return QModelIndex();

  const auto& data = GMlib::GL::Texture::getData();
  if( row >= data.size() ) return QModelIndex();

  return createIndex( row, column, nullptr );
}

QModelIndex
GMOpenGLProxyModel::parent(const QModelIndex& child) const {
  Q_UNUSED(child)

  return QModelIndex();
}

int
GMOpenGLProxyModel::rowCount(const QModelIndex& parent) const {

  if( parent.column() > 0 ) return 0;

  if(!parent.isValid()) GMlib::GL::Texture::getData().size();
}

int
GMOpenGLProxyModel::columnCount(const QModelIndex& parent) const {
  Q_UNUSED(parent)

  return 1;
}

QVariant
GMOpenGLProxyModel::data(const QModelIndex& index, int role) const {

  if(!index.isValid()) return QVariant("INVALID");

  const auto& data = GMlib::GL::Texture::getData();
  auto itr = data.begin();
  for( int i = 0; i < data.size(); ++i, ++itr );

  switch(UserRoles(role)) {
    case UserRoles::Id:   return itr->id;
    case UserRoles::Name: return itr->name.c_str();

    default: return QVariant("DEFAULT");
  }
}

QHash<int, QByteArray>
GMOpenGLProxyModel::roleNames() const {

  QHash<int, QByteArray> names;
  names[int(UserRoles::Id)]   = "id";
  names[int(UserRoles::Name)] = "name";
  return names;
}
