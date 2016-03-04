#ifndef GUIAPPLICATION_H
#define GUIAPPLICATION_H


class Window;
class GMlibWrapper;
class GLContextSurfaceWrapper;
class DefaultHidManager;
class SceneModel;

// gmlib
namespace GMlib {
  class Scene;
}

// qt
#include <QGuiApplication>

// stl
#include <memory>




class GuiApplication : public QGuiApplication {
  Q_OBJECT
public:
  explicit GuiApplication(int& argc, char* argv[]);
  ~GuiApplication();

    void      show();               // Need this as QT is difficult, just like a little bratt!!!

private:
  std::shared_ptr<Window>                     _window;
  std::shared_ptr<GMlibWrapper>               _gmlib;
  std::shared_ptr<GLContextSurfaceWrapper>    _glsurface;
  std::shared_ptr<DefaultHidManager>          _hidmanager;
  std::shared_ptr<SceneModel>                 _scenemodel;

  void                                        setupScene();

  virtual void                                initializeScenario() = 0;
  virtual void                                cleanupScenario() = 0;

private slots:

  // Void waranty on re-implementation
  virtual void                                onSGInit();

  void                                        beforeHidAction();
  void                                        afterHidAction();

protected:

  std::shared_ptr<Window>                     window();
  std::shared_ptr<GMlibWrapper>               gmlib();
  std::shared_ptr<GLContextSurfaceWrapper>    glsurface();
  std::shared_ptr<DefaultHidManager>          hidmanager();
  std::shared_ptr<GMlib::Scene>               scene();
  std::shared_ptr<SceneModel>                 scenemodel();

  void                                        resetSceneModel();



private:
  static std::unique_ptr<GuiApplication>      _instance;
public:
  static const GuiApplication&                instance();
};

#endif // GUIAPPLICATION_H
