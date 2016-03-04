#ifndef SCENEMODEL_H
#define SCENEMODEL_H



// local
class GMlibWrapper;

// GMlib
namespace GMlib {
  class Scene;
}

// Qt
#include <QAbstractItemModel>


// stl
#include <memory>


class SceneModel : public QAbstractItemModel {
  Q_OBJECT
public:
  SceneModel( std::shared_ptr<GMlibWrapper> gmlib );

  // From QAbstractItemModel
  QModelIndex               index( int row, int column, const QModelIndex &parent = QModelIndex() ) const override;
  QModelIndex               parent( const QModelIndex &child ) const override;
  int                       rowCount( const QModelIndex &parent = QModelIndex() ) const override;
  int                       columnCount( const QModelIndex &parent = QModelIndex() ) const override;
  QVariant                  data( const QModelIndex &index, int role = Qt::DisplayRole ) const override;
  Qt::ItemFlags             flags( const QModelIndex &index ) const override;

  QHash<int,QByteArray>     roleNames() const override;

private:
  enum class UserRoles : int {
    Name = Qt::UserRole,
    Identity,
    Pointer
  };



  std::shared_ptr<GMlibWrapper>         _gmlib;

  const std::shared_ptr<GMlib::Scene>&        scene() const;
};

#endif // SCENEMODEL_H
