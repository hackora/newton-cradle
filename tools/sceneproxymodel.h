#ifndef SCENEPROXYMODEL_H
#define SCENEPROXYMODEL_H



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
  class PointLightG;
  class Color;
}
#include <core/gmarray>

// Qt
#include <QAbstractItemModel>


// stl
#include <memory>


class SceneProxyModel : public QAbstractItemModel {
  Q_OBJECT
public:
  SceneProxyModel( std::shared_ptr<GMlibWrapper> gmlib = nullptr);



  QModelIndex                         indexFromSceneObject( GMlib::SceneObject* );

  Q_INVOKABLE virtual QVariant        getSceneProperty( const QString& name ) const;
  Q_INVOKABLE virtual bool            setSceneProperty( const QString& name, const QString& value );

  Q_INVOKABLE QVariantList            getPropertyModules( const QModelIndex& index ) const;

  Q_INVOKABLE QVariant                getProperty( const QModelIndex& index, int module, const QString& name ) const;
  QVariant                            getSceneObjectProperty( const GMlib::SceneObject& sceneobject, const QString& name ) const;
  QVariant                            getPointLightProperty( const GMlib::PointLightG& pointlight, const QString& name ) const;


  Q_INVOKABLE bool                    setProperty( const QModelIndex& index, int module, const QString& name, const QVariant& value );
  bool                                setSceneObjectProperty( GMlib::SceneObject& sceneobject, const QString& name, const QVariant& value );

  Q_INVOKABLE void                    selectSceneObject( const QModelIndex& index ) const;


  // From QAbstractItemModel
  QModelIndex                         index( int row, int column, const QModelIndex &parent = QModelIndex() ) const override;
  QModelIndex                         parent( const QModelIndex &child ) const override;
  int                                 rowCount( const QModelIndex &parent = QModelIndex() ) const override;
  int                                 columnCount( const QModelIndex &parent = QModelIndex() ) const override;
  QVariant                            data( const QModelIndex &index, int role = Qt::DisplayRole ) const override;
  Qt::ItemFlags                       flags( const QModelIndex &index ) const override;

  QHash<int,QByteArray>               roleNames() const override;

  bool                                setData(const QModelIndex &index, const QVariant &value, int role) override;




  enum class PropertyModules : int {
    SceneObject   = 0,

    Camera,
    PointLight,


    PSurf,
    PERBSSurf,
    PTorus,

    CustomModules = 100
  };
  Q_ENUM(PropertyModules)


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


  virtual QVariantList                        getCustomPropertyModules( const GMlib::SceneObject* sceneobject ) const;
  virtual QVariant                            getCustomProperty( const GMlib::SceneObject* sceneobject, int module, const QString& name ) const;
  virtual bool                                setCustomProperty( const GMlib::SceneObject* sceneobject, int module, const QString& name, const QVariant& value );


public:
  static GMlib::Color                         toGMlibColor( const QColor& color );
  static QColor                               toQColor( const GMlib::Color& color );
  Q_INVOKABLE QVariant                        createMaterial_GM();
};


#endif // SCENEPROXYMODEL_H
