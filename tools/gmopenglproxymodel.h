#ifndef GMOPENGLPROXYMODEL_H
#define GMOPENGLPROXYMODEL_H

// Qt
#include <QAbstractItemModel>

namespace placeholders {

  namespace GL {

    struct ShadersAndPrograms {};
    struct Shaders {};
    struct Shader{};
    struct Programs {};
    struct Program{};

    struct BufferObjects {};
    struct BOs {};
    struct BO {};
    struct RBOs {};
    struct RBO {};
    struct FBOs {};
    struct FBO {};

    struct Textures {};
    struct Texture {};
  }
}


class GMOpenGLProxyModel : public QAbstractItemModel {
  Q_OBJECT
public:
  GMOpenGLProxyModel();


  // From QAbstractItemModel
  QModelIndex             index(int row, int column, const QModelIndex &parent) const override;
  QModelIndex             parent(const QModelIndex &child) const override;
  int                     rowCount(const QModelIndex &parent) const override;
  int                     columnCount(const QModelIndex &parent) const override;
  QVariant                data(const QModelIndex &index, int role) const override;

  QHash<int,QByteArray>   roleNames() const override;


private:
  enum class UserRoles : int {
    Id = Qt::UserRole + 1,
    Name,
    DisplayName
  };


  mutable placeholders::GL::ShadersAndPrograms    _shaders_and_programs;
  mutable placeholders::GL::Shaders               _shaders;
  mutable placeholders::GL::Shader                _shader;
  mutable placeholders::GL::Programs              _programs;
  mutable placeholders::GL::Program               _program;

  mutable placeholders::GL::BufferObjects         _buffer_objects;
  mutable placeholders::GL::BOs                   _bos;
  mutable placeholders::GL::BO                    _bo;
  mutable placeholders::GL::RBOs                  _rbos;
  mutable placeholders::GL::RBO                   _rbo;
  mutable placeholders::GL::FBOs                  _fbos;
  mutable placeholders::GL::FBO                   _fbo;

  mutable placeholders::GL::Textures              _textures;
  mutable placeholders::GL::Texture               _texture;

};

#endif // GMOPENGLPROXYMODEL_H
