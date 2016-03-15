#include "gmlibwrapper.h"
#include "glcontextsurfacewrapper.h"


#include "../testtorus.h"
#include "utils.h"


// GMlib
#include <gmOpenglModule>
#include <gmSceneModule>
#include <gmParametricsModule>

// Qt
#include <QTimerEvent>
#include <QRectF>
#include <QMouseEvent>
#include <QDebug>
#include <QColor>

// stl
#include <stdexcept>
#include <thread>
#include <mutex>





std::unique_ptr<GMlibWrapper> GMlibWrapper::_instance {nullptr};


GMlibWrapper::GMlibWrapper(std::shared_ptr<GLContextSurfaceWrapper> context)
//  : GMlibWrapper()
  : QObject(), _timer_id{0}, _glsurface(context), _select_renderer{nullptr}
{

  if(_instance != nullptr) {

    std::cerr << "This version of the GMlibWrapper only supports a single instance of the GMlibWraper..." << std::endl;
    std::cerr << "Only one of me(0x" << this << ") please!! ^^" << std::endl;
    assert(!_instance);
    exit(666);
  }


  _instance = std::unique_ptr<GMlibWrapper>(this);

  _glsurface->makeCurrent();

  // Setup and initialized GMlib GL backend
  GMlib::GL::OpenGLManager::init();

  // Setup and init the GMlib GMWindow
  _scene = std::make_shared<GMlib::Scene>();
}

GMlibWrapper::~GMlibWrapper() {

  stop();

  _glsurface->makeCurrent(); {

    _select_renderer->releaseCamera();
    _select_renderer.reset();

    for( auto& rc_pair : _rc_pairs ) {

      rc_pair.second.renderer->releaseCamera();
      _scene->removeCamera( rc_pair.second.camera.get() );

      rc_pair.second.renderer.reset();
      rc_pair.second.camera.reset();
    }

    _scene->clear();

  } _glsurface->doneCurrent();
}

void GMlibWrapper::changeRcPairViewport(const QString& name, const QRectF& geometry) {

  const QSize size = geometry.size().toSize();

  if( size.width() <= 0 || size.height() <= 0 )
    return;

  if( _rc_pairs.count(name.toStdString()) <= 0 )
    return;

  auto& viewport = _rc_pairs[name.toStdString()].viewport;
  if(viewport.geometry == geometry )
    return;

  viewport.geometry = geometry;
  viewport.changed = true;
}

void GMlibWrapper::toggleSimulation() {

  _scene->toggleRun();
}

void GMlibWrapper::timerEvent(QTimerEvent* e) {

  e->accept();

  // Simuation order
  // 1) Prepare must be run first
  // 2) Simulate and render can be run in parallell


  // Grab and activate GL context
  _glsurface->makeCurrent(); {

    _scene->prepare();

    _scene->simulate();

    for( auto& rc_pair : _rc_pairs ) {

      const auto&   active  = rc_pair.second.active;
      auto&         camera  = rc_pair.second.camera;
      auto&       renderer  = rc_pair.second.renderer;
      auto&       viewport  = rc_pair.second.viewport;

      // Continue with next pair if not active
      if(!active) continue;

      // Update viewport
      if(viewport.changed) {

        const auto& size = viewport.geometry.size();
        renderer->reshape( GMlib::Vector<int,2>(size.width(),size.height()));
        camera->reshape( 0, 0, size.width(), size.height() );
        viewport.changed = false;
      }

      // Render and swap buffers
      renderer->render();
      renderer->swap();
    }

  } _glsurface->doneCurrent();

  emit signFrameReady();
}

const GMlibWrapper&
GMlibWrapper::getInstance() {
  return *_instance;
}

void GMlibWrapper::start() {

  if( _timer_id || _scene->isRunning() )
    return;

  _timer_id = startTimer(16, Qt::PreciseTimer);
  _scene->start();
}

void GMlibWrapper::stop() {

  if( !_timer_id || !_scene->isRunning() )
    return;

  _scene->stop();
  killTimer(_timer_id);
  _timer_id = 0;
}

void GMlibWrapper::init() {

  // Make OpenGL context current on offscreensurface
  _glsurface->makeCurrent(); {

    // Setup Select Renderer
    _select_renderer = std::make_shared<GMlib::DefaultSelectRenderer>();
    _select_renderer->setSelectRboName("select_render_color_rbo");

  } _glsurface->doneCurrent();
}

GMlib::SceneObject*
GMlibWrapper::findSceneObject(const QString& rc_name, const GMlib::Point<int,2>& pos) {

  if(!_rc_pairs.count(rc_name.toStdString()))
    throw std::invalid_argument("[][]Render/Camera pair '" + rc_name.toStdString() + "'  does not exist in [" + __FILE__ + " on line " + std::to_string(__LINE__) + "]!");

  auto rc_pair = _rc_pairs.at(rc_name.toStdString());
  auto cam = rc_pair.camera;
  auto viewport = rc_pair.viewport.geometry.size();
  GMlib::Vector<int,2> size( viewport.width(), viewport.height() );


  GMlib::SceneObject* sel_obj = nullptr;

  // Setup select renderer to match current view and prepare
  _select_renderer->setCamera(cam.get());
  _select_renderer->reshape( size );
  _select_renderer->prepare();

  // Render selectors and find object ad pos
  _select_renderer->select( GMlib::GM_SO_TYPE_SELECTOR );
  sel_obj = _select_renderer->findObject(pos(0),pos(1));


  // Render other objects and find object ad pos
  if(!sel_obj) {

    _select_renderer->select( -GMlib::GM_SO_TYPE_SELECTOR );
    sel_obj = _select_renderer->findObject(pos(0),pos(1));
  }

  return sel_obj;
}

RenderCamPair&
GMlibWrapper::rcPair(const QString& name) {

  if(!_rc_pairs.count(name.toStdString())) throw std::invalid_argument("[][]Render/Camera pair '" + name.toStdString() + "'  does not exist!");
  return _rc_pairs.at(name.toStdString());
}

const RenderCamPair&
GMlibWrapper::rcPair(const QString& name) const {

  if(!_rc_pairs.count(name.toStdString())) throw std::invalid_argument("[][]Render/Camera pair '" + name.toStdString() + "'  does not exist!");
  return _rc_pairs.at(name.toStdString());
}

RenderCamPair& GMlibWrapper::createRCPair(const QString& name) {

  auto rc_pair = RenderCamPair {};

  rc_pair.renderer = std::make_shared<GMlib::DefaultRenderer>();
  rc_pair.camera = std::make_shared<GMlib::Camera>();
  rc_pair.renderer->setCamera(rc_pair.camera.get());

  auto rc_names = _rc_name_model.stringList();
  rc_names << name;
  _rc_name_model.setStringList(rc_names);

  return _rc_pairs[name.toStdString()] = rc_pair;
}

std::shared_ptr<GMlib::DefaultSelectRenderer>
GMlibWrapper::defaultSelectRenderer() const {

  return _select_renderer;
}

QVariantList
GMlibWrapper::getRCPairNamesList() const {

  QVariantList names;
  for( const auto& rcpair : _rc_pairs ) names << rcpair.first.c_str();
  return names;
}

QVariant
GMlibWrapper::getRCPairProperty(const QString& name, const QString& property_name) const {

  if(!name.length()) return QVariant();

  if(property_name == "clear_color") {

    auto c = rcPair(name).renderer->getClearColor();
    QColor color;
    color.setRgbF(c.getRedC(),c.getGreenC(),c.getBlueC(),c.getAlphaC());
    return color;
  }

  return QVariant();
}

bool
GMlibWrapper::setRCPairProperty(const QString& name, const QString& property_name, const QVariant& value) {

  if(!name.length()) return false;

  if(property_name == "clear_color") {

    auto c = value.value<QColor>();
    GMlib::Color color(c.redF(),c.greenF(),c.blueF(),c.alphaF());
    rcPair(name).renderer->setClearColor(color);
  }

  return false;
}

void
GMlibWrapper::changeRcPairActiveState(const QString& name, bool state) {

  rcPair(name).active = state;
}

QStringListModel&
GMlibWrapper::rcNameModel() {

  return _rc_name_model;
}

const std::shared_ptr<GMlib::Scene>&
GMlibWrapper::scene() const {

  return _scene;
}

const GMlib::TextureRenderTarget&
GMlibWrapper::renderTextureOf(const QString& name) const {

  return rcPair(name).renderer->getFrontRenderTarget();
}

const std::shared_ptr<GMlib::Camera>&
GMlibWrapper::camera(const QString& name) const {

  return rcPair(name).camera;
}
