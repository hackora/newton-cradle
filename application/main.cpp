// local
#include "../scenario.h"
#include "rcpairrenderer.h"
#include "texturerenderer.h"
#include "../tools/gmopenglproxymodel.h"
#include "../tools/sceneproxymodel.h"
#include "../tools/glslsyntaxhighlighter.h"
#include "../mysceneproxymodel.h"

// gmlib
#include <core/gmglobal>

// qt
#include <QDebug>

// stl
#include <stdexcept>

int main(int argc, char *argv[]) try {

  // Checking Qt Development Framework Version
  if( QT_VERSION < QT_VERSION_CHECK( 5, 1, 0 ) ) {

    QString critical = QString(
      "Qt version %1 not supported."
      "At least version 5.0.0 of the Qt Development Framework is needed. Please provided the necessary Qt Development Framework libraries."
    ).arg( QT_VERSION_STR );
    qCritical() << critical;
    return 0;
  }
  else
    qDebug() << QString( "Qt Development Framework version: %1" ).arg( QT_VERSION_STR ).toStdString().c_str();


  // Checking GMlib Version
  if( GM_VERSION < GM_VERSION_CHECK( 0,5, 0 ) ) {

    QString critical = QString(
      "GMlib version %1 not supported."
      "At least GMlib version 0.5.0 needed. Please Rebuild GMlib"
    ).arg( GM_VERSION_STR );
    qCritical() << critical;
    return 0;
  }
  else
    qDebug() << QString( "GMlib version: %1" ).arg( GM_VERSION_STR ).toStdString().c_str();



  // Register meta types


  // Register modules
  qmlRegisterType<RCPairRenderer>(        "MyCppComponents", 1, 0, "RCPairRenderer" );
  qmlRegisterType<TextureRenderer>(       "MyCppComponents", 1, 0, "TextureRenderer" );
  qmlRegisterType<GLSLSyntaxHighlighter>( "MyCppComponents", 1, 0, "GLSLSyntaxHighlighter" );

  // Register proxy models as modules to expose enumerations (introduce some sense of conformity)
  qmlRegisterType<GMOpenGLProxyModel>(    "MyCppComponents", 1, 0, "GMOpenGLProxyModel" );
  qmlRegisterType<SceneProxyModel>(       "MyCppComponents", 1, 0, "SceneProxyModel" );
  qmlRegisterType<MySceneProxyModel>(     "MyCppComponents", 1, 0, "MySceneProxyModel" );


  // Create the application object
  Scenario a(argc, argv);

  a.show();

  // Start the app, and return control to the Qt system.
  return a.exec();
}
catch(const std::invalid_argument& e) {
  std::cerr << "std::invlid_argument " << e.what() << std::endl;
  exit(1);
}
catch(const std::exception& e) {
  std::cerr << "std::exception : " << e.what() << std::endl;
  exit(1);
}
catch(...) {
  std::cerr << "exception!!" << std::endl;
  exit(1);
}
