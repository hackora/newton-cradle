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


  Q_INVOKABLE int         getGLObjectType( const QModelIndex& index ) const;

  Q_INVOKABLE QVariant    getProperty(const QModelIndex &index, const QString& name ) const;



  // From QAbstractItemModel
  QModelIndex             index(int row, int column, const QModelIndex &parent) const override;
  QModelIndex             parent(const QModelIndex &child) const override;
  int                     rowCount(const QModelIndex &parent) const override;
  int                     columnCount(const QModelIndex &parent) const override;
  QVariant                data(const QModelIndex &index, int role) const override;

  QHash<int,QByteArray>   roleNames() const override;

  enum UserRoles : int {
    Id = Qt::UserRole + 1,
    Name,
    DisplayName,
    Icon
  };
  Q_ENUM (UserRoles)

  enum GLObjectType : int {
    Invalid = 0,
    Shader,
    Program,
    Buffer,
    Framebuffer,
    Renderbuffer,
    Texture
  };
  Q_ENUM (GLObjectType)


private:
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


  QVariant                getTextureProperty(const QModelIndex& index, const QString& name ) const;
  QVariant                getShaderProperty(const QModelIndex& index, const QString& name ) const;

  template <typename T>
  auto constexpr getGLObjetcInfoItrAt( const T& objinfo_list, int at ) -> decltype(objinfo_list.begin()) const {

    auto itr = objinfo_list.begin();
    for(int row = 0; row < at and itr != objinfo_list.end(); ++row, ++itr );

    return itr;
  }

  template <typename T>
  QVariant constexpr getCommonGLObjectProperty( const T& objinfo_list, int at, const QString& name) const {

    auto itr = getGLObjetcInfoItrAt(objinfo_list,at);

    if(     name == "id")         return itr->id;
    else if(name == "name")       return itr->name.c_str();
    else if(name == "count")      return itr->counter;
    else if(name == "persistent") return itr->persistent;
    else                          return QVariant();
  }

};

#endif // GMOPENGLPROXYMODEL_H
