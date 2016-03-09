#include "guiapplication.h"

// local
#include "glcontextsurfacewrapper.h"
#include "window.h"
#include "gmlibwrapper.h"

// hidmanager
#include "../hidmanager/defaulthidmanager.h"
#include "../hidmanager/hidmanagertreemodel.h"

// scenemodel
#include "../tools/scenemodel.h"

// qt
#include <QQmlContext>
#include <QQuickItem>
#include <QStringListModel>

// stl
#include <cassert>


std::unique_ptr<GuiApplication> GuiApplication::_instance {nullptr};


GuiApplication::GuiApplication(int& argc, char *argv[])
  : QGuiApplication(argc, argv),
    _window{std::make_shared<Window>()}, _gmlib{nullptr}, _glsurface{nullptr}
{

  assert(!_instance);
  _instance = std::unique_ptr<GuiApplication>(this);

  connect( _window.get(), &Window::sceneGraphInitialized,     this, &GuiApplication::onSGInit );
  connect( this,          &QGuiApplication::lastWindowClosed, this, &QGuiApplication::quit );
}

GuiApplication::~GuiApplication() {

  _glsurface->makeCurrent(); {

    _gmlib.reset();
    _window.reset();

  } _glsurface->doneCurrent();
}

void GuiApplication::show() {

  _window->show();
}

void
GuiApplication::onSGInit() {

  // Init GLSurface
  _window->initGLSurface();
  _glsurface = _window->glSurface();

  // Init GMlibWrapper
  _gmlib = std::make_shared<GMlibWrapper>(_glsurface);
  _gmlib->init();
  connect( _gmlib.get(),  &GMlibWrapper::signFrameReady,         _window.get(), &Window::update );
  connect( _window.get(), &Window::signRcPairViewportChanged,    _gmlib.get(),  &GMlibWrapper::changeRcPairViewport );
  connect( _window.get(), &Window::signRcPairActiveStateChanged, _gmlib.get(),  &GMlibWrapper::changeRcPairActiveState );

  // Create hidmanager
  _hidmanager = std::make_shared<DefaultHidManager>( _gmlib );
  _window->rootContext()->setContextProperty( "hidmanager_model", _hidmanager->getModel() );
  _window->rootContext()->setContextProperty( "rc_name_model", &_gmlib->rcNameModel() );

  // Create scene model
  _scenemodel = std::make_shared<SceneModel>( _gmlib );
  _window->rootContext()->setContextProperty( "scene_model", _scenemodel.get() );

  connect( _window.get(), &Window::signMousePressed,       _hidmanager.get(), &StandardHidManager::registerMousePressEvent );
  connect( _window.get(), &Window::signMouseReleased,      _hidmanager.get(), &StandardHidManager::registerMouseReleaseEvent );
  connect( _window.get(), &Window::signMouseDoubleClicked, _hidmanager.get(), &StandardHidManager::registerMouseDoubleClickEvent);
  connect( _window.get(), &Window::signMouseMoved,         _hidmanager.get(), &StandardHidManager::registerMouseMoveEvent );
  connect( _window.get(), &Window::signKeyPressed,         _hidmanager.get(), &StandardHidManager::registerKeyPressEvent );
  connect( _window.get(), &Window::signKeyReleased,        _hidmanager.get(), &StandardHidManager::registerKeyReleaseEvent );
  connect( _window.get(), &Window::signWheelEventOccurred, _hidmanager.get(), &StandardHidManager::registerWheelEvent );

  connect( _hidmanager.get(), &StandardHidManager::signBeforeHidAction, this,  &GuiApplication::beforeHidAction, Qt::DirectConnection );
  connect( _hidmanager.get(), &StandardHidManager::signAfterHidAction,  this,  &GuiApplication::afterHidAction );

//  connect(_hidmanager.get(), &StandardHidManager::signAfterHidAction,   _scenemodel.get(), &SceneModel::stupidForceModelUpdate);
  connect(_hidmanager.get(), &StandardHidManager::signAfterHidAction,   _scenemodel.get(), &SceneModel::revert);

  // Init test scene of the GMlib wrapper
  _glsurface->makeCurrent(); {
    initializeScenario();
  } _glsurface->doneCurrent();

  // Start simulator
  _gmlib->start();
}

void GuiApplication::beforeHidAction() {

//  qDebug() << "BeforeHidAction:";
  _glsurface->makeCurrent();
}

void GuiApplication::afterHidAction() {

//  qDebug() << "AfterHidAction:";
  _glsurface->doneCurrent();
}

std::shared_ptr<Window> GuiApplication::window() {

  return _window;
}

std::shared_ptr<GMlibWrapper> GuiApplication::gmlib() {

  return _gmlib;
}

std::shared_ptr<GLContextSurfaceWrapper> GuiApplication::glsurface() {

  return _glsurface;
}

std::shared_ptr<DefaultHidManager> GuiApplication::hidmanager() {

  return _hidmanager;
}

std::shared_ptr<GMlib::Scene> GuiApplication::scene() {

  return _gmlib->scene();
}

std::shared_ptr<SceneModel> GuiApplication::scenemodel() {

  return _scenemodel;
}

void GuiApplication::resetSceneModel() {

  _scenemodel->revert();
}

const GuiApplication&
GuiApplication::instance() {

  return *_instance;
}
