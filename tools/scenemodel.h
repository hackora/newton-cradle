#ifndef SCENEMODEL_H
#define SCENEMODEL_H



// local
namespace placeholders {

  class Root{};
  class ComponentGroup{};
}
class GMlibWrapper;

// GMlib
namespace GMlib {
  class Scene;
  class SceneObject;
}
#include <core/gmarray>

// Qt
#include <QAbstractItemModel>


// stl
#include <memory>


class SceneModel : public QAbstractItemModel {
  Q_OBJECT
public:
  SceneModel( std::shared_ptr<GMlibWrapper> gmlib );



  QModelIndex               indexFromSceneObject( GMlib::SceneObject* );







  // From QAbstractItemModel
  QModelIndex               index( int row, int column, const QModelIndex &parent = QModelIndex() ) const override;
  QModelIndex               parent( const QModelIndex &child ) const override;
  int                       rowCount( const QModelIndex &parent = QModelIndex() ) const override;
  int                       columnCount( const QModelIndex &parent = QModelIndex() ) const override;
  QVariant                  data( const QModelIndex &index, int role = Qt::DisplayRole ) const override;
  Qt::ItemFlags             flags( const QModelIndex &index ) const override;

  QHash<int,QByteArray>     roleNames() const override;




public slots:
  void                      stupidForceModelUpdate();

private:
  enum class UserRoles : int {
    Identity = Qt::UserRole + 1,
    Name,
    Visible,
    MemoryAddress
  };



  std::shared_ptr<GMlibWrapper>               _gmlib;

//  mutable placeholders::Root                          _root;


  const std::shared_ptr<GMlib::Scene>&        scene() const;

  QModelIndex                                 findQmiFromSo( const GMlib::Array<GMlib::SceneObject*>& children,
                                                             GMlib::SceneObject* obj_to_find ) const;
};

#endif // SCENEMODEL_H
