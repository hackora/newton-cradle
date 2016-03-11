#include "texturerenderer.h"
#include "window.h"
#include "glcontextsurfacewrapper.h"
#include "gmlibwrapper.h"

// Qt
#include <QQuickWindow>


// stl
#include <iostream>



TextureRenderer::TextureRenderer() : _glsurface{nullptr} {

  setAcceptedMouseButtons(Qt::AllButtons);
  setFlag(ItemHasContents);
  setSmooth(false);
  connect( this, &QQuickItem::windowChanged, this, &TextureRenderer::handleWindowChanged );
}

TextureRenderer::~TextureRenderer() {}

void
TextureRenderer::setTextureName(const QString& name) {

  _tex.acquire(name.toStdString());
}

void
TextureRenderer::setTextureId(const QVariant& id) {

  _tex.acquire(id.toUInt());
}

void
TextureRenderer::setColorMagnification(int magn) {

  _color_magn = magn;
}

uint
TextureRenderer::textureId() const {

  return _tex.getId();
}

QStringList
TextureRenderer::textureIds() const {

  QStringList ids;
  for( const auto& d : GMlib::GL::Texture::getData() )
    ids << QString("%1").arg(d.id);
  return ids;
}

QStringList
TextureRenderer::textureNames() const {

  QStringList ids;
  for( const auto& d : GMlib::GL::Texture::getData() )
    if( d.name.size() ) ids << d.name.c_str();
  return ids;
}

bool
TextureRenderer::beforeRendering() const {

  return _before_rendering;
}

void
TextureRenderer::setBeforeRendering(bool state) {

  _before_rendering = state;
}

void
TextureRenderer::sync() {

  auto prog_valid = prog().isValid() and _prog.isValid();

  if(!prog_valid && _tex.isValid() > 0) {

    Window *w = static_cast<Window*>(window());
    _glsurface = w->glSurface();
    if(_before_rendering)
      connect( w, &Window::beforeRendering, this, &TextureRenderer::paint, Qt::DirectConnection );
    else
      connect( w, &Window::afterRendering, this, &TextureRenderer::paint, Qt::DirectConnection );
  }

  if( !prog_valid )
    return;

  QRectF r = mapRectToScene(boundingRect());
  QRectF cr(r.left(),window()->height()-r.bottom(), r.width(), r.height());
  _viewport = cr;
}

void
TextureRenderer::cleanup() {

  std::cout << "Cleanup" << std::endl;
}

void
TextureRenderer::initTexMagnProg() {

  const std::string unique_name = "qt_qml_renderer_magn";

  // Check wether prog is initialized
  if( _prog.isValid() )
    return;

  // Check if prog and canvas can be acquired, if not; create them
  auto prog_ok = _prog.acquire(unique_name);

  if(prog_ok)
    return;


  GMlib::GL::VertexShader   vs;
  GMlib::GL::FragmentShader fs;
  vs.create();
  fs.create();

  vs.setSource(
        "#version 150 compatibility \n"
        "layout(std140) uniform; \n"
        "in  vec4 vertices; \n"
        "out vec2 coords; \n"
        "out vec4 gl_Position; \n"
        "void main() { \n"
        "    gl_Position = vertices; \n"
        "    coords = (vertices.xy + vec2(1.0,1.0))*0.5; \n"
        "}"
        );

  fs.setSource(
        "#version 150 compatibility \n"
        "layout(std140) uniform; \n"
        "\n"
        "uniform int u_magn; \n"
        "uniform sampler2D u_tex0; \n"
        "in vec2 coords; \n"
        "void main() { \n"
        "    gl_FragColor = texture( u_tex0, coords.st ) * u_magn; \n"
        "}"
        );

  if( !vs.compile() ) {
    std::cout << "Vertex shader compile error: " << vs.getCompilerLog() << std::endl;
    exit(-666);
  }
  if(!fs.compile()) {
    std::cout << "Fragment shader compile error: " << fs.getCompilerLog() << std::endl;
    exit(-666);
  }

  _prog.create(unique_name);
  _prog.attachShader(vs);
  _prog.attachShader(fs);
  if( _prog.link() != GL_TRUE ) {
    std::cout << "Render prog link error: " << _prog.getLinkerLog() << std::endl;
    exit(-666);
  }
}

void
TextureRenderer::handleWindowChanged(QQuickWindow* window) {

  if( !window ) return;

  Window *w = dynamic_cast<Window*>(window);
  if( !w ) return;

  connect( w, &Window::beforeSynchronizing, this, &TextureRenderer::sync );
  connect( w, &Window::sceneGraphInvalidated, this, &TextureRenderer::cleanup );
  connect( w, &Window::signFrameReady, this, &QQuickItem::update );
}

void
TextureRenderer::paint() {

  if(!_tex.isValid()) return;
  if(!isVisible()) return;

  initCanvasAndProg();
  initTexMagnProg();

  GL_CHECK(::glViewport(_viewport.x(), _viewport.y(), _viewport.width(), _viewport.height()));
  GL_CHECK(::glDisable(GL_BLEND));
  _prog.bind(); {

    _prog.uniform( "u_tex0", _tex, GL_TEXTURE0, GLuint(0) );
    _prog.uniform( "u_magn", _color_magn );


    GMlib::GL::AttributeLocation vert_loc = prog().getAttributeLocation("vertices");

    canvas().bind();
    canvas().enableVertexArrayPointer( vert_loc, 2, GL_FLOAT, GL_FALSE, 0, static_cast<const GLvoid*>(nullptr) );
    GL_CHECK(::glDrawArrays(GL_TRIANGLE_STRIP,0,4));
    canvas().disable(vert_loc);
    canvas().unbind();

  } _prog.unbind();

}

void
TextureRenderer::itemChange(ItemChange change, const ItemChangeData& value) {

//  qDebug() << "TextureRenderer changes: " << _name << ", change: " << change << ", value: " << value.boolValue;
  if(change == QQuickItem::ItemVisibleHasChanged && !value.boolValue)
    disconnect( window(), &Window::beforeRendering, this, &TextureRenderer::paint );

  QQuickItem::itemChange(change,value);
}

QSGNode*
TextureRenderer::updatePaintNode(QSGNode* node, QQuickItem::UpdatePaintNodeData*) {

//  qDebug() << "updatePaintNode; item has content: " << ((flags() & QQuickItem::ItemHasContents) == QQuickItem::ItemHasContents ? "yes" : "no");
  return node;
}
