#ifndef MYSCENEPROXYMODEL_H
#define MYSCENEPROXYMODEL_H


#include "tools/sceneproxymodel.h"


class TestTorus;

class MySceneProxyModel : public SceneProxyModel {
  Q_OBJECT
public:
  using SceneProxyModel::SceneProxyModel;

  enum class MyPropertyModules : int {
    TestTorus = int(PropertyModules::CustomModules) + 1,
  };
  Q_ENUM(MyPropertyModules)

private:

  QVariantList  getCustomPropertyModules(const GMlib::SceneObject *sceneobject) const override;
  QVariant      getCustomProperty(const GMlib::SceneObject *sceneobject, int module, const QString &name) const override;
  bool          setCustomProperty(const GMlib::SceneObject *sceneobject, int module, const QString &name, const QVariant &value) override;

};

#endif // MYSCENEPROXYMODEL_H
