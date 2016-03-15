#include "mysceneproxymodel.h"

#include "testtorus.h"

#include <QVector3D>

QVariantList
MySceneProxyModel::getCustomPropertyModules(const GMlib::SceneObject* sceneobject) const {

  QVariantList modules;

  if(dynamic_cast<const TestTorus*>(sceneobject)) modules << int(MyPropertyModules::TestTorus);

  return modules;
}

QVariant
MySceneProxyModel::getCustomProperty(const GMlib::SceneObject* sceneobject, int module, const QString& name) const {

  auto obj = dynamic_cast<const TestTorus*>(sceneobject);

  if(obj and MyPropertyModules(module) == MyPropertyModules::TestTorus) {

    if(     name == "rotation_speed") {

      auto rs = obj->getRotationSpeed();
      return rs.getDeg();
    }
    else if(name == "rotation_axel") {

      auto ra = obj->getRotationAxel();
      QVector3D axel;
      axel.setX(ra(0));
      axel.setY(ra(1));
      axel.setZ(ra(2));
      return axel;
    }
  }

  return QVariant();
}

bool
MySceneProxyModel::setCustomProperty(const GMlib::SceneObject* sceneobject, int module, const QString& name, const QVariant& value) {

  return false;
}
