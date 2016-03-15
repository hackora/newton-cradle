#include "gmlibqmltypes.h"

// Qt
#include <QtQml>







QColor
Color_GM::toQColor() const {  return  convertToQColor(*this); }

void Color_GM::setQColor(const QColor& color) { GMlib::Color::operator = (convertToGMlibColor(color)); }


GMlib::Color
Color_GM::convertToGMlibColor(const QColor& c) {

  GMlib::Color color(c.redF(),c.greenF(),c.blueF(),c.alphaF());
  return color;
}

QColor
Color_GM::convertToQColor(const GMlib::Color& c) {

  QColor color;
  color.setRgbF(c.getRedC(),c.getGreenC(),c.getBlueC(),c.getAlphaC());
  return color;
}











void registerGMlibQmlTypes() {

//  qmlRegisterType<Color_GM,1>( "GMlibTypes", 1, 0, "Color_GM" );
//  qRegisterMetaType<Color_GM>("Color_GM");

}
