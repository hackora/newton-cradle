#include "scenario.h"

#include "testtorus.h"

// application
#include "application/gmlibwrapper.h"
#include "application/window.h"

// hidmanager
#include "hidmanager/defaulthidmanager.h"

// scenemodel
#include "mysceneproxymodel.h"

// gmlib
#include <gmOpenglModule>
#include <gmSceneModule>
#include <gmParametricsModule>

// qt
#include <QQuickItem>



void Scenario::initializeScenario() {

  // Insert a light
  auto *light = new GMlib::PointLightG( GMlib::GMcolor::White, GMlib::GMcolor::White,
                                        GMlib::GMcolor::White,
                                        GMlib::Point<GLfloat,3>( 2.0, 4.0, 10 ) );
  light->setAttenuation(0.8, 0.002, 0.0008);
  scene()->insertLight( light, true );

  // Insert Sun
  scene()->insertSun();

  // Default camera parameters
  int init_viewport_size = 600;
  GMlib::Point<float,3> init_cam_pos(  0.0f, 0.0f, 0.0f );
  GMlib::Vector<float,3> init_cam_dir( 0.0f, 1.0f, 0.0f );
  GMlib::Vector<float,3> init_cam_up(  0.0f, 0.0f, 1.0f );

  // Projection cam
  auto proj_rcpair = gmlib()->createRCPair("Projection");
  proj_rcpair.camera->set(init_cam_pos,init_cam_dir,init_cam_up);
  proj_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  proj_rcpair.camera->rotateGlobal( GMlib::Angle(-45), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
  proj_rcpair.camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -20.0f, 20.0f ) );
  scene()->insertCamera( proj_rcpair.camera.get() );
  proj_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

  // Front cam
  auto front_rcpair = gmlib()->createRCPair("Front");
  front_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( 0.0f, -50.0f, 0.0f ), init_cam_dir, init_cam_up );
  front_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  scene()->insertCamera( front_rcpair.camera.get() );
  front_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

  // Side cam
  auto side_rcpair = gmlib()->createRCPair("Side");
  side_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( -50.0f, 0.0f, 0.0f ), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ), init_cam_up );
  side_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  scene()->insertCamera( side_rcpair.camera.get() );
  side_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

  // Top cam
  auto top_rcpair = gmlib()->createRCPair("Top");
  top_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( 0.0f, 0.0f, 50.0f ), -init_cam_up, init_cam_dir );
  top_rcpair.camera->setCuttingPlanes( 1.0f, 8000.0f );
  scene()->insertCamera( top_rcpair.camera.get() );
  top_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );







  // Surface visualizers
  auto surface_visualizer = new GMlib::PSurfNormalsVisualizer<float,3>;

  // Surface
  auto surface = new TestTorus;
  surface->setColor(GMlib::GMcolor::GreenYellow);
  surface->toggleDefaultVisualizer();
  surface->insertVisualizer(surface_visualizer);
  surface->replot(20,20,1,1);
  scene()->insert(surface);


  auto erbs = new GMlib::PERBSSurf<float>( surface, 4, 4, 3, 3 );
  erbs->toggleDefaultVisualizer();
  erbs->replot(20,20,1,1);
  surface->insert(erbs);

  surface->test01();







  // Setup default hid-bindings
  hidmanager()->setupDefaultHidBindings();





  // Load QML
  window()->setSource( QUrl("qrc:/qml/main.qml") );

  // Connect up HiD signals
  connect( hidmanager().get(), &DefaultHidManager::signToggleSimulation, gmlib().get(),          &GMlibWrapper::toggleSimulation );
  connect( hidmanager().get(), SIGNAL(signOpenCloseHidHelp()),           window()->rootObject(), SIGNAL(toggleHidBindView()) );


  resetSceneModel();
  qDebug() << "scene model row count: " << scenemodel()->rowCount();
  qDebug() << "scene model column count: " << scenemodel()->columnCount();
  qDebug() << "root objects in scene: " << scene()->getSize();
}

void Scenario::cleanupScenario() {

}
