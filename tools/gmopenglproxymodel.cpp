#include "gmopenglproxymodel.h"

#include "../application/glcontextsurfacewrapper.h"

// gmlib
#include <gmOpenglModule>

// qt
#include <QDebug>








GMOpenGLProxyModel::GMOpenGLProxyModel(std::shared_ptr<GLContextSurfaceWrapper> glsurface)
  : _glsurface{glsurface}
{
  Q_ASSERT(glsurface);
}

int
GMOpenGLProxyModel::getGLObjectType(const QModelIndex& index) const {

  if(!index.isValid()) return -1;

  if(     index.internalPointer() == &_shader)    return  int(GLObjectType::Shader);
  else if(index.internalPointer() == &_program)   return  int(GLObjectType::Program);
  else if(index.internalPointer() == &_bo)        return  int(GLObjectType::Buffer);
  else if(index.internalPointer() == &_fbo)       return  int(GLObjectType::Framebuffer);
  else if(index.internalPointer() == &_rbo)       return  int(GLObjectType::Renderbuffer);
  else if(index.internalPointer() == &_texture)   return  int(GLObjectType::Texture);
  else                                            return  int(GLObjectType::Invalid);
}

QVariant
GMOpenGLProxyModel::getProperty(const QModelIndex& index, const QString& name) const {

  if(!index.isValid()) return QVariant();

  // Common object properties
  // id
  // name
  // persistent
  // valid
  if( name == "id" or name == "name" or name == "count" or name == "persistent") {
    if(     index.internalPointer() == &_shader)  return  getCommonGLObjectProperty( GMlib::GL::Shader::getData(),             index.row(), name );
    else if(index.internalPointer() == &_program) return  getCommonGLObjectProperty( GMlib::GL::Program::getData(),            index.row(), name );
    else if(index.internalPointer() == &_bo)      return  getCommonGLObjectProperty( GMlib::GL::BufferObject::getData(),       index.row(), name );
    else if(index.internalPointer() == &_fbo)     return  getCommonGLObjectProperty( GMlib::GL::FramebufferObject::getData(),  index.row(), name );
    else if(index.internalPointer() == &_rbo)     return  getCommonGLObjectProperty( GMlib::GL::RenderbufferObject::getData(), index.row(), name );
    else if(index.internalPointer() == &_texture) return  getCommonGLObjectProperty( GMlib::GL::Texture::getData(),            index.row(), name );
    else                                          return  QVariant();
  }

  if(     index.internalPointer() == &_shader)  return getShaderProperty(index,name);
  else if(index.internalPointer() == &_program) return getProgramProperty(index,name);
  else if(index.internalPointer() == &_texture) return getTextureProperty(index,name);

  return QVariant();
}

bool
GMOpenGLProxyModel::setProperty(const QModelIndex& index, const QString& name, const QVariant& data) {

  if(!index.isValid()) return false;

  if(index.internalPointer() == &_shader)  return setShaderProperty(index,name,data);

  return false;
}

bool
GMOpenGLProxyModel::setShaderProperty(const QModelIndex& index, const QString& name, const QVariant& data) {


  auto itr = getGLObjetcInfoItrAt( GMlib::GL::Shader::getData(), index.row());

  GLCSWMakeCurrent context(_glsurface);
  context.makeCurrent();

  auto shader_id = itr->id;

  if(name=="source") {

    auto source_std = data.toString().toStdString();
    const char* source = source_std.c_str();

    // set source
    GL_CHECK(::glShaderSource(shader_id, 1, &source, 0x0) );

    // compile
    GL_CHECK(::glCompileShader( shader_id ));

    // check if compile is ok
    int compile_ok;
    GL_CHECK(::glGetShaderiv( shader_id, GL_COMPILE_STATUS, &compile_ok ));

    if(compile_ok != GL_TRUE) {

      qDebug() << "Compile failed!!!!";

      int len = 0;
      int written = 0;
      char *log;

      GL_CHECK(::glGetShaderiv( shader_id, GL_INFO_LOG_LENGTH, &len ));

      if( len > 0 ) {

        len = len+1;
        log = new char[len];
        GL_CHECK(::glGetShaderInfoLog( shader_id, len, &written, log ));
        qDebug() << "Compiler log: " << log;
        delete log;

        qDebug() << "SOURCE: " << source;
      }

      return false;
    }

    auto programs = GMlib::GL::Program::getData();
    for( auto prog_itr : programs ) {

      auto prog_id = prog_itr.id;

      GLint no_as;
      GL_CHECK(::glGetProgramiv( prog_id, GL_ATTACHED_SHADERS, &no_as ));

      std::vector<GLuint> shader_ids(no_as);
      GL_CHECK(::glGetAttachedShaders( prog_id, no_as, 0x0, &shader_ids[0] ) );


      bool program_has_shader = false;
      for( auto prog_shader_id : shader_ids ) if(prog_shader_id == shader_id) program_has_shader = true;

      // Try to link program if program has shader
      if(program_has_shader) {

        // Link program
        GL_CHECK(::glLinkProgram( prog_id ));

        // get link status
        int link_ok;
        GL_CHECK(::glGetProgramiv( prog_id, GL_LINK_STATUS, &link_ok ));

        if(link_ok != GL_TRUE) {

          qDebug() << "Linking failed!!!!";


          int len = 0;
          int written = 0;
          char *log;

          GL_CHECK(::glGetProgramiv( prog_id, GL_INFO_LOG_LENGTH, &len ));

          if( len > 0 ) {

            len = len+1;
            log = new char[len];

            GL_CHECK(::glGetProgramInfoLog( prog_id, len, &written, log ));

            qDebug() << "Linker log: " << log;

            delete log;
          }



          return false;
        }
      }
    }
  }

  return true;
}

QVariant
GMOpenGLProxyModel::getTextureProperty(const QModelIndex& index, const QString& name) const {

  auto itr = getGLObjetcInfoItrAt( GMlib::GL::Texture::getData(), index.row());

  if(name == "target") {
    GLenum trgt =  itr->target;
    switch(trgt) {
      case GL_TEXTURE_1D: return "GL_TEXTURE_1D";
      case GL_TEXTURE_2D: return "GL_TEXTURE_2D";
      case GL_TEXTURE_3D: return "GL_TEXTURE_3D";
      default:            return trgt;              // Look it up gdmn'it (way to much legwork for now)
    }
  }

  return QVariant();
}

QVariant
GMOpenGLProxyModel::getShaderProperty(const QModelIndex& index, const QString& name) const {

  auto itr = getGLObjetcInfoItrAt( GMlib::GL::Shader::getData(), index.row());
  if(name=="source") {

    const GLuint id = itr->id;
    std::vector<char> buff;

    GLCSWMakeCurrent context(_glsurface);
    context.makeCurrent();

    int length;
    GL_CHECK(::glGetShaderiv( id, GL_SHADER_SOURCE_LENGTH, &length ));
    length++;

    int read;
    buff.resize(length);
    GL_CHECK(::glGetShaderSource( id, length, &read, buff.data() ));

    return std::string( buff.data() ).c_str();
  }

  return QVariant();
}

QVariant
GMOpenGLProxyModel::getProgramProperty(const QModelIndex& index, const QString& name) const {

  auto itr = getGLObjetcInfoItrAt( GMlib::GL::Program::getData(), index.row());
//  if(name=="source") {
//    GMlib::GL::Program prog;
//    prog.acquire(itr->id);
//    qDebug() << "Source: " << prog.getSource().c_str();
//    return prog.getSource().c_str();
//  }

  return QVariant();
}

QModelIndex
GMOpenGLProxyModel::index(int row, int column, const QModelIndex& parent) const {

  if(!hasIndex(row,column,parent)) return QModelIndex();


  if(!parent.isValid()) {
    switch(row) {
      case 0:  return createIndex(row,column,&_shaders_and_programs);
      case 1:  return createIndex(row,column,&_buffer_objects);
      case 2:  return createIndex(row,column,&_textures);
      default: return QModelIndex();
    }
  }

  const auto no_shaders              = GMlib::GL::Shader::getData().size();
  const auto no_programs             = GMlib::GL::Program::getData().size();
  const auto no_buffer_objects       = GMlib::GL::BufferObject::getData().size();
  const auto no_framebuffer_objects  = GMlib::GL::FramebufferObject::getData().size();
  const auto no_renderbuffer_objects = GMlib::GL::RenderbufferObject::getData().size();
  const auto no_textures             = GMlib::GL::Texture::getData().size();


  if(parent.internalPointer() == &_shaders_and_programs) {
    switch (row) {
      case 0:   return createIndex(row,column,&_shaders);
      case 1:   return createIndex(row,column,&_programs);
    }
  }
  else if(parent.internalPointer() == &_shaders and row < no_shaders)
    return createIndex( row, column, &_shader );
  else if(parent.internalPointer() == &_programs and row < no_programs)
    return createIndex( row, column, &_program );
  else if(parent.internalPointer() == &_buffer_objects ) {
    switch (row) {
      case 0:   return createIndex(row,column,&_bos);
      case 1:   return createIndex(row,column,&_fbos);
      case 2:   return createIndex(row,column,&_rbos);
    }
  }
  else if(parent.internalPointer() == &_bos and row < no_buffer_objects)
    return createIndex(row,column,&_bo);
  else if(parent.internalPointer() == &_fbos and row < no_framebuffer_objects)
    return createIndex(row,column,&_fbo);
  else if(parent.internalPointer() == &_rbos and row < no_renderbuffer_objects)
    return createIndex(row,column,&_rbo);
  else if(parent.internalPointer() == &_textures and row < no_textures )
    return createIndex( row, column, &_texture );

  return QModelIndex();
}

QModelIndex
GMOpenGLProxyModel::parent(const QModelIndex& child) const {
  Q_UNUSED(child)

  if(!child.isValid()) return QModelIndex();


  if(     child.internalPointer() == &_shaders)         return createIndex(0,0, &_shaders_and_programs);
  else if(child.internalPointer() == &_programs)        return createIndex(0,0,&_shaders_and_programs);

  else if(child.internalPointer() == &_bos)             return createIndex(1,0,&_buffer_objects);
  else if(child.internalPointer() == &_bo)              return createIndex(0,0,&_bos);

  else if(child.internalPointer() == &_fbos)            return createIndex(1,0,&_buffer_objects);
  else if(child.internalPointer() == &_fbo)             return createIndex(1,0,&_fbos);

  else if(child.internalPointer() == &_rbos)            return createIndex(1,0,&_buffer_objects);
  else if(child.internalPointer() == &_rbo)             return createIndex(2,0,&_rbos);

  else if(child.internalPointer() == &_texture)         return createIndex(2,0,&_textures);

  return QModelIndex();
}

int
GMOpenGLProxyModel::rowCount(const QModelIndex& parent) const {

  if( parent.column() > 0 ) return 0;

  if(!parent.isValid()) return 3;

  if(      parent.internalPointer() == &_shaders_and_programs ) return 2;
  else if( parent.internalPointer() == &_shaders )
    return GMlib::GL::Shader::getData().size();
  else if( parent.internalPointer() == &_programs )
    return GMlib::GL::Program::getData().size();
  else if( parent.internalPointer() == &_buffer_objects ) return 3;
  else if( parent.internalPointer() == &_bos )
    return GMlib::GL::BufferObject::getData().size();
  else if( parent.internalPointer() == &_fbos )
    return GMlib::GL::FramebufferObject::getData().size();
  else if( parent.internalPointer() == &_rbos )
    return GMlib::GL::RenderbufferObject::getData().size();
  else if( parent.internalPointer() == &_textures )
    return GMlib::GL::Texture::getData().size();
  else
    return 0;
}

int
GMOpenGLProxyModel::columnCount(const QModelIndex& parent) const {
  Q_UNUSED(parent)

  return 1;
}

QVariant
GMOpenGLProxyModel::data(const QModelIndex& index, int role) const {

  if(!index.isValid()) return QVariant("INVALID");

  // Categories
  if(index.internalPointer() == &_shaders_and_programs) {
    if( UserRoles(role) == UserRoles::DisplayName ) return "Shaders & Programs";
    else QVariant();
  }
  else if(index.internalPointer() == &_shaders) {
    if( UserRoles(role) == UserRoles::DisplayName ) return "Shaders";
    else QVariant();
  }
  else if(index.internalPointer() == &_shader) {

    auto itr = getGLObjetcInfoItrAt( GMlib::GL::Shader::getData(), index.row());
    if(itr == GMlib::GL::Shader::getData().end()) return QVariant("out of bounds");
    switch(UserRoles(role)) {
      case UserRoles::Id:               return itr->id;
      case UserRoles::Name:             return itr->name.c_str();
      case UserRoles::DisplayName:      return QString("%1").arg(itr->id, 4) + (itr->name.size()?QString(" (%1)").arg(itr->name.c_str()):"");
      case UserRoles::Icon: {
        auto type = itr->type;
        switch(type) {
          case GL_VERTEX_SHADER:          return "VS";
          case GL_TESS_CONTROL_SHADER:    return "TCS";
          case GL_TESS_EVALUATION_SHADER: return "TES";
          case GL_GEOMETRY_SHADER:        return "GS";
          case GL_FRAGMENT_SHADER:        return "FS";
        }
      }
    }

  }
  else if(index.internalPointer() == &_programs) {
    if( UserRoles(role) == UserRoles::DisplayName ) return "Programs";
    else QVariant();
  }
  else if(index.internalPointer() == &_program) {

    auto itr = getGLObjetcInfoItrAt( GMlib::GL::Program::getData(), index.row());
    if(itr == GMlib::GL::Program::getData().end()) return QVariant("out of bounds");
    switch(UserRoles(role)) {
      case UserRoles::Id:               return itr->id;
      case UserRoles::Name:             return itr->name.c_str();
      case UserRoles::DisplayName:      return QString("%1").arg(itr->id, 4) + (itr->name.size()?QString(" (%1)").arg(itr->name.c_str()):"");
    }
  }
  else if(index.internalPointer() == &_buffer_objects) {
    if( UserRoles(role) == UserRoles::DisplayName ) return "Buffers";
    else QVariant();
  }
  else if(index.internalPointer() == &_bos) {
    if( UserRoles(role) == UserRoles::DisplayName ) return "Buffer objects";
    else QVariant();
  }
  else if(index.internalPointer() == &_bo) {

    auto itr = getGLObjetcInfoItrAt( GMlib::GL::BufferObject::getData(), index.row());
    if(itr == GMlib::GL::BufferObject::getData().end()) return QVariant("out of bounds");
    switch(UserRoles(role)) {
      case UserRoles::Id:               return itr->id;
      case UserRoles::Name:             return itr->name.c_str();
      case UserRoles::DisplayName:      return QString("%1").arg(itr->id, 4) + (itr->name.size()?QString(" (%1)").arg(itr->name.c_str()):"");
    }
  }
  else if(index.internalPointer() == &_fbos) {
    if( UserRoles(role) == UserRoles::DisplayName ) return "Framebuffer objects";
    else QVariant();
  }
  else if(index.internalPointer() == &_fbo) {

    auto itr = getGLObjetcInfoItrAt( GMlib::GL::FramebufferObject::getData(), index.row());
    if(itr == GMlib::GL::FramebufferObject::getData().end()) return QVariant("out of bounds");
    switch(UserRoles(role)) {
      case UserRoles::Id:               return itr->id;
      case UserRoles::Name:             return itr->name.c_str();
      case UserRoles::DisplayName:      return QString("%1").arg(itr->id, 4) + (itr->name.size()?QString(" (%1)").arg(itr->name.c_str()):"");
    }
  }
  else if(index.internalPointer() == &_rbos) {
    if( UserRoles(role) == UserRoles::DisplayName ) return "Renderbuffer objects";
    else QVariant();
  }
  else if(index.internalPointer() == &_rbo) {

    auto itr = getGLObjetcInfoItrAt( GMlib::GL::RenderbufferObject::getData(), index.row());
    if(itr == GMlib::GL::RenderbufferObject::getData().end()) return QVariant("out of bounds");
    switch(UserRoles(role)) {
      case UserRoles::Id:               return itr->id;
      case UserRoles::Name:             return itr->name.c_str();
      case UserRoles::DisplayName:      return QString("%1").arg(itr->id, 4) + (itr->name.size()?QString(" (%1)").arg(itr->name.c_str()):"");
    }
  }
  else if(index.internalPointer() == &_textures) {
    if( UserRoles(role) == UserRoles::DisplayName ) return "Textures";
    else QVariant();
  }
  else if(index.internalPointer() == &_texture) {

    auto itr = getGLObjetcInfoItrAt( GMlib::GL::Texture::getData(), index.row());
    if(itr == GMlib::GL::Texture::getData().end()) return QVariant("out of bounds");
    switch(UserRoles(role)) {
      case UserRoles::Id:               return itr->id;
      case UserRoles::Name:             return itr->name.c_str();
      case UserRoles::DisplayName:      return QString("%1").arg(itr->id, 4) + (itr->name.size()?QString(" (%1)").arg(itr->name.c_str()):"");
    }
  }

  return QVariant();
}

QHash<int, QByteArray>
GMOpenGLProxyModel::roleNames() const {

  QHash<int, QByteArray> names;
  names[int(UserRoles::Id)]             = "id";
  names[int(UserRoles::Name)]           = "name";
  names[int(UserRoles::DisplayName)]    = "display_name";
  names[int(UserRoles::Icon)]           = "icon";
  return names;
}
